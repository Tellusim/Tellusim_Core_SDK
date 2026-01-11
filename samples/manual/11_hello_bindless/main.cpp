// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <TellusimApp.h>
#include <core/TellusimLog.h>
#include <core/TellusimBlob.h>
#include <core/TellusimTime.h>
#include <format/TellusimMesh.h>
#include <graphics/TellusimMeshModel.h>
#include <platform/TellusimWindow.h>
#include <platform/TellusimDevice.h>
#include <platform/TellusimKernel.h>
#include <platform/TellusimPipeline.h>
#include <platform/TellusimCompute.h>
#include <platform/TellusimCommand.h>

#include "panel.h"

/*
 */
using namespace Tellusim;

/*
 */
static Texture create_texture(const Device &device, const MeshMaterial &material, const char *type) {
	
	// find material parameter
	uint32_t index = material.findParameter(type);
	if(index == Maxu32 || !material.hasParameterFlag(index, MeshMaterial::FlagBlob)) return Texture::null;
	
	// load image
	Image image;
	Blob blob = material.getParameterBlob(index);
	if(!image.load(blob)) return Texture::null;
	
	// create texture
	return device.createTexture(image);
}

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	// create app
	App app(argc, argv);
	if(!app.create()) return 1;
	
	// create window
	Window window(app.getPlatform(), app.getDevice());
	if(!window || !window.setSize(app.getWidth(), app.getHeight())) return 1;
	if(!window.create("11 Hello Bindless") || !window.setHidden(false)) return 1;
	window.setKeyboardPressedCallback([&](uint32_t key, uint32_t code) {
		if(key == Window::KeyEsc) window.stop();
	});
	window.setCloseClickedCallback([&]() { window.stop(); });
	
	// vertex layout
	struct Vertex {
		Vector3f position;			// position
		Vector3f normal;			// normal vector
		Vector2f texcoord;			// texture coordinate
		Vector4f tangent;			// tangent vector and orientation
	};
	
	// geometry layout
	struct Geometry {
		uint32_t base_index = 0;			// base index buffer offset
		uint32_t normal_index = Maxu32;		// normal texture index
		uint32_t diffuse_index = Maxu32;	// diffuse texture index
		uint32_t metallic_index = Maxu32;	// metallic texture index
	};
	
	// common parameters
	struct CommonParameters {
		Matrix4x4f projection;		// projection matrix
		Matrix4x4f imodelview;		// imodelview matrix
		Vector4f camera;			// camera position
		Vector4f light;				// light position
	};
	
	// create device
	Device device(window);
	if(!device) return 1;
	
	// device info
	TS_LOGF(Message, "Device: %s\n", device.getName().get());
	
	// check compute tracing support
	if(!device.getFeatures().computeTracing) {
		TS_LOG(Error, "compute tracing is not supported\n");
		return 0;
	}
	
	// create pipeline
	Pipeline pipeline = device.createPipeline();
	pipeline.setTextureMask(0, Shader::MaskFragment);
	pipeline.setColorFormat(window.getColorFormat());
	pipeline.setDepthFormat(window.getDepthFormat());
	if(!pipeline.loadShaderGLSL(Shader::TypeVertex, "main.shader", "VERTEX_SHADER=1")) return 1;
	if(!pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "FRAGMENT_SHADER=1")) return 1;
	if(!pipeline.create()) return 1;
	
	// create model pipeline
	Pipeline model_pipeline = device.createPipeline();
	model_pipeline.addAttribute(Pipeline::AttributePosition, FormatRGBf32, 0, offsetof(Vertex, position), sizeof(Vertex));
	model_pipeline.addAttribute(Pipeline::AttributeNormal, FormatRGBf32, 0, offsetof(Vertex, normal), sizeof(Vertex));
	model_pipeline.addAttribute(Pipeline::AttributeTexCoord, FormatRGf32, 0, offsetof(Vertex, texcoord), sizeof(Vertex));
	model_pipeline.addAttribute(Pipeline::AttributeTangent, FormatRGBAf32, 0, offsetof(Vertex, tangent), sizeof(Vertex));
	
	// create kernel
	Kernel kernel = device.createKernel().setSamplers(1).setSurfaces(1).setUniforms(1).setStorages(3).setTracings(1).setTableType(0, TableTypeTexture, 2048);
	if(!kernel.loadShaderGLSL("main.shader", "COMPUTE_SHADER=1")) return 1;
	if(!kernel.create()) return 1;
	
	// load mesh
	Mesh mesh;
	if(!mesh.load("model.glb") || !mesh.getNumGeometries()) return 1;
	mesh.setBasis(Mesh::BasisZUpRight);
	mesh.createTangents();
	
	// create model
	MeshModel model;
	if(!model.create(device, model_pipeline, mesh, MeshModel::FlagMaterials | MeshModel::FlagIndices32 | MeshModel::FlagBufferStorage | MeshModel::FlagBufferTracing | MeshModel::FlagBufferAddress)) return 1;
	Buffer vertex_buffer = model.getVertexBuffer();
	Buffer index_buffer = model.getIndexBuffer();
	
	// create model tracing
	Array<Texture> textures;
	Array<Geometry> geometries;
	Tracing model_tracing = device.createTracing();
	for(uint32_t i = 0; i < model.getNumGeometries(); i++) {
		MeshGeometry mesh_geometry = mesh.getGeometry(i);
		for(uint32_t j = 0; j < model.getNumMaterials(i); j++) {
			MeshMaterial mesh_material = mesh_geometry.getMaterial(j);
			
			// geometry parameters
			Geometry &geometry = geometries.append();
			geometry.base_index = model.getMaterialBaseIndex(i, j);
			
			// load normal texture
			Texture normal_texture = create_texture(device, mesh_material, MeshMaterial::TypeNormal);
			if(normal_texture) {
				geometry.normal_index = textures.size();
				textures.append(normal_texture);
			}
			
			// load diffuse texture
			Texture diffuse_texture = create_texture(device, mesh_material, MeshMaterial::TypeDiffuse);
			if(diffuse_texture) {
				geometry.diffuse_index = textures.size();
				textures.append(diffuse_texture);
			}
			
			// load metallic texture
			Texture metallic_texture = create_texture(device, mesh_material, MeshMaterial::TypeMetallic);
			if(metallic_texture) {
				geometry.metallic_index = textures.size();
				textures.append(metallic_texture);
			}
			
			// tracing geometry
			model_tracing.addVertexBuffer(model.getNumGeometryVertices(i), model_pipeline.getAttributeFormat(0), model.getVertexBufferStride(0), vertex_buffer);
			model_tracing.addIndexBuffer(model.getNumMaterialIndices(i, j), FormatRu32, index_buffer, sizeof(uint32_t) * model.getMaterialBaseIndex(i, j));
		}
	}
	if(!model_tracing.create(Tracing::TypeTriangle, Tracing::FlagCompact | Tracing::FlagFastTrace)) return 1;
	
	// create geometry buffer
	Buffer geometry_buffer = device.createBuffer(Buffer::FlagStorage, geometries.get(), geometries.bytes());
	if(!geometry_buffer) return 1;
	
	// create instance buffer
	Buffer instance_buffer = device.createBuffer(Buffer::FlagStorage | Buffer::FlagTracing, Tracing::InstanceSize);
	if(!instance_buffer) return 1;
	
	// create instance tracing
	Tracing instance_tracing = device.createTracing(1, instance_buffer);
	if(!instance_tracing) return 1;
	
	// set instance tracing
	Tracing::Instance instance;
	instance.mask = 0xff;
	instance.tracing = &model_tracing;
	Matrix4x3f::identity.get(instance.transform);
	if(!device.setTracing(instance_tracing, &instance, 1)) return 1;
	
	// create build buffer
	size_t build_size = max(model_tracing.getBuildSize(), instance_tracing.getBuildSize());
	Buffer build_buffer = device.createBuffer(Buffer::FlagStorage | Buffer::FlagScratch, build_size);
	if(!build_buffer) return 1;
	
	// build model tracing
	if(!device.buildTracing(model_tracing, build_buffer, Tracing::FlagCompact)) return 1;
	device.flushTracing(model_tracing);
	
	// build instance tracing
	if(!device.buildTracing(instance_tracing, build_buffer)) return 1;
	device.flushTracing(instance_tracing);
	
	// create texture table
	TextureTable texture_table = device.createTextureTable(textures);
	if(!texture_table) return 1;
	
	// create sampler
	Sampler sampler = device.createSampler(Sampler::FilterLinear);
	if(!sampler) return 1;
	
	// create query
	Query time_query = device.createQuery(Query::TypeTime);
	
	// create target
	Target target = device.createTarget(window);
	
	// tracing surface
	Texture surface;
	
	// create panel
	Panel panel(device);
	
	// print info
	TS_LOGF(Message, "Tracing: %s\n", String::fromBytes(model_tracing.getMemory()).get());
	TS_LOGF(Message, "Vertex: %s\n", String::fromBytes(vertex_buffer.getSize()).get());
	TS_LOGF(Message, "Index: %s\n", String::fromBytes(index_buffer.getSize()).get());
	TS_LOGF(Message, "Build: %s\n", String::fromBytes(build_size).get());
	
	float32_t animation_time = 0.0f;
	float32_t old_animation_time = 0.0f;
	bool animation = !app.isArgument("pause");
	
	// main loop
	window.run([&]() {
		
		using Tellusim::sin;
		using Tellusim::cos;
		
		Window::update();
		
		// render window
		if(!window.render()) return false;
		
		// get query
		if(time_query.isAvailable()) panel.setInfo("\nDraw: " + String::fromTime(time_query.getTime()));
		
		// update panel
		panel.update(window, device, target);
		
		// animation time
		float32_t time = (float32_t)Time::seconds();
		if(window.getKeyboardKey(' ', true)) animation = !animation;
		if(animation) animation_time += time - old_animation_time;
		old_animation_time = time;
		
		// build instance tracing
		#if _MACOS || _IOS || _TVOS
			if(!device.buildTracing(instance_tracing, build_buffer)) return false;
			device.flushTracing(instance_tracing);
		#endif
		
		// create surface
		uint32_t width = window.getWidth();
		uint32_t height = window.getHeight();
		if(window.getKeyboardKey('1')) { width = 1600; height = 900; }
		if(window.getKeyboardKey('2')) { width = 1920; height = 1080; }
		if(window.getKeyboardKey('3')) { width = 3840; height = 2160; }
		if(!surface || surface.getWidth() != width || surface.getHeight() != height) {
			device.releaseTexture(surface);
			surface = device.createTexture2D(FormatRGBAu8n, width, height, Texture::FlagSurface);
		}
		
		// trace scene
		{
			// create command list
			Compute compute = device.createCompute();
			
			// begin query
			compute.beginQuery(time_query);
				
				// set kernel
				compute.setKernel(kernel);
				
				// set sampler
				compute.setSampler(0, sampler);
				
				// set common parameters
				CommonParameters common_parameters;
				common_parameters.camera = Vector4f(sin(animation_time) * 32.0f, 1200.0f * sin(animation_time * 0.1f), 128.0f + cos(animation_time) * 32.0f, 1.0f);
				common_parameters.light = Vector4f(0.0f, 1200.0f * sin(animation_time * 0.1f + 0.2f), common_parameters.camera.z, 1.0f);
				common_parameters.projection = Matrix4x4f::perspective(60.0f, (float32_t)window.getWidth() / window.getHeight(), 0.1f, true);
				common_parameters.imodelview = inverse(Matrix4x4f::lookAt(common_parameters.camera.xyz, common_parameters.light.xyz, Vector3f(0.0f, 0.0f, 1.0f)));
				compute.setUniform(0, common_parameters);
				
				// set storage buffers
				compute.setStorageBuffers(0, {
					geometry_buffer,
					vertex_buffer,
					index_buffer,
				});
				
				// set instance tracing
				compute.setTracing(0, instance_tracing);
				
				// set surface texture
				compute.setSurfaceTexture(0, surface);
				
				// set texture table
				compute.setTextureTable(0, texture_table);
				
				// dispatch tracing
				compute.dispatch(surface);
				
			// end query
			compute.endQuery(time_query);
		}
		
		// flush surface
		device.flushTexture(surface);
		
		// window target
		target.begin();
		{
			// create command list
			Command command = device.createCommand(target);
			
			// draw surface
			command.setPipeline(pipeline);
			command.setTexture(0, surface);
			command.drawArrays(3);
			
			// draw panel
			panel.draw(command, target);
		}
		target.end();
		
		// present window
		if(!window.present()) return false;
		
		// check errors
		if(!device.check()) return false;
		
		return true;
	});
	
	// finish context
	window.finish();
	
	return 0;
}

/*
 */
#if _ANDROID
	#include <system/TellusimAndroid.h>
	TS_DECLARE_ANDROID_NATIVE_ACTIVITY
#endif
