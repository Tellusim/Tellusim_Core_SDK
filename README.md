# Tellusim Core SDK

Tellusim Core SDK is the foundational layer of the Tellusim Engine, providing low-level functionality for high-performance graphics, compute, and application development across multiple platforms and devices. It offers a unified C++ API designed to abstract hardware and OS differences, enabling developers to write portable and scalable applications in graphics, simulation, visualization, and AI.

The SDK includes comprehensive support for meshes, images, user interfaces, and GPU-accelerated algorithms such as radix sort, bounding volume hierarchies (BVH), fast Fourier transforms (FFT), and GPU-driven computational graph framework for machine learning and advanced data processing.

In addition to C++, the SDK provides bindings and interoperability for other languages such as C#, Rust, Swift, and Python, making it suitable for use in native mobile and desktop applications as well as game and graphics engines.

Happy coding, and have fun creating with Tellusim!

## Licensing

* Tellusim Core SDK is free for education
* Tellusim Core SDK is free for companies with annual revenue less than USD $200,000
* Tellusim Core SDK may be used for evaluation purposes, limited to testing, learning, and other non-commercial experimentation
* Any other use, including commercial or production deployment, requires a separate negotiated license with Tellusim Technologies Inc.

For inquiries, visit: [Tellusim Services](https://tellusim.com/services/)

## Documentation

[Tellusim Core SDK Documentation](https://docs.tellusim.com/core)

## Platforms

Please choose the correct branch for your platform:

* [Windows x64](https://github.com/Tellusim/Tellusim_Core_SDK/tree/windows_x64)
* [Windows arm64](https://github.com/Tellusim/Tellusim_Core_SDK/tree/windows_arm64)
* [Linux x64](https://github.com/Tellusim/Tellusim_Core_SDK/tree/linux_x64)
* [Linux arm64](https://github.com/Tellusim/Tellusim_Core_SDK/tree/linux_arm64)
* [macOS x64](https://github.com/Tellusim/Tellusim_Core_SDK/tree/macos_x64)
* [macOS arm64](https://github.com/Tellusim/Tellusim_Core_SDK/tree/macos_arm64)
* [Android](https://github.com/Tellusim/Tellusim_Core_SDK/tree/android)
* [iOS](https://github.com/Tellusim/Tellusim_Core_SDK/tree/ios)
* [tvOS](https://github.com/Tellusim/Tellusim_Core_SDK/tree/tvos)
* [Web](https://github.com/Tellusim/Tellusim_Core_SDK/tree/emscripten)

# Graphics

## [Clustered Lights](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/graphics/lights/)

Forward shading with 16384 dynamic lights. This algorithm is compatible with deferred shading and transparent objects.

[![Clustered Lights](utils/browser/images/graphics/graphics_lights.jpg)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/graphics/lights/)

---

## [Meshlet Render](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/graphics/meshlet/)

A massive meshlets rendering example with Mesh Shader for hardware and Compute Shader for software rasterization.  
'1' activates Instancing mode.  
'2' activates Mesh Shader mode.  
'3' activates Compute rasterization mode.

[![Meshlet Render](utils/browser/images/graphics/graphics_meshlet.jpg)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/graphics/meshlet/)

---

## [Mesh RayTracing](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/graphics/traversal/)

Traversal class for the simple raytracing pipeline access. Vulkan or Direct3D12 API is required.

[![Mesh RayTracing](utils/browser/images/graphics/graphics_traversal.jpg)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/graphics/traversal/)

---

## [Mesh RayQuery](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/graphics/tracing/)

Ray Query raytracing of animated scene. Vulkan, Direct3D12, or Metal API is required.  
'1' activates Fragment Shader raytracing (if available).

[![Mesh RayQuery](utils/browser/images/graphics/graphics_tracing.jpg)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/graphics/tracing/)

---

## [Hardware RayTracing](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/graphics/skinned_tracing/)

Hardware accelerated RayTracing of animated objects.

[![Hardware RayTracing](utils/browser/images/graphics/graphics_skinned_tracing.jpg)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/graphics/skinned_tracing/)

---

## [Compute RayTracing](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/graphics/skinned_tree/)

Compute Shader RayTracing of animated objects.

[![Compute RayTracing](utils/browser/images/graphics/graphics_skinned_tree.jpg)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/graphics/skinned_tree/)

---

## [Hardware RayTracing](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/graphics/mesh_tracing/)

Hardware accelerated RayTracing of high-polygonal objects.

[![Hardware RayTracing](utils/browser/images/graphics/graphics_mesh_tracing.jpg)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/graphics/mesh_tracing/)

---

## [Compute RayTracing](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/graphics/mesh_tree/)

Compute Shader RayTracing of high-polygonal objects.

[![Compute RayTracing](utils/browser/images/graphics/graphics_mesh_tree.jpg)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/graphics/mesh_tree/)

---

## [JPEG Decoder](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/graphics/decoder_jpeg/)

The DecoderJPEG provides GPU-accelerated JPEG decoding functionality.

[![JPEG Decoder](utils/browser/images/graphics/graphics_decoder_jpeg.jpg)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/graphics/decoder_jpeg/)

---

## [Cube Filter](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/graphics/cube_filter/)

The CubeFilter interface performs real-time Cube texture filtration.

[![Cube Filter](utils/browser/images/graphics/graphics_cube_filter.jpg)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/graphics/cube_filter/)

---

## [Separable Filter](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/graphics/separable_filter/)

The SeparableFilter interface helps to create different separable filters like Gaussian, Sobel, Box, and custom weights.

[![Separable Filter](utils/browser/images/graphics/graphics_separable_filter.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/graphics/separable_filter/)

---

## [Indirect Draw](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/graphics/indirect/)

Drawing massive amount of quads using different indirect rendering techniques.

[![Indirect Draw](utils/browser/images/graphics/graphics_indirect.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/graphics/indirect/)

---

## [Geometry Shader](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/graphics/geometry/)

Rendering massive amount of boxes with Geometry Shaders.  
'1' activates Vertex Shader mode.  
'2' activates Mesh Shader mode (if available).

[![Geometry Shader](utils/browser/images/graphics/graphics_geometry.jpg)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/graphics/geometry/)

---

## [Tessellation Shader](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/graphics/tessellation/)

Quadrilateral tessellation with Control + Evaluate or Mesh Shaders.  
'1' activates Mesh Shader tessellation mode (if available).

[![Tessellation Shader](utils/browser/images/graphics/graphics_tessellation.jpg)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/graphics/tessellation/)

---

## [Ordered Independent Transparency](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/graphics/transparency/)

Ordered Independent Transparency with atomic buffer operations from the fragment shader.

[![Ordered Independent Transparency](utils/browser/images/graphics/graphics_transparency.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/graphics/transparency/)

---

## [Hardware Ray Tracing Shadows](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/graphics/shadow_tracing/)

Hardware raytracing shadows with simple deferred shading. An API with Ray Query support is required.

[![Hardware Ray Tracing Shadows](utils/browser/images/graphics/graphics_shadow_tree.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/graphics/shadow_tracing/)

---

## [Software Ray Tracing Shadows](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/graphics/shadow_tree/)

Software raytracing shadows with simple deferred shading. Compatible with all APIs.

[![Software Ray Tracing Shadows](utils/browser/images/graphics/graphics_shadow_tree.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/graphics/shadow_tree/)

---

## [Percentage Closer Filtering Shadow Map](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/graphics/shadow_pcf/)

PCF Shadow Maps provides shadow with variable penumbra size based on the distance between the shadow caster and receiver.

[![Percentage Closer Filtering Shadow Map](utils/browser/images/graphics/graphics_shadow_pcf.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/graphics/shadow_pcf/)

---

## [Exponential Shadow Maps](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/graphics/shadow_esm/)

Exponential Shadow Maps provides noise-free shadows with a fixed performance cost and constant penumbra size.

[![Exponential Shadow Maps](utils/browser/images/graphics/graphics_shadow_esm.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/graphics/shadow_esm/)

---

## [Parallax 2D](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/graphics/parallax_2d/)

Parallax occlusion mapping with self-shadowing for the mesh geometry.

[![Parallax 2D](utils/browser/images/graphics/graphics_parallax_2d.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/graphics/parallax_2d/)

---

## [Parallax Cube](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/graphics/parallax_cube/)

Parallax occlusion mapping with self-shadowing for the analytical sphere.

[![Parallax Cube](utils/browser/images/graphics/graphics_parallax_cube.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/graphics/parallax_cube/)

---

## [Mesh Tangent Basis](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/graphics/tangent/)

Mesh tangent basis renormalization at the Fragment Shader. Mesh class can re-create normal and tangent vectors.

[![Mesh Tangent Basis](utils/browser/images/graphics/graphics_tangent.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/graphics/tangent/)

---

## [Mesh Model](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/graphics/model/)

MeshModel class creates a rendering model representation for the input Mesh or MeshGeometry with a specified Pipeline layout.  
It is possible to inherit MeshModel class and combine multiple meshes into the single Buffer.

[![Mesh Model](utils/browser/images/graphics/graphics_model.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/graphics/model/)

---

## [Mesh Morphing](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/graphics/morph/)

This is a basic morph mesh animation example. AttributeIndex provides a stable mapping between source and optimized vertices. Texel Buffer acts as a workaround for platforms that lack compute shader support.

[![Mesh Morphing](utils/browser/images/graphics/graphics_morph.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/graphics/morph/)

---

## [Mesh Skinning](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/graphics/skinned/)

This is a basic skinned mesh animation example. Mesh classes give comprehensive access to all mesh data, including Nodes, Animations, Materials, Cameras, and Lights.

[![Mesh Skinning](utils/browser/images/graphics/graphics_skinned.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/graphics/skinned/)

---

## [Multi Window](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/graphics/multi_window/)

Rendering scene into multiple borderless windows.

[![Multi Window](utils/browser/images/graphics/graphics_multi_window.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/graphics/multi_window/)

---

## [Line Rendering](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/graphics/line/)

Simple antialiased line rendering. The Vertex shader creates a screen-aligned billboard, and the fragment shader calculates the distance to the line.

[![Line Rendering](utils/browser/images/graphics/graphics_line.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/graphics/line/)

# Platform

## [Platform Precision](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/platform/precision/)

Performance and precision difference between 16-bit, 32-bit, and 64-bit floating formats.  
'1' activates 64-bit precision.  
'2' activates 16-bit precision.

[![Platform Precision](utils/browser/images/platform/platform_precision.jpg)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/platform/precision/)

---

## [Platform Bindless](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/platform/bindless/)

This example demonstrates bindless Buffer and Texture resources indexed by InstanceIndex. Vulkan, Direct3D12, or Metal API is required.

[![Platform Bindless](utils/browser/images/platform/platform_bindless.jpg)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/platform/bindless/)

---

## [Platform TextureTable](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/platform/table/)

TextureTable is an interface for an unlimited number of bindless textures that can be accessed from any shader by uniform or non-uniform index. Vulkan, Direct3D12, or Metal API is required.

[![Platform TextureTable](utils/browser/images/platform/platform_table.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/platform/table/)

---

## [Platform Texel](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/platform/texel/)

Texel buffer provides cached buffer access that is compatible with OpenGLES platform. Moreover, it can work faster than the Storage buffer in some scenarios.

[![Platform Texel](utils/browser/images/platform/platform_texel.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/platform/texel/)

---

## [Platform Texture](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/platform/texture/)

Dynamic 3D texture created with SIMD CPU instructions.

[![Platform Texture](utils/browser/images/platform/platform_texture.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/platform/texture/)

---

## [Platform Command](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/platform/command/)

Command class for basic rendering. Depth Cube texture for omnidirectional shadow map.

[![Platform Command](utils/browser/images/platform/platform_command.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/platform/command/)

---

## [Platform Tracing](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/platform/tracing/)

Hardware accelerated raytracing shadows. An API with Ray Query support is required.

[![Platform Tracing](utils/browser/images/platform/platform_tracing.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/platform/tracing/)

---

## [Platform Compute](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/platform/compute/)

Compute class for simple compute shader texture generation.

[![Platform Compute](utils/browser/images/platform/platform_compute.jpg)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/platform/compute/)

---

## [Platform Fence](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/platform/fence/)

Multi-GPU N-body simulation with Fence synchronization. A shared buffer is used for data exchange between GPUs.

[![Platform Fence](utils/browser/images/platform/platform_fence.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/platform/fence/)

---

## [Platform Fence](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/platform/shared/)

Multi-GPU synchronization with fences and semaphores.

[![Platform Fence](utils/browser/images/platform/platform_shared.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/platform/shared/)

---

## [Platform Sparse](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/platform/sparse/)

This example shows how sparse textures allow handling very large textures by allocating only the needed tiles in GPU memory

[![Platform Sparse](utils/browser/images/platform/platform_sparse.jpg)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/platform/sparse/)

---

## [Platform Mapped](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/platform/mapped/)

This example shows how Vulkan can map files into GPU buffers, allowing the GPU to read from and write to files directly without extra copying.

[![Platform Mapped](utils/browser/images/platform/platform_mapped.jpg)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/platform/mapped/)

---

## [Platform Formats](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/platform/formats/)

This example shows how mixed texture formats can reduce video memory consumption. Image format conversion is performed by the Image interface.

[![Platform Formats](utils/browser/images/platform/platform_formats.jpg)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/platform/formats/)

---

## [Platform Dynamic](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/platform/dynamic/)

A single-thread dynamic geometry rendering can provide more than 100M triangles per second rate.

[![Platform Dynamic](utils/browser/images/platform/platform_dynamic.jpg)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/platform/dynamic/)

---

## [Platform Clip Planes](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/platform/clipping/)

Vertex Shader clip distance output is useful for arbitrary geometry culling.

[![Platform Clip Planes](utils/browser/images/platform/platform_clipping.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/platform/clipping/)

---

## [Platform Stencil Buffer](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/platform/stencil/)

Constructive Solid Geometry with the Stencil Buffer. This algorithm is compatible with procedural geometry.

[![Platform Stencil Buffer](utils/browser/images/platform/platform_stencil.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/platform/stencil/)

---

## [Platform Fusion](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/platform/fusion/)

Fusion API allows replicating all commands and resources across multiple physical or logical devices. It dramatically simplifies the development of apps for multi-GPU or multi-channel rendering.

[![Platform Fusion](utils/browser/images/platform/platform_fusion.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/platform/fusion/)

---

## [Platform Layers](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/platform/layers/)

Demonstrates multilayer rendering where the target layer is selected dynamically in the Vertex Shader, Geometry Shader, or Geometry Passthrough Shader.

[![Platform Layers](utils/browser/images/platform/platform_layers.jpg)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/platform/layers/)

---

## [Platform Viewports](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/platform/viewports/)

Demonstrates multi-viewport rendering with dynamic viewport selection in the Vertex Shader, Geometry Shader, or Geometry Passthrough Shader.

[![Platform Viewports](utils/browser/images/platform/platform_viewports.jpg)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/platform/viewports/)

---

## [Platform Samplers](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/platform/samplers/)

Demonstrates various texture sampler configuration modes.

[![Platform Samplers](utils/browser/images/platform/platform_samplers.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/platform/samplers/)

---

## [Barycentric Coordinates](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/platform/barycentric/)

Build-in barycentric coordinate input is available in Vulkan, Direct3D12, and Metal APIs.

[![Barycentric Coordinates](utils/browser/images/platform/platform_barycentric.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/platform/barycentric/)

---

## [Multi Draw Indirect](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/platform/indirect/)

This example performs MDI rendering of different objects.

[![Multi Draw Indirect](utils/browser/images/platform/platform_indirect.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/platform/indirect/)

---

## [MSAA Alpha Test](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/platform/alpha/)

MSAA-compatible alpha test in comparison to hardware alpha to coverage.

[![MSAA Alpha Test](utils/browser/images/platform/platform_alpha.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/platform/alpha/)

---

## [Input Blending Color](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/platform/blending/)

Blending color parameter defines uniform value for blending operations.

[![Input Blending Color](utils/browser/images/platform/platform_blending.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/platform/blending/)

---

## [Multisample Antialiasing](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/platform/multisample/)

This example performs AA line rendering into MSAA texture.

[![Multisample Antialiasing](utils/browser/images/platform/platform_multisample.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/platform/multisample/)

---

## [Platform Preprocessor](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/platform/preprocessor/)

This example demonstrates how to use the #include preprocessor directive to declare generic functions.

[![Platform Preprocessor](utils/browser/images/platform/platform_preprocessor.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/platform/preprocessor/)

---

## [Platform Texture Samples](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/platform/samples/)

Writing and reading individual multisample texture samples with active Pipeline sample write mask.

[![Platform Texture Samples](utils/browser/images/platform/platform_samples.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/platform/samples/)

---

## [Conservative Rasterization](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/platform/conservative/)

Hardware conservative rasterization.

[![Conservative Rasterization](utils/browser/images/platform/platform_conservative.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/platform/conservative/)

---

## [Cooperative Matrix (Tensor Cores)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/platform/cooperative/)

Cooperative matrix example.

[![Cooperative Matrix (Tensor Cores)](utils/browser/images/platform/platform_cooperative.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/platform/cooperative/)

---

## [Matrix Multiplication](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/platform/matrix/)

Matrix multiplication example.

[![Matrix Multiplication](utils/browser/images/platform/platform_matrix.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/platform/matrix/)

---

## [Subgroup operations](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/platform/subgroup/)

Shader subgroup operations.

[![Subgroup operations](utils/browser/images/platform/platform_subgroup.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/platform/subgroup/)

---

## [Structure references](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/platform/reference/)

This test showcases GLSL structure mapping to raw SSBO buffer, enabling storage of data with different layouts within a single SSBO buffer.

[![Structure references](utils/browser/images/platform/platform_reference.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/platform/reference/)

---

## [Shader Printf](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/platform/printf/)

A simple preprocessor-based printf() functionality for compute shaders that work with all APIs.

[![Shader Printf](utils/browser/images/platform/platform_printf.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/platform/printf/)

# Interface

## [Interface Canvas](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/interface/canvas/)

Different CanvasElement classes, including texture filtration, gradients, contour outlines, and SVG rendering.

[![Interface Canvas](utils/browser/images/interface/interface_canvas.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/interface/canvas/)

---

## [Interface Controls](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/interface/controls/)

Different User Interface Control classes in resolution-independent configuration.

[![Interface Controls](utils/browser/images/interface/interface_controls.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/interface/controls/)

---

## [SVG](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/plugins/interface/svg/)

This plugin enables SVG images support for Control widgets.  
[docs.tellusim.com/core/plugins/interface/svg](https://docs.tellusim.com/core/plugins/interface/svg)

[![SVG](utils/browser/images/plugins/interface_svg.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/plugins/interface/svg/)

---

## [Flow](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/plugins/interface/flow/)

Flow Control is a universal node-based editor designed for a variety of applications, including material and logic editing. It includes base implementations in both GLSL and C++.  
[docs.tellusim.com/core/plugins/interface/flow](https://docs.tellusim.com/core/plugins/interface/flow)

[![Flow](utils/browser/images/plugins/interface_flow.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/plugins/interface/flow/)

---

## [Color](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/plugins/interface/color/)

Color selector control.  
[docs.tellusim.com/core/plugins/interface/color](https://docs.tellusim.com/core/plugins/interface/color)

[![Color](utils/browser/images/plugins/interface_color.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/plugins/interface/color/)

---

## [Interface Element](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/plugins/interface/element/)

A CanvasElement wrapper that allows elements to be rendered and manipulated inside a Controls widgets.  
[docs.tellusim.com/core/plugins/interface/element](https://docs.tellusim.com/core/plugins/interface/element)

[![Interface Element](utils/browser/images/plugins/interface_element.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/plugins/interface/element/)

---

## [Button](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/plugins/interface/button/)

A generic button controller that uses custom Canvas elements as Control button.  
[docs.tellusim.com/core/plugins/interface/button](https://docs.tellusim.com/core/plugins/interface/button)

[![Button](utils/browser/images/plugins/interface_button.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/plugins/interface/button/)

---

## [Slider](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/plugins/interface/slider/)

A generic slider controller that uses custom Canvas elements as Control slider.  
[docs.tellusim.com/core/plugins/interface/slider](https://docs.tellusim.com/core/plugins/interface/slider)

[![Slider](utils/browser/images/plugins/interface_slider.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/plugins/interface/slider/)

---

## [Plotter](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/plugins/interface/plotter/)

A simple line plotter visualization plugin.  
[docs.tellusim.com/core/plugins/interface/plotter](https://docs.tellusim.com/core/plugins/interface/plotter)

[![Plotter](utils/browser/images/plugins/interface_plotter.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/plugins/interface/plotter/)

---

## [Tooltip](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/plugins/interface/tooltip/)

A generic tooltip Control allows the display of help information over other interface controls.  
[docs.tellusim.com/core/plugins/interface/tooltip](https://docs.tellusim.com/core/plugins/interface/tooltip)

[![Tooltip](utils/browser/images/plugins/interface_tooltip.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/plugins/interface/tooltip/)

---

## [Interface Layer](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/interface/layer/)

A transparent multilayer Controls with variable background blur.

[![Interface Layer](utils/browser/images/interface/interface_layer.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/interface/layer/)

---

## [Manipulator Plugin](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/plugins/interface/manipulator/)

Manipulator is a simple translator and rotator control for the scene editor.  
[docs.tellusim.com/core/plugins/interface/manipulator](https://docs.tellusim.com/core/plugins/interface/manipulator)

[![Manipulator Plugin](utils/browser/images/plugins/interface_manipulator.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/plugins/interface/manipulator/)

---

## [App](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/plugins/interface/app/)

This plugin provides a framework for single-window Control-based applications.  
[docs.tellusim.com/core/plugins/interface/app](https://docs.tellusim.com/core/plugins/interface/app)

[![App](utils/browser/images/plugins/interface_app.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/plugins/interface/app/)

---

## [Shape](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/interface/shape/)

This example renders cubic shape with applied Stroke and Gradient styles.

[![Shape](utils/browser/images/interface/interface_shape.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/interface/shape/)

---

## [SVG Image](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/interface/svg/)

Simple SVG image loading and rendering. CanvasShape class accepts SVG path string as input data.

[![SVG Image](utils/browser/images/interface/interface_svg.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/interface/svg/)

---

## [Custom Control](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/interface/control/)

Custom Controls can be created by simple ControlBase class inheritance. The Control behavior can be completely overridden.

[![Custom Control](utils/browser/images/interface/interface_control.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/interface/control/)

# Parallel

## [Parallel TensorGraph from PyTorch](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/parallel/tensor_torch/)

Simple convolutional autoencoder trained with PyTorch and imported into TensorGraph.

[![Parallel TensorGraph from PyTorch](utils/browser/images/parallel/parallel_tensor_torch.jpg)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/parallel/tensor_torch/)

---

## [Parallel TensorGraph MNIST Digits Recognition](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/parallel/tensor_mnist/)

MNIST Digits Recognition using TensorGraph with PyTorch model.

[![Parallel TensorGraph MNIST Digits Recognition](utils/browser/images/parallel/parallel_tensor_mnist.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/parallel/tensor_mnist/)

---

## [Parallel Fourier 2D](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/parallel/fourier_2d/)

Image convolution based on Fast Fourier Transformation.

[![Parallel Fourier 2D](utils/browser/images/parallel/parallel_fourier_2d.jpg)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/parallel/fourier_2d/)

---

## [Parallel Fluid 2D](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/parallel/fluid_2d/)

Simple 2D fluid simulation based on Fast Fourier Transformation.

[![Parallel Fluid 2D](utils/browser/images/parallel/parallel_fluid_2d.jpg)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/parallel/fluid_2d/)

---

## [Parallel Radix Sort](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/parallel/radix_sort/)

Multiple independent sorting algorithms can be dispatched in parallel. There is no overhead in comparision with the single array sort. Additionally, dispatch parameters can be fetched from the indirect buffer.  
'1' shows the input data.  
'2' activates global sort.

[![Parallel Radix Sort](utils/browser/images/parallel/parallel_radix_sort.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/parallel/radix_sort/)

---

## [Parallel Spatial Grid](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/parallel/spatial_grid/)

Simple physics simulation with collisions based on the SpatialGrid class. It is the fastest way to collide objects of the same size.

[![Parallel Spatial Grid](utils/browser/images/parallel/parallel_spatial_grid.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/parallel/spatial_grid/)

---

## [Parallel Spatial Tree](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/parallel/spatial_tree/)

Simple physics simulation with collisions based on the SpatialTree class. The SpatialTree allows collision and intersection tests with any primitive inside BVH.

[![Parallel Spatial Tree](utils/browser/images/parallel/parallel_spatial_tree.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/parallel/spatial_tree/)

# Geometry

## [Mesh Reduce](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/geometry/reduce/)

MeshReduce is a simple way to simplify input mesh geometry. Simplification preserves all Mesh Attributes, and it is compatible with Skinning Animation.  
'1' shows the original geometry.

[![Mesh Reduce](utils/browser/images/geometry/geometry_reduce.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/geometry/reduce/)

---

## [Mesh Refine](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/geometry/refine/)

MeshRefine refines geometry mesh using Catmull-Clark (for quadrilaterals) or Loop (for triangles) subdivision algorithms. The Crease Attribute allows additional control over the subdivision process.  
'1' shows the original geometry.

[![Mesh Refine](utils/browser/images/geometry/geometry_refine.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/geometry/refine/)

# Plugins

## [Open Neural Network Exchange](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/plugins/parallel/onnx/)

The ONNX plugin allows loading and running ONNX models with TensorGraph on all platforms and APIs.  
[docs.tellusim.com/core/plugins/parallel/onnx](https://docs.tellusim.com/core/plugins/parallel/onnx)

[![Open Neural Network Exchange](utils/browser/images/plugins/parallel_onnx.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/plugins/parallel/onnx/)

---

## [OpenXR](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/plugins/platform/openxr/)

OpenXR VR/AR plugin. Supports Vulkan, Direct3D12, Direct3D11, OpenGL APIs on PC; Vulkan, OpenGLES on Android. This plugin creates an OpenXR-compatible output window with any number of channels. The input layer provides a simplified API for the OpenXR input system.  
[docs.tellusim.com/core/plugins/platform/openxr](https://docs.tellusim.com/core/plugins/platform/openxr)

[![OpenXR](utils/browser/images/plugins/platform_openxr.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/plugins/platform/openxr/)

---

## [Native Cuda driver API](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/plugins/platform/cuda/)

Create dynamic geometry with Cuda and render with Vulkan / Direct3D / OpenGL.  
[docs.tellusim.com/core/plugins/platform/cuda](https://docs.tellusim.com/core/plugins/platform/cuda)

[![Native Cuda driver API](utils/browser/images/plugins/platform_cuda.jpg)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/plugins/platform/cuda/)

---

## [Native Vulkan runtime](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/plugins/platform/vulkan/)

You can use this plugin to write applications with native Vulkan API. All Tellusim platform classes give access to internal Vulkan handlers and can be used in Vulkan API calls.  
[docs.tellusim.com/core/plugins/platform/vulkan](https://docs.tellusim.com/core/plugins/platform/vulkan)

[![Native Vulkan runtime](utils/browser/images/plugins/platform_vulkan.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/plugins/platform/vulkan/)

---

## [Native OpenGL runtime](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/plugins/platform/opengl/)

This plugin provides access to all OpenGL core functions. OpenGL API calls can be utilized when necessary.  
[docs.tellusim.com/core/plugins/platform/opengl](https://docs.tellusim.com/core/plugins/platform/opengl)

[![Native OpenGL runtime](utils/browser/images/plugins/platform_opengl.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/plugins/platform/opengl/)

---

## [Native OpenGLES runtime](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/plugins/platform/opengles/)

This plugin provides access to all OpenGLES core functions. OpenGLES API calls can be utilized when necessary.  
[docs.tellusim.com/core/plugins/platform/opengles](https://docs.tellusim.com/core/plugins/platform/opengles)

[![Native OpenGLES runtime](utils/browser/images/plugins/platform_opengles.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/plugins/platform/opengles/)

# Languages

## [C++ API reflection](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/plugins/system/reflection/)

This plugin enables reflection support for C++ API.  
[docs.tellusim.com/core/plugins/system/reflection](https://docs.tellusim.com/core/plugins/system/reflection)

[![C++ API reflection](utils/browser/images/plugins/system_reflection.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/plugins/system/reflection/)

---

## [C API binding](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/plugins/binding/capi/)

The C language API is an intermediary layer between C++ and other languages, such as C#, Rust, and others, that cannot directly import C++ code.  
[docs.tellusim.com/core/plugins/binding/capi](https://docs.tellusim.com/core/plugins/binding/capi)

[![C API binding](utils/browser/images/plugins/binding_c.jpg)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/plugins/binding/capi/)

---

## [C# API binding](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/plugins/binding/csharp/)

This plugin provides complete C# language access for all classes and functions. C API bridge plugin is required.  
[docs.tellusim.com/core/plugins/binding/csharp](https://docs.tellusim.com/core/plugins/binding/csharp)

[![C# API binding](utils/browser/images/plugins/binding_csharp.jpg)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/plugins/binding/csharp/)

---

## [Python API binding](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/plugins/binding/python/)

Python language API binding gives full access to Tellusim SDK from Python language. It is implemented on C Python API and does not require any additional dependencies.  
[docs.tellusim.com/core/plugins/binding/python](https://docs.tellusim.com/core/plugins/binding/python)

[![Python API binding](utils/browser/images/plugins/binding_python.jpg)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/plugins/binding/python/)

---

## [Rust API binding](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/plugins/binding/rust/)

This plugin provides complete Rust language access for all classes and functions. C API bridge plugin is required.  
[docs.tellusim.com/core/plugins/binding/rust](https://docs.tellusim.com/core/plugins/binding/rust)

[![Rust API binding](utils/browser/images/plugins/binding_rust.jpg)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/plugins/binding/rust/)

---

## [Swift API binding](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/plugins/binding/swift/)

This plugin provides complete Swift language access for all classes and functions.  
[docs.tellusim.com/core/plugins/binding/swift](https://docs.tellusim.com/core/plugins/binding/swift)

[![Swift API binding](utils/browser/images/plugins/binding_swift.jpg)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/plugins/binding/swift/)

---

## [Java/Kotlin API binding](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/plugins/binding/java/)

This plugin provides complete Java and Kotlin language access for all classes and functions.  
[docs.tellusim.com/core/plugins/binding/java](https://docs.tellusim.com/core/plugins/binding/java)

[![Java/Kotlin API binding](utils/browser/images/plugins/binding_java.jpg)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/plugins/binding/java/)

---

## [JavaScript API binding](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/plugins/binding/javascript/)

This plugin provides complete JavaScript language access for all classes and functions.  
[docs.tellusim.com/core/plugins/binding/javascript](https://docs.tellusim.com/core/plugins/binding/javascript)

[![JavaScript API binding](utils/browser/images/plugins/binding_javascript.jpg)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/plugins/binding/javascript/)

# Native

## [Native Direct3D12 runtime](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/native/d3d12_runtime/)

Drawing geometry using native Direct3D12 API calls.

[![Native Direct3D12 runtime](utils/browser/images/native/native_d3d12_runtime.jpg)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/native/d3d12_runtime/)

---

## [Native Direct3D11 runtime](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/native/d3d11_runtime/)

Drawing geometry using native Direct3D11 API calls.

[![Native Direct3D11 runtime](utils/browser/images/native/native_d3d11_runtime.jpg)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/native/d3d11_runtime/)

---

## [Native Metal runtime](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/native/mtl_runtime/)

Drawing geometry using native Metal API calls.

[![Native Metal runtime](utils/browser/images/native/native_mtl_runtime.jpg)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/native/mtl_runtime/)

---

## [Native Cuda runtime](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/native/cuda_runtime/)

Cuda runtime API with buffer interop.

[![Native Cuda runtime](utils/browser/images/native/native_cuda_runtime.jpg)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/native/cuda_runtime/)

---

## [Native ROCm runtime](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/native/hip_runtime/)

ROCm runtime API with buffer interop.

[![Native ROCm runtime](utils/browser/images/native/native_hip_runtime.jpg)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/native/hip_runtime/)

---

## [Native D3D12 texture](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/native/d3d12_texture/)

Using native D3D12 textures.

[![Native D3D12 texture](utils/browser/images/native/native_d3d12_texture.jpg)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/native/d3d12_texture/)

---

## [Native Cuda texture](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/native/cuda_texture/)

Cuda runtime API and texture interop.

[![Native Cuda texture](utils/browser/images/native/native_cuda_texture.jpg)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/native/cuda_texture/)

---

## [Native Direct3D12 pipeline](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/native/d3d12_pipeline/)

Creating native Direct3D12 pipeline.

[![Native Direct3D12 pipeline](utils/browser/images/native/native_d3d12_pipeline.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/native/d3d12_pipeline/)

---

## [Native Vulkan pipeline](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/native/vk_pipeline/)

Creating native Vulkan pipeline.

[![Native Vulkan pipeline](utils/browser/images/native/native_vk_pipeline.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/native/vk_pipeline/)

---

## [Native Metal pipeline](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/native/mtl_pipeline/)

Creating native Metal pipeline.

[![Native Metal pipeline](utils/browser/images/native/native_mtl_pipeline.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/native/mtl_pipeline/)

---

## [Embedding into Direct3D12](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/native/d3d12_window/)

Embedding into the nativeal Direct3D12 native window application.

[![Embedding into Direct3D12](utils/browser/images/native/native_d3d12_window.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/native/d3d12_window/)

---

## [Embedding into Direct3D11](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/native/d3d11_window/)

Embedding into the nativeal Direct3D11 native window application.

[![Embedding into Direct3D11](utils/browser/images/native/native_d3d11_window.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/native/d3d11_window/)

---

## [Embedding into Metal](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/native/mtl_window/)

Embedding into the nativeal Metal native window application (MTKView).

[![Embedding into Metal](utils/browser/images/native/native_mtl_window.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/native/mtl_window/)

# Tools

## [Tellusim Shader](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/tools/shader/)

Command-line interface to the Clay shader compiler.  
[docs.tellusim.com/core/tools/shader](https://docs.tellusim.com/core/tools/shader)

[![Tellusim Shader](utils/browser/images/tools/tellusim_shader.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/tools/shader/)

---

## [Tellusim Image](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/tools/image/)

Image conversion utility with batch processing support.  
[docs.tellusim.com/core/tools/image](https://docs.tellusim.com/core/tools/image)

[![Tellusim Image](utils/browser/images/tools/tellusim_image.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/tools/image/)

---

## [Tellusim Mesh](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/tools/mesh/)

Mesh conversion utility with batch processing support.  
[docs.tellusim.com/core/tools/mesh](https://docs.tellusim.com/core/tools/mesh)

[![Tellusim Mesh](utils/browser/images/tools/tellusim_mesh.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/tools/mesh/)

---

## [Tellusim Blob](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/tools/blob/)

Tool for generating embedded binary resources for applications.  
[docs.tellusim.com/core/tools/blob](https://docs.tellusim.com/core/tools/blob)

[![Tellusim Blob](utils/browser/images/tools/tellusim_blob.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/tools/blob/)

---

## [Tellusim Project](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/tools/project/)

Utility for generating project templates.  
[docs.tellusim.com/core/tools/project](https://docs.tellusim.com/core/tools/project)

[![Tellusim Project](utils/browser/images/tools/tellusim_project.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/tools/project/)

---

## [Tellusim Noise](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/tools/noise/)

Blue noise generation tool for stochastic sampling and rendering.  
[docs.tellusim.com/core/tools/noise](https://docs.tellusim.com/core/tools/noise)

[![Tellusim Noise](utils/browser/images/tools/tellusim_noise.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/tools/noise/)

# Tutorials

## [Hello Interop](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/manual/13_hello_interop/)

[docs.tellusim.com/core/tutorials/13_hello_interop](https://docs.tellusim.com/core/tutorials/13_hello_interop)

[![Hello Interop](utils/browser/images/manual/manual_13_hello_interop.jpg)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/manual/13_hello_interop/)

---

## [Hello Controller](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/manual/12_hello_controller/)

[docs.tellusim.com/core/tutorials/12_hello_controller](https://docs.tellusim.com/core/tutorials/12_hello_controller)

[![Hello Controller](utils/browser/images/manual/manual_12_hello_controller.jpg)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/manual/12_hello_controller/)

---

## [Hello Bindless](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/manual/11_hello_bindless/)

[docs.tellusim.com/core/tutorials/11_hello_bindless](https://docs.tellusim.com/core/tutorials/11_hello_bindless)

[![Hello Bindless](utils/browser/images/manual/manual_11_hello_bindless.jpg)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/manual/11_hello_bindless/)

---

## [Hello Image](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/manual/10_hello_image/)

[docs.tellusim.com/core/tutorials/10_hello_image/](https://docs.tellusim.com/core/tutorials/10_hello_image/)

[![Hello Image](utils/browser/images/manual/manual_10_hello_image.jpg)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/manual/10_hello_image/)

---

## [Hello Controls](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/manual/09_hello_controls/)

[docs.tellusim.com/core/tutorials/09_hello_controls/](https://docs.tellusim.com/core/tutorials/09_hello_controls/)

[![Hello Controls](utils/browser/images/manual/manual_09_hello_controls.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/manual/09_hello_controls/)

---

## [Hello Canvas](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/manual/08_hello_canvas/)

[docs.tellusim.com/core/tutorials/08_hello_canvas](https://docs.tellusim.com/core/tutorials/08_hello_canvas)

[![Hello Canvas](utils/browser/images/manual/manual_08_hello_canvas.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/manual/08_hello_canvas/)

---

## [Gaussian Splatting](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/manual/07_hello_splatting/)

[docs.tellusim.com/core/tutorials/07_hello_splatting/](https://docs.tellusim.com/core/tutorials/07_hello_splatting/)

[![Gaussian Splatting](utils/browser/images/manual/manual_07_hello_splatting.jpg)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/manual/07_hello_splatting/)

---

## [Ray Tracing with Traversal](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/manual/06_hello_traversal/)

[docs.tellusim.com/core/tutorials/06_hello_traversal/](https://docs.tellusim.com/core/tutorials/06_hello_traversal/)

[![Ray Tracing with Traversal](utils/browser/images/manual/manual_06_hello_traversal.jpg)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/manual/06_hello_traversal/)

---

## [Ray Tracing with Ray Queries](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/manual/05_hello_tracing/)

[docs.tellusim.com/core/tutorials/05_hello_tracing/](https://docs.tellusim.com/core/tutorials/05_hello_tracing/)

[![Ray Tracing with Ray Queries](utils/browser/images/manual/manual_05_hello_tracing.jpg)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/manual/05_hello_tracing/)

---

## [Compute rasterization](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/manual/04_hello_raster/)

[docs.tellusim.com/core/tutorials/04_hello_raster/](https://docs.tellusim.com/core/tutorials/04_hello_raster/)

[![Compute rasterization](utils/browser/images/manual/manual_04_hello_raster.jpg)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/manual/04_hello_raster/)

---

## [Hierarchical LOD Graphs](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/manual/03_hello_mesh/)

[docs.tellusim.com/core/tutorials/03_hello_mesh/](https://docs.tellusim.com/core/tutorials/03_hello_mesh/)

[![Hierarchical LOD Graphs](utils/browser/images/manual/manual_03_hello_mesh.jpg)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/manual/03_hello_mesh/)

---

## [Particles Simuation](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/manual/02_hello_compute/)

[docs.tellusim.com/core/tutorials/02_hello_compute](https://docs.tellusim.com/core/tutorials/02_hello_compute)

[![Particles Simuation](utils/browser/images/manual/manual_02_hello_compute.jpg)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/manual/02_hello_compute/)

---

## [USDZ Model Loading](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/manual/01_hello_usdz/)

[docs.tellusim.com/core/tutorials/01_hello_usdz](https://docs.tellusim.com/core/tutorials/01_hello_usdz)

[![USDZ Model Loading](utils/browser/images/manual/manual_01_hello_usdz.jpg)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/manual/01_hello_usdz/)

---

## [Hello Triangle](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/manual/00_hello_triangle/)

[docs.tellusim.com/core/tutorials/00_hello_triangle](https://docs.tellusim.com/core/tutorials/00_hello_triangle)

[![Hello Triangle](utils/browser/images/manual/manual_00_hello_triangle.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/samples/manual/00_hello_triangle/)

# Resources

## [Documentation](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/)

Access Tellusim Core SDK documentation online.  
[docs.tellusim.com/core](https://docs.tellusim.com/core)

[![Documentation](utils/browser/images/resources/documentation.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/)

---

## [Developer Forum](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/)

Join Tellusim Developer Forum to ask questions and explore community discussions.  
[forum.tellusim.com](https://forum.tellusim.com)

[![Developer Forum](utils/browser/images/resources/developer_forum.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/)

---

## [Local API Reference](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/)

Browse the offline C++ API reference for the Tellusim Core SDK.

[![Local API Reference](utils/browser/images/resources/api_reference.png)](https://github.com/Tellusim/Tellusim_Core_SDK/tree/main/)

