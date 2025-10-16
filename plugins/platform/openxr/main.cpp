// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <common/common.h>
#include <core/TellusimPointer.h>
#include <math/TellusimRandom.h>
#include <format/TellusimMesh.h>
#include <platform/TellusimDevice.h>
#include <platform/TellusimCommand.h>
#include <platform/TellusimPipeline.h>
#include <graphics/TellusimMeshModel.h>
#include <interface/TellusimCanvas.h>
#include <interface/TellusimControls.h>

#include "include/TellusimXRInput.h"
#include "include/TellusimXRWindow.h"

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	App app(argc, argv);
	if(!app.create()) return 1;
	
	// create window
	auto xr_window = makeAutoPtr(new XRWindow(app.getPlatform(), app.getDevice()));
	Window &window = xr_window.ref();
	DECLARE_WINDOW_CALLBACKS
	
	String title = String::format("%s Tellusim::XRWindow", window.getPlatformName());
	DECLARE_WINDOW_CREATE(title)
	
	// left controller
	XRInput left_input;
	if(!left_input.create(xr_window.get(), XRInput::HandLeft)) return 1;
	uint32_t l_aim_id = left_input.addMatrix4x3f(XRInput::InputAim, XRInput::ProfileOculus);
	uint32_t l_offset_id = left_input.addVector2f(XRInput::InputThumb, XRInput::ProfileOculus);
	uint32_t l_trigger_id = left_input.addScalarf32(XRInput::InputTrigger, XRInput::ProfileOculus);
	uint32_t l_squeeze_id = left_input.addScalarf32(XRInput::InputSqueeze, XRInput::ProfileOculus);
	uint32_t l_button_id = left_input.addBool(XRInput::InputX, XRInput::ProfileOculus);
	
	// right controller
	XRInput right_input;
	if(!right_input.create(xr_window.get(), XRInput::HandRight)) return 1;
	uint32_t r_aim_id = right_input.addMatrix4x3f(XRInput::InputAim, XRInput::ProfileOculus);
	uint32_t r_offset_id = right_input.addVector2f(XRInput::InputThumb, XRInput::ProfileOculus);
	uint32_t r_trigger_id = right_input.addScalarf32(XRInput::InputTrigger, XRInput::ProfileOculus);
	uint32_t r_squeeze_id = right_input.addScalarf32(XRInput::InputSqueeze, XRInput::ProfileOculus);
	uint32_t r_button_id = right_input.addBool(XRInput::InputA, XRInput::ProfileOculus);
	
	// OpenXR instance info
	const auto &properties = XR::getProperties();
	TS_LOGF(Verbose, "Layers: %s\n", XR::getLayers().get());
	TS_LOGF(Verbose, "Extensions: %s\n", XR::getExtensions().get());
	TS_LOGF(Verbose, "Runtime Name: %s\n", properties.runtimeName);
	TS_LOGF(Verbose, "Runtime Version: %u.%u.%u\n", XR_VERSION_MAJOR(properties.runtimeVersion), XR_VERSION_MINOR(properties.runtimeVersion), XR_VERSION_PATCH(properties.runtimeVersion));		
	TS_LOGF(Verbose, "Window: %s %ux%u\n", window.getPlatformName(), window.getWidth(), window.getHeight());
	TS_LOGF(Verbose, "Color Format: %s\n", getFormatName(window.getColorFormat()));
	TS_LOGF(Verbose, "Depth Format: %s\n", getFormatName(window.getDepthFormat()));
	TS_LOGF(Verbose, "Swap Chains: %u\n", xr_window->getNumSwapChains());
	
	// OpenXR system info
	TS_LOGF(Verbose, "Systems: %u\n", XR::getNumSystems());
	for(uint32_t i = 0; i < XR::getNumSystems(); i++) {
		
		XRSystem *system = XR::getSystem(i);
		
		// system properties;
		const auto &properties = system->getProperties();
		TS_LOGF(Verbose, "System Name: %s\n", properties.systemName);
		TS_LOGF(Verbose, "System Vendor: 0x%x\n", properties.vendorId);
		TS_LOGF(Verbose, "Oritation Tracking: %u\n", properties.trackingProperties.orientationTracking);
		TS_LOGF(Verbose, "Position Tracking: %u\n", properties.trackingProperties.positionTracking);
		
		// view configurations
		for(uint32_t i = 0; i < system->getNumViewTypes(); i++) {
			String view_info;
			XrViewConfigurationType type = system->getViewType(i);
			if(type == XR_VIEW_CONFIGURATION_TYPE_PRIMARY_MONO) view_info = "Primary Mono";
			else if(type == XR_VIEW_CONFIGURATION_TYPE_PRIMARY_STEREO) view_info = "Primary Stereo";
			else if(type == XR_VIEW_CONFIGURATION_TYPE_PRIMARY_QUAD_VARJO) view_info = "Primary Quad VARJO";
			else if(type == XR_VIEW_CONFIGURATION_TYPE_SECONDARY_MONO_FIRST_PERSON_OBSERVER_MSFT) view_info = "Secondary Mono FPO MSFT";
			else view_info = String::fromu32(type);
			if(system->getViewModes(i)) {
				view_info += ":";
				for(const auto &view : system->getViewModes(i)) {
					view_info += String::format(" (%ux%u %ux)", view.recommendedImageRectWidth, view.recommendedImageRectHeight, view.recommendedSwapchainSampleCount);
				}
			}
			TS_LOGF(Verbose, "%s\n", view_info.get());
		}
		
		// reference space types
		String space_types;
		for(XrReferenceSpaceType type : system->getSpaceTypes()) {
			if(space_types) space_types += ", ";
			if(type == XR_REFERENCE_SPACE_TYPE_VIEW) space_types += "View";
			else if(type == XR_REFERENCE_SPACE_TYPE_LOCAL) space_types += "Local";
			else if(type == XR_REFERENCE_SPACE_TYPE_STAGE) space_types += "Stage";
			else if(type == XR_REFERENCE_SPACE_TYPE_UNBOUNDED_MSFT) space_types += "Unbounded MSFT";
			else if(type == XR_REFERENCE_SPACE_TYPE_COMBINED_EYE_VARJO) space_types += "Combined Eye VARJO";
			else space_types = String::fromu32(type);
		}
		TS_LOGF(Verbose, "Space Types: %s\n", space_types.get());
		
		// swap chain formats
		String formats;
		for(int64_t format : system->getFormats()) {
			formats += (formats) ? ", 0x" : "0x";
			formats += String::fromi64(format, 16);
		}
		TS_LOGF(Verbose, "Formats: %s\n", formats.get());
	}
	
	// scene size
	constexpr uint32_t width = 24;
	constexpr uint32_t height = 24;
	constexpr uint32_t depth = 4;
	
	// structures
	struct Vertex {
		float32_t position[3];
		float32_t normal[3];
	};
	
	struct CommonParameters {
		Matrix4x4f projection;
		Matrix4x4f modelview;
		Matrix4x4f transform;
		Vector4f camera;
	};
	
	// create device
	Device device(window);
	if(!device) return 1;
	
	// create pipeline
	Pipeline pipeline = device.createPipeline();
	pipeline.setUniformMask(0, Shader::MaskVertex);
	pipeline.addAttribute(Pipeline::AttributePosition, FormatRGBf32, 0, offsetof(Vertex, position), sizeof(Vertex));
	pipeline.addAttribute(Pipeline::AttributeNormal, FormatRGBf32, 0, offsetof(Vertex, normal), sizeof(Vertex));
	pipeline.setMultisample(window.getMultisample());
	pipeline.setColorFormat(window.getColorFormat());
	pipeline.setDepthFormat(window.getDepthFormat());
	pipeline.setDepthFunc(Pipeline::DepthFuncGreater);
	if(!pipeline.loadShaderGLSL(Shader::TypeVertex, "main.shader", "VERTEX_SHADER=1")) return 1;
	if(!pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "FRAGMENT_SHADER=1")) return 1;
	if(!pipeline.create()) return 1;
	
	// load mesh
	Mesh mesh;
	if(!mesh.load("model.glb")) return 1;
	
	// create model
	MeshModel model;
	if(!model.create(device, pipeline, mesh)) return 1;
	
	// create canvas
	Canvas canvas;
	canvas.setDepthFunc(Pipeline::DepthFuncGreaterEqual);
	
	// create root control
	ControlRoot root(canvas, true);
	root.getFontStyle().offset.z = -0.002f;
	
	// create panel
	ControlPanel panel(&root);
	panel.setAlign(Control::AlignCenter);
	panel.setPosition(0.0f, 0.0f, -0.004f);
	
	ControlText hello_text(&panel, "Hello OpenXR\n");
	hello_text.setAlign(Control::AlignCenter);
	
	ControlText fps_text(&panel, "FPS: N/A\n");
	fps_text.setAlign(Control::AlignCenter);
	
	ControlText info_text(&panel);
	info_text.setAlign(Control::AlignCenter);
	info_text.setFontSize(10);
	
	// create targets
	Array<Target> targets;
	for(uint32_t i = 0; i < xr_window->getNumSurfaces(); i++) {
		Surface surface = xr_window->getSurface(i);
		Target target = device.createTarget(surface);
		target.setClearColor(Color(0.2f, 0.2f, 0.2f, 1.0f).gammaToLinear());
		target.setClearDepth(0.0f);
		targets.append(target);
	}
	
	// initial orientation
	Matrix4x3f window_transform = Matrix4x3f::zero;
	Matrix4x3f window_itransform = Matrix4x3f::zero;
	
	// initial position
	Vector3f position = Vector3f::zero;
	
	// main loop
	DECLARE_GLOBAL
	window.run([&]() {
		DECLARE_COMMON
		
		Window::update();
		
		if(!window.render()) return false;
		
		// fps value
		if(fps > 0) fps_text.setText(String::format("FPS: %.1f\n", fps));
		
		// camera position
		Vector3f camera = xr_window->getPosition();
		info_text.setText(String::format("x: %6.3f\ny: %6.3f\nz: %6.3f", camera.x, camera.y, camera.z));
		
		// update controls
		root.setViewport(1920.0f, 1080.0f);
		while(root.update(canvas.getScale(targets[0]))) { }
		
		// create canvas
		canvas.create(device, targets[0], 200);
		
		// local orientation
		if(window.isFocused() && (window_transform == Matrix4x3f::zero || left_input.getBool(l_button_id))) {
			window_transform = xr_window->getTransform() * Matrix4x3f::rotateX(-90.0f);
			window_itransform = inverse(window_transform);
		}
		
		// navigation
		Matrix4x3f transform = window_itransform * xr_window->getTransform() * Matrix4x3f::rotateX(-90.0f);
		position += transform.getColumn(0) * (right_input.getVector2f(r_offset_id).x * 0.05f);
		position += transform.getColumn(1) * (right_input.getVector2f(r_offset_id).y * 0.05f);
		position += transform.getColumn(2) * (right_input.getScalarf32(r_trigger_id) * 0.05f);
		position -= transform.getColumn(2) * (right_input.getScalarf32(r_squeeze_id) * 0.05f);
		
		// window targets
		for(uint32_t i = 0; i < targets.size() && !window.isMinimized(); i++) {
			
			// common parameters
			CommonParameters common_parameters;
			common_parameters.projection = xr_window->getProjection(i, 0.01f);
			common_parameters.modelview = Matrix4x4f(xr_window->getModelview(i) * window_transform * Matrix4x3f::translate(-position));
			if(targets[i].isFlipped()) common_parameters.projection = Matrix4x4f::scale(1.0f, -1.0f, 1.0f) * common_parameters.projection;
			common_parameters.camera = Vector4f(window_itransform * xr_window->getPosition() + position, 0.0f);
			
			// window target
			targets[i].begin();
			{
				// create command list
				Command command = device.createCommand(targets[i]);
				
				// set pipeline
				command.setPipeline(pipeline);
				
				// set buffers
				model.setBuffers(command);
				
				// draw instances
				Random<> random(0);
				float32_t step = 0.5f;
				Matrix4x4f scale = Matrix4x4f::scale(0.1f);
				for(uint32_t z = 0; z < depth; z++) {
					float32_t Z = (z - (depth - 1) * 0.5f) * step;
					for(uint32_t y = 0; y < height; y++) {
						float32_t Y = (y - (height - 1) * 0.5f) * step;
						for(uint32_t x = 0; x < width; x++) {
							float32_t X = (x - (width - 1) * 0.5f) * step;
							float32_t z = Tellusim::cos(random.getf32(0.5f, 1.0f) * time + random.getf32(0.0f, Pi)) * step * 0.1f;
							common_parameters.transform = Matrix4x4f::translate(X, Y, Z + z) * Matrix4x4f::rotateZ(random.getf32(7.0f, 17.0f) * time) * scale;
							command.setUniform(0, common_parameters);
							model.draw(command);
						}
					}
				}
				
				// left input
				Matrix4x3f left_transform = window_itransform * left_input.getMatrix4x3f(l_aim_id);
				if(left_transform != Matrix4x3f::zero) {
					Vector2f offset = left_input.getVector2f(l_offset_id) * 0.05f;
					float32_t scale = left_input.getScalarf32(l_trigger_id) + 1.0f;
					scale /= left_input.getScalarf32(l_squeeze_id, 1.0f) + 1.0f;
					common_parameters.transform = Matrix4x4f::translate(position) * Matrix4x4f(left_transform) * Matrix4x4f::translate(offset.x, 0.0f, -offset.y) * Matrix4x4f::scale(scale * 0.05f);
					command.setUniform(0, common_parameters);
					model.draw(command);
				}
				
				// right input
				Matrix4x3f right_transform = window_itransform * right_input.getMatrix4x3f(r_aim_id);
				if(right_transform != Matrix4x3f::zero && !right_input.getBool(r_button_id)) {
					Vector2f offset = right_input.getVector2f(r_offset_id) * 0.05f;
					float32_t scale = right_input.getScalarf32(r_trigger_id) + 1.0f;
					scale /= right_input.getScalarf32(r_squeeze_id) + 1.0f;
					common_parameters.transform = Matrix4x4f::translate(position) * Matrix4x4f(right_transform) * Matrix4x4f::translate(offset.x, 0.0f, -offset.y) * Matrix4x4f::scale(scale * 0.05f);
					command.setUniform(0, common_parameters);
					model.draw(command);
				}
				
				// draw canvas
				canvas.setViewport(Viewport(-1.0f, -1.0f, 2.0f, 2.0f, 0.0f, -1.0f));
				Matrix4x4f transform = Matrix4x4f::scale(1.0f / 200.0f, 1.0f / 200.0f, 1.0f) * Matrix4x4f::translate(-1920.0f / 2.0f, -1080.0f / 2.0f, 0.0f);
				if(right_input.getBool(r_button_id)) transform = Matrix4x4f::translate(position) * Matrix4x4f(right_transform) * Matrix4x4f::rotateX(-90.0f) * Matrix4x4f::scale(0.5f) * transform;
				else transform = Matrix4x4f::translate(0.0f, 1.0f, -0.1f) * Matrix4x4f::rotateX(90.0f) * transform;
				canvas.setTransform(common_parameters.projection * common_parameters.modelview * transform);
				canvas.draw(command);
			}
			targets[i].end();
		}
		
		if(!window.present()) return false;
		
		if(!device.check()) return false;
		
		return true;
	});
	
	// finish context
	window.finish();
	
	return 0;
}
