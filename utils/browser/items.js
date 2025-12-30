{
	"Graphics": {
		"graphics_lights": {
			"title": "Clustered Lights",
			"image": "images/graphics/graphics_lights.jpg",
			"text": "Forward shading with 16384 dynamic lights. This algorithm is compatible with deferred shading and transparent objects.",
			"path": "samples/graphics/lights",
			"exec": "main",
			"source": "samples/graphics/lights/main.cpp",
			"project": "samples/graphics/lights/lights"
		},
		"graphics_meshlet": {
			"title": "Meshlet Render",
			"image": "images/graphics/graphics_meshlet.jpg",
			"text": "A massive meshlets rendering example with Mesh Shader for hardware and Compute Shader for software rasterization.<br>'1' activates Instancing mode.<br>'2' activates Mesh Shader mode.<br>'3' activates Compute rasterization mode.",
			"path": "samples/graphics/meshlet",
			"exec": "main",
			"source": "samples/graphics/meshlet/main.cpp",
			"python": "samples/graphics/meshlet/main.py",
			"csharp": "samples/graphics/meshlet/main.cs",
			"rust": "samples/graphics/meshlet/main.rs",
			"project": "samples/graphics/meshlet/meshlet"
		},
		"graphics_traveral": {
			"title": "Mesh RayTracing",
			"image": "images/graphics/graphics_traversal.jpg",
			"text": "Traversal class for the simple raytracing pipeline access. Vulkan or Direct3D12 API is required.",
			"path": "samples/graphics/traversal",
			"exec": "main",
			"source": "samples/graphics/traversal/main.cpp",
			"project": "samples/graphics/traversal/traversal"
		},
		"graphics_tracing": {
			"title": "Mesh RayQuery",
			"image": "images/graphics/graphics_tracing.jpg",
			"text": "Ray Query raytracing of animated scene. Vulkan, Direct3D12, or Metal API is required.<br>'1' activates Fragment Shader raytracing (if available).",
			"path": "samples/graphics/tracing",
			"exec": "main",
			"source": "samples/graphics/tracing/main.cpp",
			"python": "samples/graphics/tracing/main.py",
			"csharp": "samples/graphics/tracing/main.cs",
			"rust": "samples/graphics/tracing/main.rs",
			"project": "samples/graphics/tracing/tracing"
		},
		"graphics_skinned_tracing": {
			"title": "Hardware RayTracing",
			"image": "images/graphics/graphics_skinned_tracing.jpg",
			"text": "Hardware accelerated RayTracing of animated objects.",
			"path": "samples/graphics/skinned_tracing",
			"exec": "main",
			"source": "samples/graphics/skinned_tracing/main.cpp",
			"project": "samples/graphics/skinned_tracing/skinned_tracing"
		},
		"graphics_skinned_tree": {
			"title": "Compute RayTracing",
			"image": "images/graphics/graphics_skinned_tree.jpg",
			"text": "Compute Shader RayTracing of animated objects.",
			"path": "samples/graphics/skinned_tree",
			"exec": "main",
			"source": "samples/graphics/skinned_tree/main.cpp",
			"project": "samples/graphics/skinned_tree/skinned_tree"
		},
		"graphics_mesh_tracing": {
			"title": "Hardware RayTracing",
			"image": "images/graphics/graphics_mesh_tracing.jpg",
			"text": "Hardware accelerated RayTracing of high-polygonal objects.",
			"path": "samples/graphics/mesh_tracing",
			"exec": "main",
			"source": "samples/graphics/mesh_tracing/main.cpp",
			"project": "samples/graphics/mesh_tracing/mesh_tracing"
		},
		"graphics_mesh_tree": {
			"title": "Compute RayTracing",
			"image": "images/graphics/graphics_mesh_tree.jpg",
			"text": "Compute Shader RayTracing of high-polygonal objects.",
			"path": "samples/graphics/mesh_tree",
			"exec": "main",
			"source": "samples/graphics/mesh_tree/main.cpp",
			"project": "samples/graphics/mesh_tree/mesh_tree"
		},
		"graphics_object_tree": {
			"title": "Compute Traversal",
			"image": "images/graphics/graphics_object_tree.jpg",
			"text": "Compute Shader BVH tree traversal is a key technique in GPU-driven rendering that provides significantly better performance than CPU-based culling.",
			"path": "samples/graphics/object_tree",
			"exec": "main",
			"source": "samples/graphics/object_tree/main.cpp",
			"project": "samples/graphics/object_tree/object_tree"
		},
		"graphics_decoder_jpeg": {
			"title": "JPEG Decoder",
			"image": "images/graphics/graphics_decoder_jpeg.jpg",
			"text": "The DecoderJPEG provides GPU-accelerated JPEG decoding functionality.",
			"path": "samples/graphics/decoder_jpeg",
			"exec": "main",
			"source": "samples/graphics/decoder_jpeg/main.cpp",
			"project": "samples/graphics/decoder_jpeg/decoder_jpeg"
		},
		"graphics_cube_filter": {
			"title": "Cube Filter",
			"image": "images/graphics/graphics_cube_filter.jpg",
			"text": "The CubeFilter interface performs real-time Cube texture filtration.",
			"path": "samples/graphics/cube_filter",
			"exec": "main",
			"source": "samples/graphics/cube_filter/main.cpp",
			"project": "samples/graphics/cube_filter/cube_filter"
		},
		"graphics_separable_filter": {
			"title": "Separable Filter",
			"image": "images/graphics/graphics_separable_filter.png",
			"text": "The SeparableFilter interface helps to create different separable filters like Gaussian, Sobel, Box, and custom weights.",
			"path": "samples/graphics/separable_filter",
			"exec": "main",
			"source": "samples/graphics/separable_filter/main.cpp",
			"project": "samples/graphics/separable_filter/separable_filter"
		},
		"graphics_indirect": {
			"title": "Indirect Draw",
			"image": "images/graphics/graphics_indirect.png",
			"text": "Drawing massive amount of quads using different indirect rendering techniques.",
			"path": "samples/graphics/indirect",
			"exec": "main",
			"source": "samples/graphics/indirect/main.cpp",
			"project": "samples/graphics/indirect/indirect"
		},
		"graphics_geometry": {
			"title": "Geometry Shader",
			"image": "images/graphics/graphics_geometry.jpg",
			"text": "Rendering massive amount of boxes with Geometry Shaders.<br>'1' activates Vertex Shader mode.<br>'2' activates Mesh Shader mode (if available).",
			"path": "samples/graphics/geometry",
			"exec": "main",
			"source": "samples/graphics/geometry/main.cpp",
			"project": "samples/graphics/geometry/geometry"
		},
		"graphics_tessellation": {
			"title": "Tessellation Shader",
			"image": "images/graphics/graphics_tessellation.jpg",
			"text": "Quadrilateral tessellation with Control + Evaluate or Mesh Shaders.<br>'1' activates Mesh Shader tessellation mode (if available).",
			"path": "samples/graphics/tessellation",
			"exec": "main",
			"source": "samples/graphics/tessellation/main.cpp",
			"project": "samples/graphics/tessellation/tessellation"
		},
		"graphics_transparency": {
			"title": "Ordered Independent Transparency",
			"image": "images/graphics/graphics_transparency.png",
			"text": "Ordered Independent Transparency with atomic buffer operations from the fragment shader.",
			"path": "samples/graphics/transparency",
			"exec": "main",
			"source": "samples/graphics/transparency/main.cpp",
			"project": "samples/graphics/transparency/transparency"
		},
		"graphics_shadow_tracing": {
			"title": "Hardware Ray Tracing Shadows",
			"image": "images/graphics/graphics_shadow_tree.png",
			"text": "Hardware raytracing shadows with simple deferred shading. An API with Ray Query support is required.",
			"path": "samples/graphics/shadow_tracing",
			"exec": "main",
			"source": "samples/graphics/shadow_tracing/main.cpp",
			"project": "samples/graphics/shadow_tracing/shadow_tracing"
		},
		"graphics_shadow_tree": {
			"title": "Software Ray Tracing Shadows",
			"image": "images/graphics/graphics_shadow_tree.png",
			"text": "Software raytracing shadows with simple deferred shading. Compatible with all APIs.",
			"path": "samples/graphics/shadow_tree",
			"exec": "main",
			"source": "samples/graphics/shadow_tree/main.cpp",
			"project": "samples/graphics/shadow_tree/shadow_tree"
		},
		"graphics_shadow_pcf": {
			"title": "Percentage Closer Filtering Shadow Map",
			"image": "images/graphics/graphics_shadow_pcf.png",
			"text": "PCF Shadow Maps provides shadow with variable penumbra size based on the distance between the shadow caster and receiver.",
			"path": "samples/graphics/shadow_pcf",
			"exec": "main",
			"source": "samples/graphics/shadow_pcf/main.cpp",
			"project": "samples/graphics/shadow_pcf/shadow_pcf"
		},
		"graphics_shadow_esm": {
			"title": "Exponential Shadow Maps",
			"image": "images/graphics/graphics_shadow_esm.png",
			"text": "Exponential Shadow Maps provides noise-free shadows with a fixed performance cost and constant penumbra size.",
			"path": "samples/graphics/shadow_esm",
			"exec": "main",
			"source": "samples/graphics/shadow_esm/main.cpp",
			"project": "samples/graphics/shadow_esm/shadow_esm"
		},
		"graphics_parallax_2d": {
			"title": "Parallax 2D",
			"image": "images/graphics/graphics_parallax_2d.png",
			"text": "Parallax occlusion mapping with self-shadowing for the mesh geometry.",
			"path": "samples/graphics/parallax_2d",
			"exec": "main",
			"source": "samples/graphics/parallax_2d/main.cpp",
			"project": "samples/graphics/parallax_2d/parallax_2d"
		},
		"graphics_parallax_cube": {
			"title": "Parallax Cube",
			"image": "images/graphics/graphics_parallax_cube.png",
			"text": "Parallax occlusion mapping with self-shadowing for the analytical sphere.",
			"path": "samples/graphics/parallax_cube",
			"exec": "main",
			"source": "samples/graphics/parallax_cube/main.cpp",
			"project": "samples/graphics/parallax_cube/parallax_cube"
		},
		"graphics_tangent": {
			"title": "Mesh Tangent Basis",
			"image": "images/graphics/graphics_tangent.png",
			"text": "Mesh tangent basis renormalization at the Fragment Shader. Mesh class can re-create normal and tangent vectors.",
			"path": "samples/graphics/tangent",
			"exec": "main",
			"source": "samples/graphics/tangent/main.cpp",
			"project": "samples/graphics/tangent/tangent"
		},
		"graphics_model": {
			"title": "Mesh Model",
			"image": "images/graphics/graphics_model.png",
			"text": "MeshModel class creates a rendering model representation for the input Mesh or MeshGeometry with a specified Pipeline layout.<br>It is possible to inherit MeshModel class and combine multiple meshes into the single Buffer.",
			"path": "samples/graphics/model",
			"exec": "main",
			"source": "samples/graphics/model/main.cpp",
			"python": "samples/graphics/model/main.py",
			"project": "samples/graphics/model/model"
		},
		"graphics_morph": {
			"title": "Mesh Morphing",
			"image": "images/graphics/graphics_morph.png",
			"text": "This is a basic morph mesh animation example. AttributeIndex provides a stable mapping between source and optimized vertices. Texel Buffer acts as a workaround for platforms that lack compute shader support.",
			"path": "samples/graphics/morph",
			"exec": "main",
			"source": "samples/graphics/morph/main.cpp",
			"project": "samples/graphics/morph/morph"
		},
		"graphics_skinned": {
			"title": "Mesh Skinning",
			"image": "images/graphics/graphics_skinned.png",
			"text": "This is a basic skinned mesh animation example. Mesh classes give comprehensive access to all mesh data, including Nodes, Animations, Materials, Cameras, and Lights.",
			"path": "samples/graphics/skinned",
			"exec": "main",
			"source": "samples/graphics/skinned/main.cpp",
			"python": "samples/graphics/skinned/main.py",
			"project": "samples/graphics/skinned/skinned"
		},
		"graphics_multi_window": {
			"title": "Multi Window",
			"image": "images/graphics/graphics_multi_window.png",
			"text": "Rendering scene into multiple borderless windows.",
			"path": "samples/graphics/multi_window",
			"exec": "main",
			"source": "samples/graphics/multi_window/main.cpp",
			"project": "samples/graphics/multi_window/multi_window"
		},
		"graphics_line": {
			"title": "Line Rendering",
			"image": "images/graphics/graphics_line.png",
			"text": "Simple antialiased line rendering. The Vertex shader creates a screen-aligned billboard, and the fragment shader calculates the distance to the line.",
			"path": "samples/graphics/line",
			"exec": "main",
			"source": "samples/graphics/line/main.cpp",
			"project": "samples/graphics/line/line"
		}
	},
	"Platform": {
		"platform_precision": {
			"title": "Platform Precision",
			"image": "images/platform/platform_precision.jpg",
			"text": "Performance and precision difference between 16-bit, 32-bit, and 64-bit floating formats.<br>'1' activates 64-bit precision.<br>'2' activates 16-bit precision.",
			"path": "samples/platform/precision",
			"exec": "main",
			"source": "samples/platform/precision/main.cpp",
			"project": "samples/platform/precision/precision"
		},
		"platform_bindless": {
			"title": "Platform Bindless",
			"image": "images/platform/platform_bindless.jpg",
			"text": "This example demonstrates bindless Buffer and Texture resources indexed by InstanceIndex. Vulkan, Direct3D12, or Metal API is required.",
			"path": "samples/platform/bindless",
			"exec": "main",
			"source": "samples/platform/bindless/main.cpp",
			"project": "samples/platform/bindless/bindless"
		},
		"platform_table": {
			"title": "Platform TextureTable",
			"image": "images/platform/platform_table.png",
			"text": "TextureTable is an interface for an unlimited number of bindless textures that can be accessed from any shader by uniform or non-uniform index. Vulkan, Direct3D12, or Metal API is required.",
			"path": "samples/platform/table",
			"exec": "main",
			"source": "samples/platform/table/main.cpp",
			"project": "samples/platform/table/table"
		},
		"platform_texel": {
			"title": "Platform Texel",
			"image": "images/platform/platform_texel.png",
			"text": "Texel buffer provides cached buffer access that is compatible with OpenGLES platform. Moreover, it can work faster than the Storage buffer in some scenarios.",
			"path": "samples/platform/texel",
			"exec": "main",
			"source": "samples/platform/texel/main.cpp",
			"project": "samples/platform/texel/texel"
		},
		"platform_texture": {
			"title": "Platform Texture",
			"image": "images/platform/platform_texture.png",
			"text": "Dynamic 3D texture created with SIMD CPU instructions.",
			"path": "samples/platform/texture",
			"exec": "main",
			"source": "samples/platform/texture/main.cpp",
			"project": "samples/platform/texture/texture"
		},
		"platform_command": {
			"title": "Platform Command",
			"image": "images/platform/platform_command.png",
			"text": "Command class for basic rendering. Depth Cube texture for omnidirectional shadow map.",
			"path": "samples/platform/command",
			"exec": "main",
			"source": "samples/platform/command/main.cpp",
			"project": "samples/platform/command/command"
		},
		"platform_tracing": {
			"title": "Platform Tracing",
			"image": "images/platform/platform_tracing.png",
			"text": "Hardware accelerated raytracing shadows. An API with Ray Query support is required.",
			"path": "samples/platform/tracing",
			"exec": "main",
			"source": "samples/platform/tracing/main.cpp",
			"project": "samples/platform/tracing/tracing"
		},
		"platform_compute": {
			"title": "Platform Compute",
			"image": "images/platform/platform_compute.jpg",
			"text": "Compute class for simple compute shader texture generation.",
			"path": "samples/platform/compute",
			"exec": "main",
			"source": "samples/platform/compute/main.cpp",
			"python": "samples/platform/compute/main.py",
			"project": "samples/platform/compute/compute"
		},
		"platform_fence": {
			"title": "Platform Fence",
			"image": "images/platform/platform_fence.png",
			"text": "Multi-GPU N-body simulation with Fence synchronization. A shared buffer is used for data exchange between GPUs.",
			"path": "samples/platform/fence",
			"exec": "main",
			"source": "samples/platform/fence/main.cpp",
			"project": "samples/platform/fence/fence"
		},
		"platform_shared": {
			"title": "Platform Fence",
			"image": "images/platform/platform_shared.png",
			"text": "Multi-GPU synchronization with fences and semaphores.",
			"path": "samples/platform/shared",
			"exec": "main",
			"source": "samples/platform/shared/main.cpp",
			"project": "samples/platform/shared/shared"
		},
		"platform_sparse": {
			"title": "Platform Sparse",
			"image": "images/platform/platform_sparse.jpg",
			"text": "This example shows how sparse textures allow handling very large textures by allocating only the needed tiles in GPU memory",
			"path": "samples/platform/sparse",
			"exec": "main",
			"source": "samples/platform/sparse/main.cpp",
			"project": "samples/platform/sparse/sparse"
		},
		"platform_mapped": {
			"title": "Platform Mapped",
			"image": "images/platform/platform_mapped.jpg",
			"text": "This example shows how Vulkan can map files into GPU buffers, allowing the GPU to read from and write to files directly without extra copying.",
			"path": "samples/platform/mapped",
			"exec": "main",
			"source": "samples/platform/mapped/main.cpp",
			"project": "samples/platform/mapped/mapped"
		},
		"platform_formats": {
			"title": "Platform Formats",
			"image": "images/platform/platform_formats.jpg",
			"text": "This example shows how mixed texture formats can reduce video memory consumption. Image format conversion is performed by the Image interface.",
			"path": "samples/platform/formats",
			"exec": "main",
			"source": "samples/platform/formats/main.cpp",
			"project": "samples/platform/formats/formats"
		},
		"platform_dynamic": {
			"title": "Platform Dynamic",
			"image": "images/platform/platform_dynamic.jpg",
			"text": "A single-thread dynamic geometry rendering can provide more than 100M triangles per second rate.",
			"path": "samples/platform/dynamic",
			"exec": "main",
			"source": "samples/platform/dynamic/main.cpp",
			"project": "samples/platform/dynamic/dynamic"
		},
		"platform_clipping": {
			"title": "Platform Clip Planes",
			"image": "images/platform/platform_clipping.png",
			"text": "Vertex Shader clip distance output is useful for arbitrary geometry culling.",
			"path": "samples/platform/clipping",
			"exec": "main",
			"source": "samples/platform/clipping/main.cpp",
			"project": "samples/platform/clipping/clipping"
		},
		"platform_stencil": {
			"title": "Platform Stencil Buffer",
			"image": "images/platform/platform_stencil.png",
			"text": "Constructive Solid Geometry with the Stencil Buffer. This algorithm is compatible with procedural geometry.",
			"path": "samples/platform/stencil",
			"exec": "main",
			"source": "samples/platform/stencil/main.cpp",
			"project": "samples/platform/stencil/stencil"
		},
		"platform_fusion": {
			"title": "Platform Fusion",
			"image": "images/platform/platform_fusion.png",
			"text": "Fusion API allows replicating all commands and resources across multiple physical or logical devices. It dramatically simplifies the development of apps for multi-GPU or multi-channel rendering.",
			"path": "samples/platform/fusion",
			"exec": "main",
			"source": "samples/platform/fusion/main.cpp",
			"project": "samples/platform/fusion/fusion"
		},
		"platform_layers": {
			"title": "Platform Layers",
			"image": "images/platform/platform_layers.jpg",
			"text": "Demonstrates multilayer rendering where the target layer is selected dynamically in the Vertex Shader, Geometry Shader, or Geometry Passthrough Shader.",
			"path": "samples/platform/layers",
			"exec": "main",
			"source": "samples/platform/layers/main.cpp",
			"project": "samples/platform/layers/layers"
		},
		"platform_viewports": {
			"title": "Platform Viewports",
			"image": "images/platform/platform_viewports.jpg",
			"text": "Demonstrates multi-viewport rendering with dynamic viewport selection in the Vertex Shader, Geometry Shader, or Geometry Passthrough Shader.",
			"path": "samples/platform/viewports",
			"exec": "main",
			"source": "samples/platform/viewports/main.cpp",
			"project": "samples/platform/viewports/viewports"
		},
		"platform_samplers": {
			"title": "Platform Samplers",
			"image": "images/platform/platform_samplers.png",
			"text": "Demonstrates various texture sampler configuration modes.",
			"path": "samples/platform/samplers",
			"exec": "main",
			"source": "samples/platform/samplers/main.cpp",
			"project": "samples/platform/samplers/viewports"
		},
		"platform_barycentric": {
			"title": "Barycentric Coordinates",
			"image": "images/platform/platform_barycentric.png",
			"text": "Build-in barycentric coordinate input is available in Vulkan, Direct3D12, and Metal APIs.",
			"path": "samples/platform/barycentric",
			"exec": "main",
			"source": "samples/platform/barycentric/main.cpp",
			"project": "samples/platform/barycentric/barycentric"
		},
		"platform_indirect": {
			"title": "Multi Draw Indirect",
			"image": "images/platform/platform_indirect.png",
			"text": "This example performs MDI rendering of different objects.",
			"path": "samples/platform/indirect",
			"exec": "main",
			"source": "samples/platform/indirect/main.cpp",
			"project": "samples/platform/indirect/indirect"
		},
		"platform_divisor": {
			"title": "Vertex Attribute Divisor",
			"image": "images/platform/platform_divisor.png",
			"text": "This example demonstrates the use of a vertex attribute divisor to fetch per-draw data.",
			"path": "samples/platform/divisor",
			"exec": "main",
			"source": "samples/platform/divisor/main.cpp",
			"project": "samples/platform/divisor/divisor"
		},
		"platform_alpha": {
			"title": "MSAA Alpha Test",
			"image": "images/platform/platform_alpha.png",
			"text": "MSAA-compatible alpha test in comparison to hardware alpha to coverage.",
			"path": "samples/platform/alpha",
			"exec": "main",
			"source": "samples/platform/alpha/main.cpp",
			"project": "samples/platform/alpha/alpha"
		},
		"platform_blending": {
			"title": "Input Blending Color",
			"image": "images/platform/platform_blending.png",
			"text": "Blending color parameter defines uniform value for blending operations.",
			"path": "samples/platform/blending",
			"exec": "main",
			"source": "samples/platform/blending/main.cpp",
			"project": "samples/platform/blending/blending"
		},
		"platform_multisample": {
			"title": "Multisample Antialiasing",
			"image": "images/platform/platform_multisample.png",
			"text": "This example performs AA line rendering into MSAA texture.",
			"path": "samples/platform/multisample",
			"exec": "main",
			"source": "samples/platform/multisample/main.cpp",
			"project": "samples/platform/multisample/multisample"
		},
		"platform_preprocessor": {
			"title": "Platform Preprocessor",
			"image": "images/platform/platform_preprocessor.png",
			"text": "This example demonstrates how to use the #include preprocessor directive to declare generic functions.",
			"path": "samples/platform/preprocessor",
			"exec": "main",
			"source": "samples/platform/preprocessor/main.cpp",
			"project": "samples/platform/preprocessor/preprocessor"
		},
		"platform_samples": {
			"title": "Platform Texture Samples",
			"image": "images/platform/platform_samples.png",
			"text": "Writing and reading individual multisample texture samples with active Pipeline sample write mask.",
			"path": "samples/platform/samples",
			"exec": "main",
			"source": "samples/platform/samples/main.cpp",
			"project": "samples/platform/samples/samples"
		},
		"platform_conservative": {
			"title": "Conservative Rasterization",
			"image": "images/platform/platform_conservative.png",
			"text": "Hardware conservative rasterization.",
			"path": "samples/platform/conservative",
			"exec": "main",
			"source": "samples/platform/conservative/main.cpp",
			"project": "samples/platform/conservative/conservative"
		},
		"platform_cooperative": {
			"title": "Cooperative Matrix (Tensor Cores)",
			"image": "images/platform/platform_cooperative.png",
			"text": "Cooperative matrix example.",
			"path": "samples/platform/cooperative",
			"exec": "main",
			"source": "samples/platform/cooperative/main.cpp",
			"project": "samples/platform/cooperative/cooperative"
		},
		"platform_matrix": {
			"title": "Matrix Multiplication",
			"image": "images/platform/platform_matrix.png",
			"text": "Matrix multiplication example.",
			"path": "samples/platform/matrix",
			"exec": "main",
			"source": "samples/platform/matrix/main.cpp",
			"project": "samples/platform/matrix/matrix"
		},
		"platform_subgroup": {
			"title": "Subgroup operations",
			"image": "images/platform/platform_subgroup.png",
			"text": "Shader subgroup operations.",
			"path": "samples/platform/subgroup",
			"exec": "main",
			"source": "samples/platform/subgroup/main.cpp",
			"project": "samples/platform/subgroup/subgroup"
		},
		"platform_reference": {
			"title": "Structure references",
			"image": "images/platform/platform_reference.png",
			"text": "This test showcases GLSL structure mapping to raw SSBO buffer, enabling storage of data with different layouts within a single SSBO buffer.",
			"path": "samples/platform/reference",
			"exec": "main",
			"source": "samples/platform/reference/main.cpp",
			"project": "samples/platform/reference/reference"
		},
		"platform_printf": {
			"title": "Shader Printf",
			"image": "images/platform/platform_printf.png",
			"text": "A simple preprocessor-based printf() functionality for compute shaders that work with all APIs.",
			"path": "samples/platform/printf",
			"exec": "main",
			"source": "samples/platform/printf/main.cpp",
			"project": "samples/platform/printf/printf"
		}
	},
	"Interface": {
		"interface_canvas": {
			"title": "Interface Canvas",
			"image": "images/interface/interface_canvas.png",
			"text": "Different CanvasElement classes, including texture filtration, gradients, contour outlines, and SVG rendering.",
			"path": "samples/interface/canvas",
			"exec": "main",
			"source": "samples/interface/canvas/main.cpp",
			"project": "samples/interface/canvas/canvas"
		},
		"interface_controls": {
			"title": "Interface Controls",
			"image": "images/interface/interface_controls.png",
			"text": "Different User Interface Control classes in resolution-independent configuration.",
			"path": "samples/interface/controls",
			"exec": "main",
			"source": "samples/interface/controls/main.cpp",
			"project": "samples/interface/controls/controls"
		},
		"interface_svg_plugins": {
			"title": "SVG",
			"image": "images/plugins/interface_svg.png",
			"text": "This plugin enables SVG images support for Control widgets.<br><a href=\"https://docs.tellusim.com/core/plugins/interface/svg\" target=\"_blank\">docs.tellusim.com/core/plugins/interface/svg</a>",
			"path": "plugins/interface/svg",
			"exec": "main",
			"source": "plugins/interface/svg/main.cpp",
			"project": "plugins/interface/svg/svg"
		},
		"interface_flow": {
			"title": "Flow",
			"image": "images/plugins/interface_flow.png",
			"text": "Flow Control is a universal node-based editor designed for a variety of applications, including material and logic editing. It includes base implementations in both GLSL and C++.<br><a href=\"https://docs.tellusim.com/core/plugins/interface/flow\" target=\"_blank\">docs.tellusim.com/core/plugins/interface/flow</a>",
			"path": "plugins/interface/flow",
			"exec": "main",
			"source": "plugins/interface/flow/main.cpp",
			"project": "plugins/interface/flow/flow"
		},
		"interface_color": {
			"title": "Color",
			"image": "images/plugins/interface_color.png",
			"text": "Color selector control.<br><a href=\"https://docs.tellusim.com/core/plugins/interface/color\" target=\"_blank\">docs.tellusim.com/core/plugins/interface/color</a>",
			"path": "plugins/interface/color",
			"exec": "main",
			"source": "plugins/interface/color/main.cpp",
			"project": "plugins/interface/color/color"
		},
		"interface_element": {
			"title": "Interface Element",
			"image": "images/plugins/interface_element.png",
			"text": "A CanvasElement wrapper that allows elements to be rendered and manipulated inside a Controls widgets.<br><a href=\"https://docs.tellusim.com/core/plugins/interface/element\" target=\"_blank\">docs.tellusim.com/core/plugins/interface/element</a>",
			"path": "plugins/interface/element",
			"exec": "main",
			"source": "plugins/interface/element/main.cpp",
			"project": "plugins/interface/element/element"
		},
		"interface_button": {
			"title": "Button",
			"image": "images/plugins/interface_button.png",
			"text": "A generic button controller that uses custom Canvas elements as Control button.<br><a href=\"https://docs.tellusim.com/core/plugins/interface/button\" target=\"_blank\">docs.tellusim.com/core/plugins/interface/button</a>",
			"path": "plugins/interface/button",
			"exec": "main",
			"source": "plugins/interface/button/main.cpp",
			"project": "plugins/interface/button/button"
		},
		"interface_slider": {
			"title": "Slider",
			"image": "images/plugins/interface_slider.png",
			"text": "A generic slider controller that uses custom Canvas elements as Control slider.<br><a href=\"https://docs.tellusim.com/core/plugins/interface/slider\" target=\"_blank\">docs.tellusim.com/core/plugins/interface/slider</a>",
			"path": "plugins/interface/slider",
			"exec": "main",
			"source": "plugins/interface/slider/main.cpp",
			"project": "plugins/interface/slider/slider"
		},
		"interface_plotter": {
			"title": "Plotter",
			"image": "images/plugins/interface_plotter.png",
			"text": "A simple line plotter visualization plugin.<br><a href=\"https://docs.tellusim.com/core/plugins/interface/plotter\" target=\"_blank\">docs.tellusim.com/core/plugins/interface/plotter</a>",
			"path": "plugins/interface/plotter",
			"exec": "main",
			"source": "plugins/interface/plotter/main.cpp",
			"project": "plugins/interface/plotter/plotter"
		},
		"interface_tooltip": {
			"title": "Tooltip",
			"image": "images/plugins/interface_tooltip.png",
			"text": "A generic tooltip Control allows the display of help information over other interface controls.<br><a href=\"https://docs.tellusim.com/core/plugins/interface/tooltip\" target=\"_blank\">docs.tellusim.com/core/plugins/interface/tooltip</a>",
			"path": "plugins/interface/tooltip",
			"exec": "main",
			"source": "plugins/interface/tooltip/main.cpp",
			"project": "plugins/interface/tooltip/tooltip"
		},
		"interface_popup": {
			"title": "Popup",
			"image": "images/plugins/interface_popup.png",
			"text": "This plugin provides support for dynamic popup windows and contextual menus within the interface.",
			"path": "plugins/interface/popup",
			"exec": "main",
			"source": "plugins/interface/popup/main.cpp",
			"project": "plugins/interface/popup/popup"
		},
		"interface_layer": {
			"title": "Interface Layer",
			"image": "images/interface/interface_layer.png",
			"text": "A transparent multilayer Controls with variable background blur.",
			"path": "samples/interface/layer",
			"exec": "main",
			"source": "samples/interface/layer/main.cpp",
			"project": "samples/interface/layer/layer"
		},
		"interface_manipulator": {
			"title": "Manipulator Plugin",
			"image": "images/plugins/interface_manipulator.png",
			"text": "Manipulator is a simple translator and rotator control for the scene editor.<br><a href=\"https://docs.tellusim.com/core/plugins/interface/manipulator\" target=\"_blank\">docs.tellusim.com/core/plugins/interface/manipulator</a>",
			"path": "plugins/interface/manipulator",
			"exec": "main",
			"source": "plugins/interface/manipulator/main.cpp",
			"project": "plugins/interface/manipulator/manipulator"
		},
		"interface_app": {
			"title": "App",
			"image": "images/plugins/interface_app.png",
			"text": "This plugin provides a framework for single-window Control-based applications.<br><a href=\"https://docs.tellusim.com/core/plugins/interface/app\" target=\"_blank\">docs.tellusim.com/core/plugins/interface/app</a>",
			"path": "plugins/interface/app",
			"exec": "main",
			"source": "plugins/interface/app/main.cpp",
			"project": "plugins/interface/app/app"
		},
		"interface_shape": {
			"title": "Shape",
			"image": "images/interface/interface_shape.png",
			"text": "This example renders cubic shape with applied Stroke and Gradient styles.",
			"path": "samples/interface/shape",
			"exec": "main",
			"source": "samples/interface/shape/main.cpp",
			"project": "samples/interface/shape/shape"
		},
		"interface_svg": {
			"title": "SVG Image",
			"image": "images/interface/interface_svg.png",
			"text": "Simple SVG image loading and rendering. CanvasShape class accepts SVG path string as input data.",
			"path": "samples/interface/svg",
			"exec": "main",
			"source": "samples/interface/svg/main.cpp",
			"project": "samples/interface/svg/svg"
		},
		"interface_control": {
			"title": "Custom Control",
			"image": "images/interface/interface_control.png",
			"text": "Custom Controls can be created by simple ControlBase class inheritance. The Control behavior can be completely overridden.",
			"path": "samples/interface/control",
			"exec": "main",
			"source": "samples/interface/control/main.cpp",
			"project": "samples/interface/control/control"
		}
	},
	"Parallel": {
		"parallel_tensor_torch": {
			"title": "Parallel TensorGraph from PyTorch",
			"image": "images/parallel/parallel_tensor_torch.jpg",
			"text": "Simple convolutional autoencoder trained with PyTorch and imported into TensorGraph.",
			"path": "samples/parallel/tensor_torch",
			"exec": "main",
			"source": "samples/parallel/tensor_torch/main.cpp",
			"python": "samples/parallel/tensor_torch/main.py",
			"csharp": "samples/parallel/tensor_torch/main.cs",
			"rust": "samples/parallel/tensor_torch/main.rs",
			"swift": "samples/parallel/tensor_torch/main.swift",
			"project": "samples/parallel/tensor_torch/tensor_torch"
		},
		"parallel_tensor_mnist": {
			"title": "Parallel TensorGraph MNIST Digits Recognition",
			"image": "images/parallel/parallel_tensor_mnist.png",
			"text": "MNIST Digits Recognition using TensorGraph with PyTorch model.",
			"path": "samples/parallel/tensor_mnist",
			"exec": "main",
			"source": "samples/parallel/tensor_mnist/main.cpp",
			"python": "samples/parallel/tensor_mnist/main.py",
			"csharp": "samples/parallel/tensor_mnist/main.cs",
			"rust": "samples/parallel/tensor_mnist/main.rs",
			"swift": "samples/parallel/tensor_mnist/main.swift",
			"project": "samples/parallel/tensor_mnist/tensor_mnist"
		},
		"parallel_fourier_2d": {
			"title": "Parallel Fourier 2D",
			"image": "images/parallel/parallel_fourier_2d.jpg",
			"text": "Image convolution based on Fast Fourier Transformation.",
			"path": "samples/parallel/fourier_2d",
			"exec": "main",
			"source": "samples/parallel/fourier_2d/main.cpp",
			"python": "samples/parallel/fourier_2d/main.py",
			"project": "samples/parallel/fourier_2d/fourier_2d"
		},
		"parallel_fluid_2d": {
			"title": "Parallel Fluid 2D",
			"image": "images/parallel/parallel_fluid_2d.jpg",
			"text": "Simple 2D fluid simulation based on Fast Fourier Transformation.",
			"path": "samples/parallel/fluid_2d",
			"exec": "main",
			"source": "samples/parallel/fluid_2d/main.cpp",
			"python": "samples/parallel/fluid_2d/main.py",
			"project": "samples/parallel/fluid_2d/fluid_2d"
		},
		"parallel_radix_sort": {
			"title": "Parallel Radix Sort",
			"image": "images/parallel/parallel_radix_sort.png",
			"text": "Multiple independent sorting algorithms can be dispatched in parallel. There is no overhead in comparision with the single array sort. Additionally, dispatch parameters can be fetched from the indirect buffer.<br>'1' shows the input data.<br>'2' activates global sort.",
			"path": "samples/parallel/radix_sort",
			"exec": "main",
			"source": "samples/parallel/radix_sort/main.cpp",
			"project": "samples/parallel/radix_sort/radix_sort"
		},
		"parallel_spatial_grid": {
			"title": "Parallel Spatial Grid",
			"image": "images/parallel/parallel_spatial_grid.png",
			"text": "Simple physics simulation with collisions based on the SpatialGrid class. It is the fastest way to collide objects of the same size.",
			"path": "samples/parallel/spatial_grid",
			"exec": "main",
			"source": "samples/parallel/spatial_grid/main.cpp",
			"project": "samples/parallel/spatial_grid/spatial_grid"
		},
		"parallel_spatial_tree": {
			"title": "Parallel Spatial Tree",
			"image": "images/parallel/parallel_spatial_tree.png",
			"text": "Simple physics simulation with collisions based on the SpatialTree class. The SpatialTree allows collision and intersection tests with any primitive inside BVH.",
			"path": "samples/parallel/spatial_tree",
			"exec": "main",
			"source": "samples/parallel/spatial_tree/main.cpp",
			"project": "samples/parallel/spatial_tree/spatial_tree"
		}
	},
	"Geometry": {
		"geometry_reduce": {
			"title": "Mesh Reduce",
			"image": "images/geometry/geometry_reduce.png",
			"text": "MeshReduce is a simple way to simplify input mesh geometry. Simplification preserves all Mesh Attributes, and it is compatible with Skinning Animation.<br>'1' shows the original geometry.",
			"path": "samples/geometry/reduce",
			"exec": "main",
			"source": "samples/geometry/reduce/main.cpp",
			"project": "samples/geometry/reduce/reduce"
		},
		"geometry_refine": {
			"title": "Mesh Refine",
			"image": "images/geometry/geometry_refine.png",
			"text": "MeshRefine refines geometry mesh using Catmull-Clark (for quadrilaterals) or Loop (for triangles) subdivision algorithms. The Crease Attribute allows additional control over the subdivision process.<br>'1' shows the original geometry.",
			"path": "samples/geometry/refine",
			"exec": "main",
			"source": "samples/geometry/refine/main.cpp",
			"project": "samples/geometry/refine/refine"
		}
	},
	"Plugins": {
		"parallel_onnx": {
			"title": "Open Neural Network Exchange",
			"image": "images/plugins/parallel_onnx.png",
			"text": "The ONNX plugin allows loading and running ONNX models with TensorGraph on all platforms and APIs.<br><a href=\"https://docs.tellusim.com/core/plugins/parallel/onnx\" target=\"_blank\">docs.tellusim.com/core/plugins/parallel/onnx</a>",
			"path": "plugins/parallel/onnx",
			"exec": "main",
			"source": "plugins/parallel/onnx/main.cpp",
			"project": "plugins/parallel/onnx/tensor_mnist"
		},
		"platform_openxr": {
			"title": "OpenXR",
			"image": "images/plugins/platform_openxr.png",
			"text": "OpenXR VR/AR plugin. Supports Vulkan, Direct3D12, Direct3D11, OpenGL APIs on PC; Vulkan, OpenGLES on Android. This plugin creates an OpenXR-compatible output window with any number of channels. The input layer provides a simplified API for the OpenXR input system.<br><a href=\"https://docs.tellusim.com/core/plugins/platform/openxr\" target=\"_blank\">docs.tellusim.com/core/plugins/platform/openxr</a>",
			"path": "plugins/platform/openxr",
			"exec": "main",
			"readme": "plugins/platform/openxr/Readme.txt",
			"source": "plugins/platform/openxr/main.cpp",
			"project": "plugins/platform/openxr/openxr"
		},
		"platform_cuda": {
			"title": "Native Cuda driver API",
			"image": "images/plugins/platform_cuda.jpg",
			"text": "Create dynamic geometry with Cuda and render with Vulkan / Direct3D / OpenGL.<br><a href=\"https://docs.tellusim.com/core/plugins/platform/cuda\" target=\"_blank\">docs.tellusim.com/core/plugins/platform/cuda</a>",
			"path": "plugins/platform/cuda",
			"exec": "main",
			"source": "plugins/platform/cuda/main.cpp",
			"project": "plugins/platform/cuda/cuda"
		},
		"platform_vulkan": {
			"title": "Native Vulkan runtime",
			"image": "images/plugins/platform_vulkan.png",
			"text": "You can use this plugin to write applications with native Vulkan API. All Tellusim platform classes give access to internal Vulkan handlers and can be used in Vulkan API calls.<br><a href=\"https://docs.tellusim.com/core/plugins/platform/vulkan\" target=\"_blank\">docs.tellusim.com/core/plugins/platform/vulkan</a>",
			"path": "plugins/platform/vulkan",
			"exec": "main",
			"source": "plugins/platform/vulkan/main.cpp",
			"project": "plugins/platform/vulkan/vulkan"
		},
		"platform_gl": {
			"title": "Native OpenGL runtime",
			"image": "images/plugins/platform_opengl.png",
			"text": "This plugin provides access to all OpenGL core functions. OpenGL API calls can be utilized when necessary.<br><a href=\"https://docs.tellusim.com/core/plugins/platform/opengl\" target=\"_blank\">docs.tellusim.com/core/plugins/platform/opengl</a>",
			"path": "plugins/platform/opengl",
			"exec": "main",
			"source": "plugins/platform/opengl/main.cpp",
			"project": "plugins/platform/opengl/opengl"
		},
		"platform_gles": {
			"title": "Native OpenGLES runtime",
			"image": "images/plugins/platform_opengles.png",
			"text": "This plugin provides access to all OpenGLES core functions. OpenGLES API calls can be utilized when necessary.<br><a href=\"https://docs.tellusim.com/core/plugins/platform/opengles\" target=\"_blank\">docs.tellusim.com/core/plugins/platform/opengles</a>",
			"path": "plugins/platform/opengles",
			"exec": "main",
			"source": "plugins/platform/opengles/main.cpp",
			"project": "plugins/platform/opengles/opengles"
		}
	},
	"Languages": {
		"system_reflection": {
			"title": "C++ API reflection",
			"image": "images/plugins/system_reflection.png",
			"text": "This plugin enables reflection support for C++ API.<br><a href=\"https://docs.tellusim.com/core/plugins/system/reflection\" target=\"_blank\">docs.tellusim.com/core/plugins/system/reflection</a>",
			"path": "plugins/system/reflection",
			"exec": "main",
			"source": "plugins/system/reflection/main.cpp",
			"project": "plugins/system/reflection/reflection"
		},
		"binding_c": {
			"title": "C API binding",
			"image": "images/plugins/binding_c.jpg",
			"text": "The C language API is an intermediary layer between C++ and other languages, such as C#, Rust, and others, that cannot directly import C++ code.<br><a href=\"https://docs.tellusim.com/core/plugins/binding/capi\" target=\"_blank\">docs.tellusim.com/core/plugins/binding/capi</a>",
			"path": "plugins/binding/capi",
			"exec": "main",
			"source": "plugins/binding/capi/main.c"
		},
		"binding_csharp": {
			"title": "C# API binding",
			"image": "images/plugins/binding_csharp.jpg",
			"text": "This plugin provides complete C# language access for all classes and functions. C API bridge plugin is required.<br><a href=\"https://docs.tellusim.com/core/plugins/binding/csharp\" target=\"_blank\">docs.tellusim.com/core/plugins/binding/csharp</a>",
			"path": "plugins/binding/csharp",
			"exec": "main.exe",
			"readme": "plugins/binding/csharp/Readme.txt",
			"source": "plugins/binding/csharp/main.cs"
		},
		"binding_python": {
			"title": "Python API binding",
			"image": "images/plugins/binding_python.jpg",
			"text": "Python language API binding gives full access to Tellusim SDK from Python language. It is implemented on C Python API and does not require any additional dependencies.<br><a href=\"https://docs.tellusim.com/core/plugins/binding/python\" target=\"_blank\">docs.tellusim.com/core/plugins/binding/python</a>",
			"path": "plugins/binding/python",
			"exec": "main.py",
			"readme": "plugins/binding/python/Readme.txt",
			"source": "plugins/binding/python/main.py"
		},
		"binding_rust": {
			"title": "Rust API binding",
			"image": "images/plugins/binding_rust.jpg",
			"text": "This plugin provides complete Rust language access for all classes and functions. C API bridge plugin is required.<br><a href=\"https://docs.tellusim.com/core/plugins/binding/rust\" target=\"_blank\">docs.tellusim.com/core/plugins/binding/rust</a>",
			"path": "plugins/binding/rust",
			"exec": "main",
			"readme": "plugins/binding/rust/Readme.txt",
			"source": "plugins/binding/rust/main.rs"
		},
		"binding_swift": {
			"title": "Swift API binding",
			"image": "images/plugins/binding_swift.jpg",
			"text": "This plugin provides complete Swift language access for all classes and functions.<br><a href=\"https://docs.tellusim.com/core/plugins/binding/swift\" target=\"_blank\">docs.tellusim.com/core/plugins/binding/swift</a>",
			"path": "plugins/binding/swift",
			"exec": "main",
			"source": "plugins/binding/swift/main.swift"
		},
		"binding_java": {
			"title": "Java/Kotlin API binding",
			"image": "images/plugins/binding_java.jpg",
			"text": "This plugin provides complete Java and Kotlin language access for all classes and functions.<br><a href=\"https://docs.tellusim.com/core/plugins/binding/java\" target=\"_blank\">docs.tellusim.com/core/plugins/binding/java</a>",
			"path": "plugins/binding/java",
			"exec": "main",
			"source": "plugins/binding/java/main.java"
		},
		"binding_javascript": {
			"title": "JavaScript API binding",
			"image": "images/plugins/binding_javascript.jpg",
			"text": "This plugin provides complete JavaScript language access for all classes and functions.<br><a href=\"https://docs.tellusim.com/core/plugins/binding/javascript\" target=\"_blank\">docs.tellusim.com/core/plugins/binding/javascript</a>",
			"path": "plugins/binding/javascript",
			"exec": "main",
			"source": "plugins/binding/javascript/main.js"
		}
	},
	"Native": {
		"native_d3d12_runtime": {
			"title": "Native Direct3D12 runtime",
			"image": "images/native/native_d3d12_runtime.jpg",
			"text": "Drawing geometry using native Direct3D12 API calls.",
			"path": "samples/native/d3d12_runtime",
			"exec": "main",
			"source": "samples/native/d3d12_runtime/main.cpp",
			"project": "samples/native/d3d12_runtime/d3d12_runtime"
		},
		"native_d3d11_runtime": {
			"title": "Native Direct3D11 runtime",
			"image": "images/native/native_d3d11_runtime.jpg",
			"text": "Drawing geometry using native Direct3D11 API calls.",
			"path": "samples/native/d3d11_runtime",
			"exec": "main",
			"source": "samples/native/d3d11_runtime/main.cpp",
			"project": "samples/native/d3d11_runtime/d3d11_runtime"
		},
		"native_mtl_runtime": {
			"title": "Native Metal runtime",
			"image": "images/native/native_mtl_runtime.jpg",
			"text": "Drawing geometry using native Metal API calls.",
			"path": "samples/native/mtl_runtime",
			"exec": "main",
			"source": "samples/native/mtl_runtime/main.cpp",
			"project": "samples/native/mtl_runtime/mtl_runtime"
		},
		"native_cuda_runtime": {
			"title": "Native Cuda runtime",
			"image": "images/native/native_cuda_runtime.jpg",
			"text": "Cuda runtime API with buffer interop.",
			"path": "samples/native/cuda_runtime",
			"exec": "main",
			"source": "samples/native/cuda_runtime/main.cpp",
			"project": "samples/native/cuda_runtime/cuda_runtime"
		},
		"native_hip_runtime": {
			"title": "Native ROCm runtime",
			"image": "images/native/native_hip_runtime.jpg",
			"text": "ROCm runtime API with buffer interop.",
			"path": "samples/native/hip_runtime",
			"exec": "main",
			"source": "samples/native/hip_runtime/main.cpp",
			"project": "samples/native/hip_runtime/hip_runtime"
		},
		"native_d3d12_texture": {
			"title": "Native D3D12 texture",
			"image": "images/native/native_d3d12_texture.jpg",
			"text": "Using native D3D12 textures.",
			"path": "samples/native/d3d12_texture",
			"exec": "main",
			"source": "samples/native/d3d12_texture/main.cpp",
			"project": "samples/native/d3d12_texture/d3d12_texture"
		},
		"native_cuda_texture": {
			"title": "Native Cuda texture",
			"image": "images/native/native_cuda_texture.jpg",
			"text": "Cuda runtime API and texture interop.",
			"path": "samples/native/cuda_texture",
			"exec": "main",
			"source": "samples/native/cuda_texture/main.cpp",
			"project": "samples/native/cuda_texture/cuda_texture"
		},
		"native_d3d12_pipeline": {
			"title": "Native Direct3D12 pipeline",
			"image": "images/native/native_d3d12_pipeline.png",
			"text": "Creating native Direct3D12 pipeline.",
			"path": "samples/native/d3d12_pipeline",
			"exec": "main",
			"source": "samples/native/d3d12_pipeline/main.cpp",
			"project": "samples/native/d3d12_pipeline/d3d12_pipeline"
		},
		"native_vk_pipeline": {
			"title": "Native Vulkan pipeline",
			"image": "images/native/native_vk_pipeline.png",
			"text": "Creating native Vulkan pipeline.",
			"path": "samples/native/vk_pipeline",
			"exec": "main",
			"source": "samples/native/vk_pipeline/main.cpp",
			"project": "samples/native/vk_pipeline/vk_pipeline"
		},
		"native_mtl_pipeline": {
			"title": "Native Metal pipeline",
			"image": "images/native/native_mtl_pipeline.png",
			"text": "Creating native Metal pipeline.",
			"path": "samples/native/mtl_pipeline",
			"exec": "main",
			"source": "samples/native/mtl_pipeline/main.cpp",
			"project": "samples/native/mtl_pipeline/mtl_pipeline"
		},
		"native_d3d12_window": {
			"title": "Embedding into Direct3D12",
			"image": "images/native/native_d3d12_window.png",
			"text": "Embedding into the nativeal Direct3D12 native window application.",
			"path": "samples/native/d3d12_window",
			"exec": "main",
			"source": "samples/native/d3d12_window/main.cpp",
			"project": "samples/native/d3d12_window/d3d12_window"
		},
		"native_d3d11_window": {
			"title": "Embedding into Direct3D11",
			"image": "images/native/native_d3d11_window.png",
			"text": "Embedding into the nativeal Direct3D11 native window application.",
			"path": "samples/native/d3d11_window",
			"exec": "main",
			"source": "samples/native/d3d11_window/main.cpp",
			"project": "samples/native/d3d11_indow/d3d11_window"
		},
		"native_mtl_window": {
			"title": "Embedding into Metal",
			"image": "images/native/native_mtl_window.png",
			"text": "Embedding into the nativeal Metal native window application (MTKView).",
			"path": "samples/native/mtl_window",
			"exec": "main",
			"source": "samples/native/mtl_window/main.cpp",
			"project": "samples/native/mtl_window/mtl_window"
		}
	},
	"Tools": {
		"tellisim_shader": {
			"title": "Tellusim Shader",
			"image": "images/tools/tellusim_shader.png",
			"text": "Command-line interface to the Clay shader compiler.<br><a href=\"https://docs.tellusim.com/core/tools/shader\" target=\"_blank\">docs.tellusim.com/core/tools/shader</a>",
			"path": "bin",
			"source": "tools/shader/shader.cpp",
			"project": "tools/shader/shader"
		},
		"tellisim_image": {
			"title": "Tellusim Image",
			"image": "images/tools/tellusim_image.png",
			"text": "Image conversion utility with batch processing support.<br><a href=\"https://docs.tellusim.com/core/tools/image\" target=\"_blank\">docs.tellusim.com/core/tools/image</a>",
			"path": "bin",
			"source": "tools/image/image.cpp",
			"project": "tools/image/image"
		},
		"tellisim_mesh": {
			"title": "Tellusim Mesh",
			"image": "images/tools/tellusim_mesh.png",
			"text": "Mesh conversion utility with batch processing support.<br><a href=\"https://docs.tellusim.com/core/tools/mesh\" target=\"_blank\">docs.tellusim.com/core/tools/mesh</a>",
			"path": "bin",
			"source": "tools/mesh/mesh.cpp",
			"project": "tools/mesh/mesh"
		},
		"tellisim_blob": {
			"title": "Tellusim Blob",
			"image": "images/tools/tellusim_blob.png",
			"text": "Tool for generating embedded binary resources for applications.<br><a href=\"https://docs.tellusim.com/core/tools/blob\" target=\"_blank\">docs.tellusim.com/core/tools/blob</a>",
			"path": "bin",
			"source": "tools/blob/blob.cpp",
			"project": "tools/blob/blob"
		},
		"tellisim_project": {
			"title": "Tellusim Project",
			"image": "images/tools/tellusim_project.png",
			"text": "Utility for generating project templates.<br><a href=\"https://docs.tellusim.com/core/tools/project\" target=\"_blank\">docs.tellusim.com/core/tools/project</a>",
			"path": "bin",
			"source": "tools/project/project.cpp",
			"project": "tools/project/project"
		},
		"tellisim_noise": {
			"title": "Tellusim Noise",
			"image": "images/tools/tellusim_noise.png",
			"text": "Blue noise generation tool for stochastic sampling and rendering.<br><a href=\"https://docs.tellusim.com/core/tools/noise\" target=\"_blank\">docs.tellusim.com/core/tools/noise</a>",
			"path": "bin",
			"source": "tools/noise/noise.cpp",
			"project": "tools/noise/noise"
		}
	},
	"Tutorials": {
		"13_hello_interop": {
			"title": "Hello Interop",
			"image": "images/manual/manual_13_hello_interop.jpg",
			"text": "<a href=\"https://docs.tellusim.com/core/tutorials/13_hello_interop\" target=\"_blank\">docs.tellusim.com/core/tutorials/13_hello_interop</a>",
			"path": "samples/manual/13_hello_interop",
			"exec": "main",
			"source": "samples/manual/13_hello_interop/main.cu"
		},
		"12_hello_controller": {
			"title": "Hello Controller",
			"image": "images/manual/manual_12_hello_controller.jpg",
			"text": "<a href=\"https://docs.tellusim.com/core/tutorials/12_hello_controller\" target=\"_blank\">docs.tellusim.com/core/tutorials/12_hello_controller</a>",
			"path": "samples/manual/12_hello_controller",
			"exec": "main",
			"source": "samples/manual/12_hello_controller/main.cpp",
			"project": "samples/manual/12_hello_controller/12_hello_controller"
		},
		"11_hello_bindless": {
			"title": "Hello Bindless",
			"image": "images/manual/manual_11_hello_bindless.jpg",
			"text": "<a href=\"https://docs.tellusim.com/core/tutorials/11_hello_bindless\" target=\"_blank\">docs.tellusim.com/core/tutorials/11_hello_bindless</a>",
			"path": "samples/manual/11_hello_bindless",
			"exec": "main",
			"source": "samples/manual/11_hello_bindless/main.cpp",
			"project": "samples/manual/11_hello_bindless/11_hello_bindless"
		},
		"10_hello_image": {
			"title": "Hello Image",
			"image": "images/manual/manual_10_hello_image.jpg",
			"text": "<a href=\"https://docs.tellusim.com/core/tutorials/10_hello_image/\" target=\"_blank\">docs.tellusim.com/core/tutorials/10_hello_image/</a>",
			"path": "samples/manual/10_hello_image",
			"exec": "main",
			"source": "samples/manual/10_hello_image/main.py"
		},
		"09_hello_controls": {
			"title": "Hello Controls",
			"image": "images/manual/manual_09_hello_controls.png",
			"text": "<a href=\"https://docs.tellusim.com/core/tutorials/09_hello_controls/\" target=\"_blank\">docs.tellusim.com/core/tutorials/09_hello_controls/</a>",
			"path": "samples/manual/09_hello_controls",
			"exec": "main",
			"source": "samples/manual/09_hello_controls/main.cpp",
			"project": "samples/manual/09_hello_controls/09_hello_controls"
		},
		"08_hello_canvas": {
			"title": "Hello Canvas",
			"image": "images/manual/manual_08_hello_canvas.png",
			"text": "<a href=\"https://docs.tellusim.com/core/tutorials/08_hello_canvas\" target=\"_blank\">docs.tellusim.com/core/tutorials/08_hello_canvas</a>",
			"path": "samples/manual/08_hello_canvas",
			"exec": "main",
			"source": "samples/manual/08_hello_canvas/main.cpp",
			"project": "samples/manual/08_hello_canvas/08_hello_canvas"
		},
		"07_hello_splatting": {
			"title": "Gaussian Splatting",
			"image": "images/manual/manual_07_hello_splatting.jpg",
			"text": "<a href=\"https://docs.tellusim.com/core/tutorials/07_hello_splatting/\" target=\"_blank\">docs.tellusim.com/core/tutorials/07_hello_splatting/</a>",
			"path": "samples/manual/07_hello_splatting",
			"exec": "main",
			"source": "samples/manual/07_hello_splatting/main.cpp",
			"project": "samples/manual/07_hello_splatting/07_hello_splatting"
		},
		"06_hello_tracing": {
			"title": "Ray Tracing with Traversal",
			"image": "images/manual/manual_06_hello_traversal.jpg",
			"text": "<a href=\"https://docs.tellusim.com/core/tutorials/06_hello_traversal/\" target=\"_blank\">docs.tellusim.com/core/tutorials/06_hello_traversal/</a>",
			"path": "samples/manual/06_hello_traversal",
			"exec": "main",
			"source": "samples/manual/06_hello_traversal/main.cpp",
			"project": "samples/manual/06_hello_traversal/06_hello_traversal"
		},
		"05_hello_tracing": {
			"title": "Ray Tracing with Ray Queries",
			"image": "images/manual/manual_05_hello_tracing.jpg",
			"text": "<a href=\"https://docs.tellusim.com/core/tutorials/05_hello_tracing/\" target=\"_blank\">docs.tellusim.com/core/tutorials/05_hello_tracing/</a>",
			"path": "samples/manual/05_hello_tracing",
			"exec": "main",
			"source": "samples/manual/05_hello_tracing/main.cpp",
			"project": "samples/manual/05_hello_tracing/05_hello_tracing"
		},
		"04_hello_raster": {
			"title": "Compute rasterization",
			"image": "images/manual/manual_04_hello_raster.jpg",
			"text": "<a href=\"https://docs.tellusim.com/core/tutorials/04_hello_raster/\" target=\"_blank\">docs.tellusim.com/core/tutorials/04_hello_raster/</a>",
			"path": "samples/manual/04_hello_raster",
			"exec": "main",
			"source": "samples/manual/04_hello_raster/main.cpp",
			"project": "samples/manual/04_hello_raster/04_hello_raster"
		},
		"03_hello_mesh": {
			"title": "Hierarchical LOD Graphs",
			"image": "images/manual/manual_03_hello_mesh.jpg",
			"text": "<a href=\"https://docs.tellusim.com/core/tutorials/03_hello_mesh/\" target=\"_blank\">docs.tellusim.com/core/tutorials/03_hello_mesh/</a>",
			"path": "samples/manual/03_hello_mesh",
			"exec": "main",
			"source": "samples/manual/03_hello_mesh/main.cpp",
			"project": "samples/manual/03_hello_mesh/03_hello_mesh"
		},
		"02_hello_compute": {
			"title": "Particles Simuation",
			"image": "images/manual/manual_02_hello_compute.jpg",
			"text": "<a href=\"https://docs.tellusim.com/core/tutorials/02_hello_compute\" target=\"_blank\">docs.tellusim.com/core/tutorials/02_hello_compute</a>",
			"path": "samples/manual/02_hello_compute",
			"exec": "main",
			"source": "samples/manual/02_hello_compute/main.cpp",
			"project": "samples/manual/02_hello_compute/02_hello_compute"
		},
		"01_hello_usdz": {
			"title": "USDZ Model Loading",
			"image": "images/manual/manual_01_hello_usdz.jpg",
			"text": "<a href=\"https://docs.tellusim.com/core/tutorials/01_hello_usdz\" target=\"_blank\">docs.tellusim.com/core/tutorials/01_hello_usdz</a>",
			"path": "samples/manual/01_hello_usdz",
			"exec": "main",
			"source": "samples/manual/01_hello_usdz/main.cpp",
			"python": "samples/manual/01_hello_usdz/main.py",
			"rust": "samples/manual/01_hello_usdz/main.rs",
			"swift": "samples/manual/01_hello_usdz/main.swift",
			"project": "samples/manual/01_hello_usdz/01_hello_usdz"
		},
		"00_hello_triangle": {
			"title": "Hello Triangle",
			"image": "images/manual/manual_00_hello_triangle.png",
			"text": "<a href=\"https://docs.tellusim.com/core/tutorials/00_hello_triangle\" target=\"_blank\">docs.tellusim.com/core/tutorials/00_hello_triangle</a>",
			"path": "samples/manual/00_hello_triangle",
			"exec": "main",
			"source": "samples/manual/00_hello_triangle/main.cpp",
			"python": "samples/manual/00_hello_triangle/main.py",
			"project": "samples/manual/00_hello_triangle/01_hello_triangle"
		}
	},
	"Resources": {
		"documentation": {
			"title": "Documentation",
			"image": "images/resources/documentation.png",
			"text": "Access Tellusim Core SDK documentation online.<br><a href=\"https://docs.tellusim.com/core\" target=\"_blank\">docs.tellusim.com/core</a>",
			"open": "https://docs.tellusim.com/core"
		},
		"developer_forum": {
			"title": "Developer Forum",
			"image": "images/resources/developer_forum.png",
			"text": "Join Tellusim Developer Forum to ask questions and explore community discussions.<br><a href=\"https://forum.tellusim.com\" target=\"_blank\">forum.tellusim.com</a>",
			"open": "https://forum.tellusim.com"
		},
		"api_reference": {
			"title": "Local API Reference",
			"image": "images/resources/api_reference.png",
			"text": "Browse the offline C++ API reference for the Tellusim Core SDK.",
			"open": "docs/Tellusim_Core_API.pdf"
		}
	}
}
