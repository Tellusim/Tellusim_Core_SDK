// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <common/common.h>
#include <math/TellusimMath.h>
#include <format/TellusimMesh.h>
#include <graphics/TellusimMeshModel.h>
#include <platform/TellusimDevice.h>
#include <platform/TellusimPipeline.h>
#include <platform/TellusimCommand.h>

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	DECLARE_WINDOW
	
	// create window
	String title = String::format("%s Tellusim::Tessellation", window.getPlatformName());
	DECLARE_WINDOW_CREATE(title)
	
	constexpr uint32_t grid_size = 16;
	
	// structures
	struct CommonParameters {
		Matrix4x4f projection;
		Matrix4x4f modelview;
		Matrix4x4f transform;
		Vector4f camera;
		uint32_t index;
		float32_t time;
	};
	
	// create device
	Device device(window);
	if(!device) return 1;
	
	// check tessellation support
	if(!device.hasShader(Shader::TypeControl) && !device.hasShader(Shader::TypeTask)) {
		TS_LOG(Error, "tessellation shader is not supported\n");
		return 0;
	}
	
	// create tessellation pipeline
	Pipeline tessellation_pipeline = device.createPipeline();
	tessellation_pipeline.setUniformMask(0, Shader::MaskVertex | Shader::MaskEvaluate);
	tessellation_pipeline.addAttribute(Pipeline::AttributePosition, FormatRGBAf16, 0, sizeof(float32_t) * 0, sizeof(float32_t) * 4);
	tessellation_pipeline.addAttribute(Pipeline::AttributeNormal, FormatRGBAf16, 0, sizeof(float32_t) * 2, sizeof(float32_t) * 4);
	tessellation_pipeline.setColorFormat(window.getColorFormat());
	tessellation_pipeline.setDepthFormat(window.getDepthFormat());
	tessellation_pipeline.setDepthFunc(Pipeline::DepthFuncLessEqual);
	tessellation_pipeline.setPrimitive(Pipeline::PrimitiveQuadrilateralPatch);
	if(device.hasShader(Shader::TypeControl)) {
		if(!tessellation_pipeline.loadShaderGLSL(Shader::TypeVertex, "main.shader", "VERTEX_SHADER=1; GRID_SIZE=%uu", grid_size)) return 1;
		if(!tessellation_pipeline.loadShaderGLSL(Shader::TypeControl, "main.shader", "CONTROL_SHADER=1")) return 1;
		if(!tessellation_pipeline.loadShaderGLSL(Shader::TypeEvaluate, "main.shader", "EVALUATE_SHADER=1")) return 1;
		if(!tessellation_pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "FRAGMENT_SHADER=1")) return 1;
		if(!tessellation_pipeline.create()) return 1;
	}
	
	// create mesh pipeline
	Pipeline mesh_pipeline;
	if(device.hasShader(Shader::TypeTask)) {
		mesh_pipeline = device.createPipeline();
		mesh_pipeline.setUniformMask(0, Shader::MaskTask | Shader::MaskMesh);
		mesh_pipeline.setStorageMasks(0, 2, Shader::MaskMesh);
		mesh_pipeline.setColorFormat(window.getColorFormat());
		mesh_pipeline.setDepthFormat(window.getDepthFormat());
		mesh_pipeline.setDepthFunc(Pipeline::DepthFuncLessEqual);
		if(!mesh_pipeline.loadShaderGLSL(Shader::TypeTask, "main.shader", "TASK_SHADER=1; GRID_SIZE=%uu", grid_size)) return 1;
		if(!mesh_pipeline.loadShaderGLSL(Shader::TypeMesh, "main.shader", "MESH_SHADER=1")) return 1;
		if(!mesh_pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "FRAGMENT_SHADER=1")) return 1;
		if(!mesh_pipeline.create()) return 1;
	}
	
	// load mesh
	Mesh mesh;
	if(!mesh.load("model.dae")) return 1;
	
	// create tessellation model
	MeshModel tessellation_model;
	if(!tessellation_model.create(device, tessellation_pipeline, mesh, MeshModel::FlagVerbose)) return 1;
	
	// create mesh model
	MeshModel mesh_model;
	if(mesh_pipeline && !mesh_model.create(device, tessellation_pipeline, mesh, MeshModel::FlagVerbose | MeshModel::FlagBufferStorage)) return 1;
	
	// create target
	Target target = device.createTarget(window);
	
	// current mode
	const char *mode = "";
	
	// main loop
	DECLARE_GLOBAL
	window.run([&]() {
		DECLARE_COMMON
		
		Window::update();
		
		if(!window.render()) return false;
		
		// window title
		if(fps > 0.0f) window.setTitle(String::format("%s%s %.1f FPS", title.get(), mode, fps));
		
		// window target
		target.setClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		target.begin();
		{
			// create command list
			Command command = device.createCommand(target);
			
			// common parameters
			CommonParameters common_parameters;
			common_parameters.camera = Matrix4x4f::rotateZ(time * 4.0f) * Vector4f(48.0f, 0.0f, 24.0f, 1.0f);
			common_parameters.projection = Matrix4x4f::perspective(60.0f, (float32_t)window.getWidth() / window.getHeight(), 0.1f, 1000.0f);
			common_parameters.modelview = Matrix4x4f::lookAt(Vector3f(common_parameters.camera), Vector3f::zero, Vector3f::oneZ);
			common_parameters.transform = Matrix4x4f::rotateZ(time * 32.0f);
			common_parameters.time = time;
			if(target.isFlipped()) common_parameters.projection = Matrix4x4f::scale(1.0f, -1.0f, 1.0f) * common_parameters.projection;
			
			// mesh mode
			if(mesh_pipeline && (window.getKeyboardKey('1') || !tessellation_pipeline.isCreated())) {
				command.setPipeline(mesh_pipeline);
				command.setStorageBuffers(0, { mesh_model.getVertexBuffer(), mesh_model.getIndexBuffer() });
				uint32_t num_meshes = grid_size * grid_size * grid_size;
				uint32_t max_meshes = device.getFeatures().maxTaskMeshes;
				for(uint32_t i = 0; i < num_meshes; i += max_meshes) {
					uint32_t num = min(num_meshes - i, max_meshes);
					common_parameters.index = i;
					command.setUniform(0, common_parameters);
					if(window.getKeyboardKey('i')) {
						command.setIndirect(Command::DrawMeshIndirect { num, 1, 1 });
						command.drawMeshIndirect(1);
						mode = " Mesh Indirect";
					} else {
						command.drawMesh(num);
						mode = " Mesh";
					}
				}
			}
			// tessellation mode
			else if(tessellation_pipeline.isCreated()) {
				command.setPipeline(tessellation_pipeline);
				command.setUniform(0, common_parameters);
				tessellation_model.setBuffers(command);
				tessellation_model.drawInstanced(command, 0, grid_size * grid_size * grid_size);
				mode = "";
			}
		}
		target.end();
		
		if(!window.present()) return false;
		
		if(!device.check()) return false;
		
		return true;
	});
	
	// finish context
	window.finish();
	
	return 0;
}
