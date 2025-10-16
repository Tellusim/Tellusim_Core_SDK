// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

// enums
public prefix func ~(e: Directory.Attributes) -> Directory.Attributes { Directory.Attributes(rawValue: ~e.rawValue)! }
public func |(e0: Directory.Attributes, e1: Directory.Attributes) -> Directory.Attributes { Directory.Attributes(rawValue: (e0.rawValue | e1.rawValue))! }
public func &(e0: Directory.Attributes, e1: Directory.Attributes) -> Directory.Attributes { Directory.Attributes(rawValue: (e0.rawValue & e1.rawValue))! }
public func |=(e0: inout Directory.Attributes, e1: Directory.Attributes) { e0 = Directory.Attributes(rawValue: (e0.rawValue | e1.rawValue))! }
public func &=(e0: inout Directory.Attributes, e1: Directory.Attributes) { e0 = Directory.Attributes(rawValue: (e0.rawValue & e1.rawValue))! }
public prefix func ~(e: Image.Flags) -> Image.Flags { Image.Flags(rawValue: ~e.rawValue)! }
public func |(e0: Image.Flags, e1: Image.Flags) -> Image.Flags { Image.Flags(rawValue: (e0.rawValue | e1.rawValue))! }
public func &(e0: Image.Flags, e1: Image.Flags) -> Image.Flags { Image.Flags(rawValue: (e0.rawValue & e1.rawValue))! }
public func |=(e0: inout Image.Flags, e1: Image.Flags) { e0 = Image.Flags(rawValue: (e0.rawValue | e1.rawValue))! }
public func &=(e0: inout Image.Flags, e1: Image.Flags) { e0 = Image.Flags(rawValue: (e0.rawValue & e1.rawValue))! }
public prefix func ~(e: MeshMaterial.Flags) -> MeshMaterial.Flags { MeshMaterial.Flags(rawValue: ~e.rawValue)! }
public func |(e0: MeshMaterial.Flags, e1: MeshMaterial.Flags) -> MeshMaterial.Flags { MeshMaterial.Flags(rawValue: (e0.rawValue | e1.rawValue))! }
public func &(e0: MeshMaterial.Flags, e1: MeshMaterial.Flags) -> MeshMaterial.Flags { MeshMaterial.Flags(rawValue: (e0.rawValue & e1.rawValue))! }
public func |=(e0: inout MeshMaterial.Flags, e1: MeshMaterial.Flags) { e0 = MeshMaterial.Flags(rawValue: (e0.rawValue | e1.rawValue))! }
public func &=(e0: inout MeshMaterial.Flags, e1: MeshMaterial.Flags) { e0 = MeshMaterial.Flags(rawValue: (e0.rawValue & e1.rawValue))! }
public prefix func ~(e: Mesh.Flags) -> Mesh.Flags { Mesh.Flags(rawValue: ~e.rawValue)! }
public func |(e0: Mesh.Flags, e1: Mesh.Flags) -> Mesh.Flags { Mesh.Flags(rawValue: (e0.rawValue | e1.rawValue))! }
public func &(e0: Mesh.Flags, e1: Mesh.Flags) -> Mesh.Flags { Mesh.Flags(rawValue: (e0.rawValue & e1.rawValue))! }
public func |=(e0: inout Mesh.Flags, e1: Mesh.Flags) { e0 = Mesh.Flags(rawValue: (e0.rawValue | e1.rawValue))! }
public func &=(e0: inout Mesh.Flags, e1: Mesh.Flags) { e0 = Mesh.Flags(rawValue: (e0.rawValue & e1.rawValue))! }
public prefix func ~(e: Buffer.Flags) -> Buffer.Flags { Buffer.Flags(rawValue: ~e.rawValue)! }
public func |(e0: Buffer.Flags, e1: Buffer.Flags) -> Buffer.Flags { Buffer.Flags(rawValue: (e0.rawValue | e1.rawValue))! }
public func &(e0: Buffer.Flags, e1: Buffer.Flags) -> Buffer.Flags { Buffer.Flags(rawValue: (e0.rawValue & e1.rawValue))! }
public func |=(e0: inout Buffer.Flags, e1: Buffer.Flags) { e0 = Buffer.Flags(rawValue: (e0.rawValue | e1.rawValue))! }
public func &=(e0: inout Buffer.Flags, e1: Buffer.Flags) { e0 = Buffer.Flags(rawValue: (e0.rawValue & e1.rawValue))! }
public prefix func ~(e: Fence.Flags) -> Fence.Flags { Fence.Flags(rawValue: ~e.rawValue)! }
public func |(e0: Fence.Flags, e1: Fence.Flags) -> Fence.Flags { Fence.Flags(rawValue: (e0.rawValue | e1.rawValue))! }
public func &(e0: Fence.Flags, e1: Fence.Flags) -> Fence.Flags { Fence.Flags(rawValue: (e0.rawValue & e1.rawValue))! }
public func |=(e0: inout Fence.Flags, e1: Fence.Flags) { e0 = Fence.Flags(rawValue: (e0.rawValue | e1.rawValue))! }
public func &=(e0: inout Fence.Flags, e1: Fence.Flags) { e0 = Fence.Flags(rawValue: (e0.rawValue & e1.rawValue))! }
public prefix func ~(e: Shader.Mask) -> Shader.Mask { Shader.Mask(rawValue: ~e.rawValue)! }
public func |(e0: Shader.Mask, e1: Shader.Mask) -> Shader.Mask { Shader.Mask(rawValue: (e0.rawValue | e1.rawValue))! }
public func &(e0: Shader.Mask, e1: Shader.Mask) -> Shader.Mask { Shader.Mask(rawValue: (e0.rawValue & e1.rawValue))! }
public func |=(e0: inout Shader.Mask, e1: Shader.Mask) { e0 = Shader.Mask(rawValue: (e0.rawValue | e1.rawValue))! }
public func &=(e0: inout Shader.Mask, e1: Shader.Mask) { e0 = Shader.Mask(rawValue: (e0.rawValue & e1.rawValue))! }
public prefix func ~(e: ShaderCompiler.Flags) -> ShaderCompiler.Flags { ShaderCompiler.Flags(rawValue: ~e.rawValue)! }
public func |(e0: ShaderCompiler.Flags, e1: ShaderCompiler.Flags) -> ShaderCompiler.Flags { ShaderCompiler.Flags(rawValue: (e0.rawValue | e1.rawValue))! }
public func &(e0: ShaderCompiler.Flags, e1: ShaderCompiler.Flags) -> ShaderCompiler.Flags { ShaderCompiler.Flags(rawValue: (e0.rawValue & e1.rawValue))! }
public func |=(e0: inout ShaderCompiler.Flags, e1: ShaderCompiler.Flags) { e0 = ShaderCompiler.Flags(rawValue: (e0.rawValue | e1.rawValue))! }
public func &=(e0: inout ShaderCompiler.Flags, e1: ShaderCompiler.Flags) { e0 = ShaderCompiler.Flags(rawValue: (e0.rawValue & e1.rawValue))! }
public prefix func ~(e: Texture.Flags) -> Texture.Flags { Texture.Flags(rawValue: ~e.rawValue)! }
public func |(e0: Texture.Flags, e1: Texture.Flags) -> Texture.Flags { Texture.Flags(rawValue: (e0.rawValue | e1.rawValue))! }
public func &(e0: Texture.Flags, e1: Texture.Flags) -> Texture.Flags { Texture.Flags(rawValue: (e0.rawValue & e1.rawValue))! }
public func |=(e0: inout Texture.Flags, e1: Texture.Flags) { e0 = Texture.Flags(rawValue: (e0.rawValue | e1.rawValue))! }
public func &=(e0: inout Texture.Flags, e1: Texture.Flags) { e0 = Texture.Flags(rawValue: (e0.rawValue & e1.rawValue))! }
public prefix func ~(e: Tracing.Flags) -> Tracing.Flags { Tracing.Flags(rawValue: ~e.rawValue)! }
public func |(e0: Tracing.Flags, e1: Tracing.Flags) -> Tracing.Flags { Tracing.Flags(rawValue: (e0.rawValue | e1.rawValue))! }
public func &(e0: Tracing.Flags, e1: Tracing.Flags) -> Tracing.Flags { Tracing.Flags(rawValue: (e0.rawValue & e1.rawValue))! }
public func |=(e0: inout Tracing.Flags, e1: Tracing.Flags) { e0 = Tracing.Flags(rawValue: (e0.rawValue | e1.rawValue))! }
public func &=(e0: inout Tracing.Flags, e1: Tracing.Flags) { e0 = Tracing.Flags(rawValue: (e0.rawValue & e1.rawValue))! }
public prefix func ~(e: Target.Operation) -> Target.Operation { Target.Operation(rawValue: ~e.rawValue)! }
public func |(e0: Target.Operation, e1: Target.Operation) -> Target.Operation { Target.Operation(rawValue: (e0.rawValue | e1.rawValue))! }
public func &(e0: Target.Operation, e1: Target.Operation) -> Target.Operation { Target.Operation(rawValue: (e0.rawValue & e1.rawValue))! }
public func |=(e0: inout Target.Operation, e1: Target.Operation) { e0 = Target.Operation(rawValue: (e0.rawValue | e1.rawValue))! }
public func &=(e0: inout Target.Operation, e1: Target.Operation) { e0 = Target.Operation(rawValue: (e0.rawValue & e1.rawValue))! }
public prefix func ~(e: Pipeline.ColorMask) -> Pipeline.ColorMask { Pipeline.ColorMask(rawValue: ~e.rawValue)! }
public func |(e0: Pipeline.ColorMask, e1: Pipeline.ColorMask) -> Pipeline.ColorMask { Pipeline.ColorMask(rawValue: (e0.rawValue | e1.rawValue))! }
public func &(e0: Pipeline.ColorMask, e1: Pipeline.ColorMask) -> Pipeline.ColorMask { Pipeline.ColorMask(rawValue: (e0.rawValue & e1.rawValue))! }
public func |=(e0: inout Pipeline.ColorMask, e1: Pipeline.ColorMask) { e0 = Pipeline.ColorMask(rawValue: (e0.rawValue | e1.rawValue))! }
public func &=(e0: inout Pipeline.ColorMask, e1: Pipeline.ColorMask) { e0 = Pipeline.ColorMask(rawValue: (e0.rawValue & e1.rawValue))! }
public prefix func ~(e: Window.Flags) -> Window.Flags { Window.Flags(rawValue: ~e.rawValue)! }
public func |(e0: Window.Flags, e1: Window.Flags) -> Window.Flags { Window.Flags(rawValue: (e0.rawValue | e1.rawValue))! }
public func &(e0: Window.Flags, e1: Window.Flags) -> Window.Flags { Window.Flags(rawValue: (e0.rawValue & e1.rawValue))! }
public func |=(e0: inout Window.Flags, e1: Window.Flags) { e0 = Window.Flags(rawValue: (e0.rawValue | e1.rawValue))! }
public func &=(e0: inout Window.Flags, e1: Window.Flags) { e0 = Window.Flags(rawValue: (e0.rawValue & e1.rawValue))! }
public prefix func ~(e: Window.Button) -> Window.Button { Window.Button(rawValue: ~e.rawValue)! }
public func |(e0: Window.Button, e1: Window.Button) -> Window.Button { Window.Button(rawValue: (e0.rawValue | e1.rawValue))! }
public func &(e0: Window.Button, e1: Window.Button) -> Window.Button { Window.Button(rawValue: (e0.rawValue & e1.rawValue))! }
public func |=(e0: inout Window.Button, e1: Window.Button) { e0 = Window.Button(rawValue: (e0.rawValue | e1.rawValue))! }
public func &=(e0: inout Window.Button, e1: Window.Button) { e0 = Window.Button(rawValue: (e0.rawValue & e1.rawValue))! }
public prefix func ~(e: CanvasElement.Align) -> CanvasElement.Align { CanvasElement.Align(rawValue: ~e.rawValue)! }
public func |(e0: CanvasElement.Align, e1: CanvasElement.Align) -> CanvasElement.Align { CanvasElement.Align(rawValue: (e0.rawValue | e1.rawValue))! }
public func &(e0: CanvasElement.Align, e1: CanvasElement.Align) -> CanvasElement.Align { CanvasElement.Align(rawValue: (e0.rawValue & e1.rawValue))! }
public func |=(e0: inout CanvasElement.Align, e1: CanvasElement.Align) { e0 = CanvasElement.Align(rawValue: (e0.rawValue | e1.rawValue))! }
public func &=(e0: inout CanvasElement.Align, e1: CanvasElement.Align) { e0 = CanvasElement.Align(rawValue: (e0.rawValue & e1.rawValue))! }
public prefix func ~(e: CanvasElement.Stack) -> CanvasElement.Stack { CanvasElement.Stack(rawValue: ~e.rawValue)! }
public func |(e0: CanvasElement.Stack, e1: CanvasElement.Stack) -> CanvasElement.Stack { CanvasElement.Stack(rawValue: (e0.rawValue | e1.rawValue))! }
public func &(e0: CanvasElement.Stack, e1: CanvasElement.Stack) -> CanvasElement.Stack { CanvasElement.Stack(rawValue: (e0.rawValue & e1.rawValue))! }
public func |=(e0: inout CanvasElement.Stack, e1: CanvasElement.Stack) { e0 = CanvasElement.Stack(rawValue: (e0.rawValue | e1.rawValue))! }
public func &=(e0: inout CanvasElement.Stack, e1: CanvasElement.Stack) { e0 = CanvasElement.Stack(rawValue: (e0.rawValue & e1.rawValue))! }
public prefix func ~(e: Control.Align) -> Control.Align { Control.Align(rawValue: ~e.rawValue)! }
public func |(e0: Control.Align, e1: Control.Align) -> Control.Align { Control.Align(rawValue: (e0.rawValue | e1.rawValue))! }
public func &(e0: Control.Align, e1: Control.Align) -> Control.Align { Control.Align(rawValue: (e0.rawValue & e1.rawValue))! }
public func |=(e0: inout Control.Align, e1: Control.Align) { e0 = Control.Align(rawValue: (e0.rawValue | e1.rawValue))! }
public func &=(e0: inout Control.Align, e1: Control.Align) { e0 = Control.Align(rawValue: (e0.rawValue & e1.rawValue))! }
public prefix func ~(e: Control.Button) -> Control.Button { Control.Button(rawValue: ~e.rawValue)! }
public func |(e0: Control.Button, e1: Control.Button) -> Control.Button { Control.Button(rawValue: (e0.rawValue | e1.rawValue))! }
public func &(e0: Control.Button, e1: Control.Button) -> Control.Button { Control.Button(rawValue: (e0.rawValue & e1.rawValue))! }
public func |=(e0: inout Control.Button, e1: Control.Button) { e0 = Control.Button(rawValue: (e0.rawValue | e1.rawValue))! }
public func &=(e0: inout Control.Button, e1: Control.Button) { e0 = Control.Button(rawValue: (e0.rawValue & e1.rawValue))! }
public prefix func ~(e: DialogMessage.Flags) -> DialogMessage.Flags { DialogMessage.Flags(rawValue: ~e.rawValue)! }
public func |(e0: DialogMessage.Flags, e1: DialogMessage.Flags) -> DialogMessage.Flags { DialogMessage.Flags(rawValue: (e0.rawValue | e1.rawValue))! }
public func &(e0: DialogMessage.Flags, e1: DialogMessage.Flags) -> DialogMessage.Flags { DialogMessage.Flags(rawValue: (e0.rawValue & e1.rawValue))! }
public func |=(e0: inout DialogMessage.Flags, e1: DialogMessage.Flags) { e0 = DialogMessage.Flags(rawValue: (e0.rawValue | e1.rawValue))! }
public func &=(e0: inout DialogMessage.Flags, e1: DialogMessage.Flags) { e0 = DialogMessage.Flags(rawValue: (e0.rawValue & e1.rawValue))! }
public prefix func ~(e: DialogFileOpen.Flags) -> DialogFileOpen.Flags { DialogFileOpen.Flags(rawValue: ~e.rawValue)! }
public func |(e0: DialogFileOpen.Flags, e1: DialogFileOpen.Flags) -> DialogFileOpen.Flags { DialogFileOpen.Flags(rawValue: (e0.rawValue | e1.rawValue))! }
public func &(e0: DialogFileOpen.Flags, e1: DialogFileOpen.Flags) -> DialogFileOpen.Flags { DialogFileOpen.Flags(rawValue: (e0.rawValue & e1.rawValue))! }
public func |=(e0: inout DialogFileOpen.Flags, e1: DialogFileOpen.Flags) { e0 = DialogFileOpen.Flags(rawValue: (e0.rawValue | e1.rawValue))! }
public func &=(e0: inout DialogFileOpen.Flags, e1: DialogFileOpen.Flags) { e0 = DialogFileOpen.Flags(rawValue: (e0.rawValue & e1.rawValue))! }
public prefix func ~(e: DialogFileSave.Flags) -> DialogFileSave.Flags { DialogFileSave.Flags(rawValue: ~e.rawValue)! }
public func |(e0: DialogFileSave.Flags, e1: DialogFileSave.Flags) -> DialogFileSave.Flags { DialogFileSave.Flags(rawValue: (e0.rawValue | e1.rawValue))! }
public func &(e0: DialogFileSave.Flags, e1: DialogFileSave.Flags) -> DialogFileSave.Flags { DialogFileSave.Flags(rawValue: (e0.rawValue & e1.rawValue))! }
public func |=(e0: inout DialogFileSave.Flags, e1: DialogFileSave.Flags) { e0 = DialogFileSave.Flags(rawValue: (e0.rawValue | e1.rawValue))! }
public func &=(e0: inout DialogFileSave.Flags, e1: DialogFileSave.Flags) { e0 = DialogFileSave.Flags(rawValue: (e0.rawValue & e1.rawValue))! }
public prefix func ~(e: DialogDirectory.Flags) -> DialogDirectory.Flags { DialogDirectory.Flags(rawValue: ~e.rawValue)! }
public func |(e0: DialogDirectory.Flags, e1: DialogDirectory.Flags) -> DialogDirectory.Flags { DialogDirectory.Flags(rawValue: (e0.rawValue | e1.rawValue))! }
public func &(e0: DialogDirectory.Flags, e1: DialogDirectory.Flags) -> DialogDirectory.Flags { DialogDirectory.Flags(rawValue: (e0.rawValue & e1.rawValue))! }
public func |=(e0: inout DialogDirectory.Flags, e1: DialogDirectory.Flags) { e0 = DialogDirectory.Flags(rawValue: (e0.rawValue | e1.rawValue))! }
public func &=(e0: inout DialogDirectory.Flags, e1: DialogDirectory.Flags) { e0 = DialogDirectory.Flags(rawValue: (e0.rawValue & e1.rawValue))! }
public prefix func ~(e: DialogProgress.Flags) -> DialogProgress.Flags { DialogProgress.Flags(rawValue: ~e.rawValue)! }
public func |(e0: DialogProgress.Flags, e1: DialogProgress.Flags) -> DialogProgress.Flags { DialogProgress.Flags(rawValue: (e0.rawValue | e1.rawValue))! }
public func &(e0: DialogProgress.Flags, e1: DialogProgress.Flags) -> DialogProgress.Flags { DialogProgress.Flags(rawValue: (e0.rawValue & e1.rawValue))! }
public func |=(e0: inout DialogProgress.Flags, e1: DialogProgress.Flags) { e0 = DialogProgress.Flags(rawValue: (e0.rawValue | e1.rawValue))! }
public func &=(e0: inout DialogProgress.Flags, e1: DialogProgress.Flags) { e0 = DialogProgress.Flags(rawValue: (e0.rawValue & e1.rawValue))! }
public prefix func ~(e: DialogColor.Flags) -> DialogColor.Flags { DialogColor.Flags(rawValue: ~e.rawValue)! }
public func |(e0: DialogColor.Flags, e1: DialogColor.Flags) -> DialogColor.Flags { DialogColor.Flags(rawValue: (e0.rawValue | e1.rawValue))! }
public func &(e0: DialogColor.Flags, e1: DialogColor.Flags) -> DialogColor.Flags { DialogColor.Flags(rawValue: (e0.rawValue & e1.rawValue))! }
public func |=(e0: inout DialogColor.Flags, e1: DialogColor.Flags) { e0 = DialogColor.Flags(rawValue: (e0.rawValue | e1.rawValue))! }
public func &=(e0: inout DialogColor.Flags, e1: DialogColor.Flags) { e0 = DialogColor.Flags(rawValue: (e0.rawValue & e1.rawValue))! }
public prefix func ~(e: DialogMenu.Flags) -> DialogMenu.Flags { DialogMenu.Flags(rawValue: ~e.rawValue)! }
public func |(e0: DialogMenu.Flags, e1: DialogMenu.Flags) -> DialogMenu.Flags { DialogMenu.Flags(rawValue: (e0.rawValue | e1.rawValue))! }
public func &(e0: DialogMenu.Flags, e1: DialogMenu.Flags) -> DialogMenu.Flags { DialogMenu.Flags(rawValue: (e0.rawValue & e1.rawValue))! }
public func |=(e0: inout DialogMenu.Flags, e1: DialogMenu.Flags) { e0 = DialogMenu.Flags(rawValue: (e0.rawValue | e1.rawValue))! }
public func &=(e0: inout DialogMenu.Flags, e1: DialogMenu.Flags) { e0 = DialogMenu.Flags(rawValue: (e0.rawValue & e1.rawValue))! }
public prefix func ~(e: CubeFilter.Flags) -> CubeFilter.Flags { CubeFilter.Flags(rawValue: ~e.rawValue)! }
public func |(e0: CubeFilter.Flags, e1: CubeFilter.Flags) -> CubeFilter.Flags { CubeFilter.Flags(rawValue: (e0.rawValue | e1.rawValue))! }
public func &(e0: CubeFilter.Flags, e1: CubeFilter.Flags) -> CubeFilter.Flags { CubeFilter.Flags(rawValue: (e0.rawValue & e1.rawValue))! }
public func |=(e0: inout CubeFilter.Flags, e1: CubeFilter.Flags) { e0 = CubeFilter.Flags(rawValue: (e0.rawValue | e1.rawValue))! }
public func &=(e0: inout CubeFilter.Flags, e1: CubeFilter.Flags) { e0 = CubeFilter.Flags(rawValue: (e0.rawValue & e1.rawValue))! }
public prefix func ~(e: DecoderJPEG.Flags) -> DecoderJPEG.Flags { DecoderJPEG.Flags(rawValue: ~e.rawValue)! }
public func |(e0: DecoderJPEG.Flags, e1: DecoderJPEG.Flags) -> DecoderJPEG.Flags { DecoderJPEG.Flags(rawValue: (e0.rawValue | e1.rawValue))! }
public func &(e0: DecoderJPEG.Flags, e1: DecoderJPEG.Flags) -> DecoderJPEG.Flags { DecoderJPEG.Flags(rawValue: (e0.rawValue & e1.rawValue))! }
public func |=(e0: inout DecoderJPEG.Flags, e1: DecoderJPEG.Flags) { e0 = DecoderJPEG.Flags(rawValue: (e0.rawValue | e1.rawValue))! }
public func &=(e0: inout DecoderJPEG.Flags, e1: DecoderJPEG.Flags) { e0 = DecoderJPEG.Flags(rawValue: (e0.rawValue & e1.rawValue))! }
public prefix func ~(e: EncoderBC15.Flags) -> EncoderBC15.Flags { EncoderBC15.Flags(rawValue: ~e.rawValue)! }
public func |(e0: EncoderBC15.Flags, e1: EncoderBC15.Flags) -> EncoderBC15.Flags { EncoderBC15.Flags(rawValue: (e0.rawValue | e1.rawValue))! }
public func &(e0: EncoderBC15.Flags, e1: EncoderBC15.Flags) -> EncoderBC15.Flags { EncoderBC15.Flags(rawValue: (e0.rawValue & e1.rawValue))! }
public func |=(e0: inout EncoderBC15.Flags, e1: EncoderBC15.Flags) { e0 = EncoderBC15.Flags(rawValue: (e0.rawValue | e1.rawValue))! }
public func &=(e0: inout EncoderBC15.Flags, e1: EncoderBC15.Flags) { e0 = EncoderBC15.Flags(rawValue: (e0.rawValue & e1.rawValue))! }
public prefix func ~(e: EncoderBC67.Flags) -> EncoderBC67.Flags { EncoderBC67.Flags(rawValue: ~e.rawValue)! }
public func |(e0: EncoderBC67.Flags, e1: EncoderBC67.Flags) -> EncoderBC67.Flags { EncoderBC67.Flags(rawValue: (e0.rawValue | e1.rawValue))! }
public func &(e0: EncoderBC67.Flags, e1: EncoderBC67.Flags) -> EncoderBC67.Flags { EncoderBC67.Flags(rawValue: (e0.rawValue & e1.rawValue))! }
public func |=(e0: inout EncoderBC67.Flags, e1: EncoderBC67.Flags) { e0 = EncoderBC67.Flags(rawValue: (e0.rawValue | e1.rawValue))! }
public func &=(e0: inout EncoderBC67.Flags, e1: EncoderBC67.Flags) { e0 = EncoderBC67.Flags(rawValue: (e0.rawValue & e1.rawValue))! }
public prefix func ~(e: EncoderASTC.Flags) -> EncoderASTC.Flags { EncoderASTC.Flags(rawValue: ~e.rawValue)! }
public func |(e0: EncoderASTC.Flags, e1: EncoderASTC.Flags) -> EncoderASTC.Flags { EncoderASTC.Flags(rawValue: (e0.rawValue | e1.rawValue))! }
public func &(e0: EncoderASTC.Flags, e1: EncoderASTC.Flags) -> EncoderASTC.Flags { EncoderASTC.Flags(rawValue: (e0.rawValue & e1.rawValue))! }
public func |=(e0: inout EncoderASTC.Flags, e1: EncoderASTC.Flags) { e0 = EncoderASTC.Flags(rawValue: (e0.rawValue | e1.rawValue))! }
public func &=(e0: inout EncoderASTC.Flags, e1: EncoderASTC.Flags) { e0 = EncoderASTC.Flags(rawValue: (e0.rawValue & e1.rawValue))! }
public prefix func ~(e: MeshModel.Flags) -> MeshModel.Flags { MeshModel.Flags(rawValue: ~e.rawValue)! }
public func |(e0: MeshModel.Flags, e1: MeshModel.Flags) -> MeshModel.Flags { MeshModel.Flags(rawValue: (e0.rawValue | e1.rawValue))! }
public func &(e0: MeshModel.Flags, e1: MeshModel.Flags) -> MeshModel.Flags { MeshModel.Flags(rawValue: (e0.rawValue & e1.rawValue))! }
public func |=(e0: inout MeshModel.Flags, e1: MeshModel.Flags) { e0 = MeshModel.Flags(rawValue: (e0.rawValue | e1.rawValue))! }
public func &=(e0: inout MeshModel.Flags, e1: MeshModel.Flags) { e0 = MeshModel.Flags(rawValue: (e0.rawValue & e1.rawValue))! }
public prefix func ~(e: SeparableFilter.Flags) -> SeparableFilter.Flags { SeparableFilter.Flags(rawValue: ~e.rawValue)! }
public func |(e0: SeparableFilter.Flags, e1: SeparableFilter.Flags) -> SeparableFilter.Flags { SeparableFilter.Flags(rawValue: (e0.rawValue | e1.rawValue))! }
public func &(e0: SeparableFilter.Flags, e1: SeparableFilter.Flags) -> SeparableFilter.Flags { SeparableFilter.Flags(rawValue: (e0.rawValue & e1.rawValue))! }
public func |=(e0: inout SeparableFilter.Flags, e1: SeparableFilter.Flags) { e0 = SeparableFilter.Flags(rawValue: (e0.rawValue | e1.rawValue))! }
public func &=(e0: inout SeparableFilter.Flags, e1: SeparableFilter.Flags) { e0 = SeparableFilter.Flags(rawValue: (e0.rawValue & e1.rawValue))! }
public prefix func ~(e: PrefixScan.Flags) -> PrefixScan.Flags { PrefixScan.Flags(rawValue: ~e.rawValue)! }
public func |(e0: PrefixScan.Flags, e1: PrefixScan.Flags) -> PrefixScan.Flags { PrefixScan.Flags(rawValue: (e0.rawValue | e1.rawValue))! }
public func &(e0: PrefixScan.Flags, e1: PrefixScan.Flags) -> PrefixScan.Flags { PrefixScan.Flags(rawValue: (e0.rawValue & e1.rawValue))! }
public func |=(e0: inout PrefixScan.Flags, e1: PrefixScan.Flags) { e0 = PrefixScan.Flags(rawValue: (e0.rawValue | e1.rawValue))! }
public func &=(e0: inout PrefixScan.Flags, e1: PrefixScan.Flags) { e0 = PrefixScan.Flags(rawValue: (e0.rawValue & e1.rawValue))! }
public prefix func ~(e: RadixSort.Flags) -> RadixSort.Flags { RadixSort.Flags(rawValue: ~e.rawValue)! }
public func |(e0: RadixSort.Flags, e1: RadixSort.Flags) -> RadixSort.Flags { RadixSort.Flags(rawValue: (e0.rawValue | e1.rawValue))! }
public func &(e0: RadixSort.Flags, e1: RadixSort.Flags) -> RadixSort.Flags { RadixSort.Flags(rawValue: (e0.rawValue & e1.rawValue))! }
public func |=(e0: inout RadixSort.Flags, e1: RadixSort.Flags) { e0 = RadixSort.Flags(rawValue: (e0.rawValue | e1.rawValue))! }
public func &=(e0: inout RadixSort.Flags, e1: RadixSort.Flags) { e0 = RadixSort.Flags(rawValue: (e0.rawValue & e1.rawValue))! }
public prefix func ~(e: BitonicSort.Flags) -> BitonicSort.Flags { BitonicSort.Flags(rawValue: ~e.rawValue)! }
public func |(e0: BitonicSort.Flags, e1: BitonicSort.Flags) -> BitonicSort.Flags { BitonicSort.Flags(rawValue: (e0.rawValue | e1.rawValue))! }
public func &(e0: BitonicSort.Flags, e1: BitonicSort.Flags) -> BitonicSort.Flags { BitonicSort.Flags(rawValue: (e0.rawValue & e1.rawValue))! }
public func |=(e0: inout BitonicSort.Flags, e1: BitonicSort.Flags) { e0 = BitonicSort.Flags(rawValue: (e0.rawValue | e1.rawValue))! }
public func &=(e0: inout BitonicSort.Flags, e1: BitonicSort.Flags) { e0 = BitonicSort.Flags(rawValue: (e0.rawValue & e1.rawValue))! }
public prefix func ~(e: SpatialTree.Flags) -> SpatialTree.Flags { SpatialTree.Flags(rawValue: ~e.rawValue)! }
public func |(e0: SpatialTree.Flags, e1: SpatialTree.Flags) -> SpatialTree.Flags { SpatialTree.Flags(rawValue: (e0.rawValue | e1.rawValue))! }
public func &(e0: SpatialTree.Flags, e1: SpatialTree.Flags) -> SpatialTree.Flags { SpatialTree.Flags(rawValue: (e0.rawValue & e1.rawValue))! }
public func |=(e0: inout SpatialTree.Flags, e1: SpatialTree.Flags) { e0 = SpatialTree.Flags(rawValue: (e0.rawValue | e1.rawValue))! }
public func &=(e0: inout SpatialTree.Flags, e1: SpatialTree.Flags) { e0 = SpatialTree.Flags(rawValue: (e0.rawValue & e1.rawValue))! }
public prefix func ~(e: FourierTransform.Flags) -> FourierTransform.Flags { FourierTransform.Flags(rawValue: ~e.rawValue)! }
public func |(e0: FourierTransform.Flags, e1: FourierTransform.Flags) -> FourierTransform.Flags { FourierTransform.Flags(rawValue: (e0.rawValue | e1.rawValue))! }
public func &(e0: FourierTransform.Flags, e1: FourierTransform.Flags) -> FourierTransform.Flags { FourierTransform.Flags(rawValue: (e0.rawValue & e1.rawValue))! }
public func |=(e0: inout FourierTransform.Flags, e1: FourierTransform.Flags) { e0 = FourierTransform.Flags(rawValue: (e0.rawValue | e1.rawValue))! }
public func &=(e0: inout FourierTransform.Flags, e1: FourierTransform.Flags) { e0 = FourierTransform.Flags(rawValue: (e0.rawValue & e1.rawValue))! }
public prefix func ~(e: TensorGraph.Flags) -> TensorGraph.Flags { TensorGraph.Flags(rawValue: ~e.rawValue)! }
public func |(e0: TensorGraph.Flags, e1: TensorGraph.Flags) -> TensorGraph.Flags { TensorGraph.Flags(rawValue: (e0.rawValue | e1.rawValue))! }
public func &(e0: TensorGraph.Flags, e1: TensorGraph.Flags) -> TensorGraph.Flags { TensorGraph.Flags(rawValue: (e0.rawValue & e1.rawValue))! }
public func |=(e0: inout TensorGraph.Flags, e1: TensorGraph.Flags) { e0 = TensorGraph.Flags(rawValue: (e0.rawValue | e1.rawValue))! }
public func &=(e0: inout TensorGraph.Flags, e1: TensorGraph.Flags) { e0 = TensorGraph.Flags(rawValue: (e0.rawValue & e1.rawValue))! }
public prefix func ~(e: TensorGraph.Masks) -> TensorGraph.Masks { TensorGraph.Masks(rawValue: ~e.rawValue)! }
public func |(e0: TensorGraph.Masks, e1: TensorGraph.Masks) -> TensorGraph.Masks { TensorGraph.Masks(rawValue: (e0.rawValue | e1.rawValue))! }
public func &(e0: TensorGraph.Masks, e1: TensorGraph.Masks) -> TensorGraph.Masks { TensorGraph.Masks(rawValue: (e0.rawValue & e1.rawValue))! }
public func |=(e0: inout TensorGraph.Masks, e1: TensorGraph.Masks) { e0 = TensorGraph.Masks(rawValue: (e0.rawValue | e1.rawValue))! }
public func &=(e0: inout TensorGraph.Masks, e1: TensorGraph.Masks) { e0 = TensorGraph.Masks(rawValue: (e0.rawValue & e1.rawValue))! }

// classes
public prefix func!(v: Async) -> Bool { !v.isValidPtr() }
public prefix func!(v: Stream) -> Bool { !v.isValidPtr() }
public prefix func!(v: Blob) -> Bool { !v.isValidPtr() }
public prefix func!(v: File) -> Bool { !v.isValidPtr() }
public prefix func!(v: Socket) -> Bool { !v.isValidPtr() }
public prefix func!(v: SocketSSL) -> Bool { !v.isValidPtr() }
public prefix func!(v: Source) -> Bool { !v.isValidPtr() }
public prefix func!(v: Date) -> Bool { !v.isValidPtr() }
public prefix func!(v: Info) -> Bool { !v.isValidPtr() }
public prefix func!(v: Directory) -> Bool { !v.isValidPtr() }
public prefix func!(v: Image) -> Bool { !v.isValidPtr() }
public prefix func!(v: MeshNode) -> Bool { !v.isValidPtr() }
public prefix func!(v: MeshIndices) -> Bool { !v.isValidPtr() }
public prefix func!(v: MeshAttribute) -> Bool { !v.isValidPtr() }
public prefix func!(v: MeshJoint) -> Bool { !v.isValidPtr() }
public prefix func!(v: MeshMaterial) -> Bool { !v.isValidPtr() }
public prefix func!(v: MeshGeometry) -> Bool { !v.isValidPtr() }
public prefix func!(v: MeshTransform) -> Bool { !v.isValidPtr() }
public prefix func!(v: MeshAnimation) -> Bool { !v.isValidPtr() }
public prefix func!(v: MeshAttachment) -> Bool { !v.isValidPtr() }
public prefix func!(v: Mesh) -> Bool { !v.isValidPtr() }
public prefix func!(v: Json) -> Bool { !v.isValidPtr() }
public prefix func!(v: Xml) -> Bool { !v.isValidPtr() }
public prefix func!(v: Buffer) -> Bool { !v.isValidPtr() }
public prefix func!(v: BufferTable) -> Bool { !v.isValidPtr() }
public prefix func!(v: D3D12Buffer) -> Bool { !v.isValidPtr() }
public prefix func!(v: D3D11Buffer) -> Bool { !v.isValidPtr() }
public prefix func!(v: MTLBuffer) -> Bool { !v.isValidPtr() }
public prefix func!(v: VKBuffer) -> Bool { !v.isValidPtr() }
public prefix func!(v: GLBuffer) -> Bool { !v.isValidPtr() }
public prefix func!(v: GLESBuffer) -> Bool { !v.isValidPtr() }
public prefix func!(v: CUBuffer) -> Bool { !v.isValidPtr() }
public prefix func!(v: HIPBuffer) -> Bool { !v.isValidPtr() }
public prefix func!(v: FUBuffer) -> Bool { !v.isValidPtr() }
public prefix func!(v: Command) -> Bool { !v.isValidPtr() }
public prefix func!(v: D3D12Command) -> Bool { !v.isValidPtr() }
public prefix func!(v: MTLCommand) -> Bool { !v.isValidPtr() }
public prefix func!(v: VKCommand) -> Bool { !v.isValidPtr() }
public prefix func!(v: FUCommand) -> Bool { !v.isValidPtr() }
public prefix func!(v: Compute) -> Bool { !v.isValidPtr() }
public prefix func!(v: D3D12Compute) -> Bool { !v.isValidPtr() }
public prefix func!(v: MTLCompute) -> Bool { !v.isValidPtr() }
public prefix func!(v: VKCompute) -> Bool { !v.isValidPtr() }
public prefix func!(v: FUCompute) -> Bool { !v.isValidPtr() }
public prefix func!(v: Context) -> Bool { !v.isValidPtr() }
public prefix func!(v: D3D12Context) -> Bool { !v.isValidPtr() }
public prefix func!(v: D3D11Context) -> Bool { !v.isValidPtr() }
public prefix func!(v: MTLContext) -> Bool { !v.isValidPtr() }
public prefix func!(v: VKContext) -> Bool { !v.isValidPtr() }
public prefix func!(v: GLContext) -> Bool { !v.isValidPtr() }
public prefix func!(v: GLESContext) -> Bool { !v.isValidPtr() }
public prefix func!(v: WGContext) -> Bool { !v.isValidPtr() }
public prefix func!(v: CUContext) -> Bool { !v.isValidPtr() }
public prefix func!(v: HIPContext) -> Bool { !v.isValidPtr() }
public prefix func!(v: Query) -> Bool { !v.isValidPtr() }
public prefix func!(v: FUQuery) -> Bool { !v.isValidPtr() }
public prefix func!(v: Fence) -> Bool { !v.isValidPtr() }
public prefix func!(v: VKFence) -> Bool { !v.isValidPtr() }
public prefix func!(v: FUFence) -> Bool { !v.isValidPtr() }
public prefix func!(v: Shader) -> Bool { !v.isValidPtr() }
public prefix func!(v: ShaderCompiler) -> Bool { !v.isValidPtr() }
public prefix func!(v: D3D12Shader) -> Bool { !v.isValidPtr() }
public prefix func!(v: D3D11Shader) -> Bool { !v.isValidPtr() }
public prefix func!(v: MTLShader) -> Bool { !v.isValidPtr() }
public prefix func!(v: VKShader) -> Bool { !v.isValidPtr() }
public prefix func!(v: GLShader) -> Bool { !v.isValidPtr() }
public prefix func!(v: GLESShader) -> Bool { !v.isValidPtr() }
public prefix func!(v: CUShader) -> Bool { !v.isValidPtr() }
public prefix func!(v: HIPShader) -> Bool { !v.isValidPtr() }
public prefix func!(v: FUShader) -> Bool { !v.isValidPtr() }
public prefix func!(v: Sampler) -> Bool { !v.isValidPtr() }
public prefix func!(v: MTLSampler) -> Bool { !v.isValidPtr() }
public prefix func!(v: FUSampler) -> Bool { !v.isValidPtr() }
public prefix func!(v: Texture) -> Bool { !v.isValidPtr() }
public prefix func!(v: TextureTable) -> Bool { !v.isValidPtr() }
public prefix func!(v: D3D12Texture) -> Bool { !v.isValidPtr() }
public prefix func!(v: D3D11Texture) -> Bool { !v.isValidPtr() }
public prefix func!(v: MTLTexture) -> Bool { !v.isValidPtr() }
public prefix func!(v: VKTexture) -> Bool { !v.isValidPtr() }
public prefix func!(v: GLTexture) -> Bool { !v.isValidPtr() }
public prefix func!(v: GLESTexture) -> Bool { !v.isValidPtr() }
public prefix func!(v: CUTexture) -> Bool { !v.isValidPtr() }
public prefix func!(v: HIPTexture) -> Bool { !v.isValidPtr() }
public prefix func!(v: FUTexture) -> Bool { !v.isValidPtr() }
public prefix func!(v: Tracing) -> Bool { !v.isValidPtr() }
public prefix func!(v: D3D12Tracing) -> Bool { !v.isValidPtr() }
public prefix func!(v: MTLTracing) -> Bool { !v.isValidPtr() }
public prefix func!(v: VKTracing) -> Bool { !v.isValidPtr() }
public prefix func!(v: FUTracing) -> Bool { !v.isValidPtr() }
public prefix func!(v: Target) -> Bool { !v.isValidPtr() }
public prefix func!(v: D3D12Target) -> Bool { !v.isValidPtr() }
public prefix func!(v: D3D11Target) -> Bool { !v.isValidPtr() }
public prefix func!(v: MTLTarget) -> Bool { !v.isValidPtr() }
public prefix func!(v: VKTarget) -> Bool { !v.isValidPtr() }
public prefix func!(v: GLTarget) -> Bool { !v.isValidPtr() }
public prefix func!(v: GLESTarget) -> Bool { !v.isValidPtr() }
public prefix func!(v: FUTarget) -> Bool { !v.isValidPtr() }
public prefix func!(v: Device) -> Bool { !v.isValidPtr() }
public prefix func!(v: D3D12Device) -> Bool { !v.isValidPtr() }
public prefix func!(v: D3D11Device) -> Bool { !v.isValidPtr() }
public prefix func!(v: MTLDevice) -> Bool { !v.isValidPtr() }
public prefix func!(v: VKDevice) -> Bool { !v.isValidPtr() }
public prefix func!(v: FUDevice) -> Bool { !v.isValidPtr() }
public prefix func!(v: Kernel) -> Bool { !v.isValidPtr() }
public prefix func!(v: D3D12Kernel) -> Bool { !v.isValidPtr() }
public prefix func!(v: MTLKernel) -> Bool { !v.isValidPtr() }
public prefix func!(v: FUKernel) -> Bool { !v.isValidPtr() }
public prefix func!(v: Pipeline) -> Bool { !v.isValidPtr() }
public prefix func!(v: D3D12Pipeline) -> Bool { !v.isValidPtr() }
public prefix func!(v: MTLPipeline) -> Bool { !v.isValidPtr() }
public prefix func!(v: FUPipeline) -> Bool { !v.isValidPtr() }
public prefix func!(v: Traversal) -> Bool { !v.isValidPtr() }
public prefix func!(v: D3D12Traversal) -> Bool { !v.isValidPtr() }
public prefix func!(v: FUTraversal) -> Bool { !v.isValidPtr() }
public prefix func!(v: Surface) -> Bool { !v.isValidPtr() }
public prefix func!(v: D3D12Surface) -> Bool { !v.isValidPtr() }
public prefix func!(v: D3D11Surface) -> Bool { !v.isValidPtr() }
public prefix func!(v: MTLSurface) -> Bool { !v.isValidPtr() }
public prefix func!(v: VKSurface) -> Bool { !v.isValidPtr() }
public prefix func!(v: GLSurface) -> Bool { !v.isValidPtr() }
public prefix func!(v: GLESSurface) -> Bool { !v.isValidPtr() }
public prefix func!(v: Window) -> Bool { !v.isValidPtr() }
public prefix func!(v: Font) -> Bool { !v.isValidPtr() }
public prefix func!(v: CanvasElement) -> Bool { !v.isValidPtr() }
public prefix func!(v: CanvasText) -> Bool { !v.isValidPtr() }
public prefix func!(v: CanvasMesh) -> Bool { !v.isValidPtr() }
public prefix func!(v: CanvasRect) -> Bool { !v.isValidPtr() }
public prefix func!(v: CanvasTriangle) -> Bool { !v.isValidPtr() }
public prefix func!(v: CanvasEllipse) -> Bool { !v.isValidPtr() }
public prefix func!(v: CanvasShape) -> Bool { !v.isValidPtr() }
public prefix func!(v: CanvasStrip) -> Bool { !v.isValidPtr() }
public prefix func!(v: Canvas) -> Bool { !v.isValidPtr() }
public prefix func!(v: Control) -> Bool { !v.isValidPtr() }
public prefix func!(v: ControlRoot) -> Bool { !v.isValidPtr() }
public prefix func!(v: ControlText) -> Bool { !v.isValidPtr() }
public prefix func!(v: ControlRect) -> Bool { !v.isValidPtr() }
public prefix func!(v: ControlGrid) -> Bool { !v.isValidPtr() }
public prefix func!(v: ControlGroup) -> Bool { !v.isValidPtr() }
public prefix func!(v: ControlPanel) -> Bool { !v.isValidPtr() }
public prefix func!(v: ControlDialog) -> Bool { !v.isValidPtr() }
public prefix func!(v: ControlWindow) -> Bool { !v.isValidPtr() }
public prefix func!(v: ControlCheck) -> Bool { !v.isValidPtr() }
public prefix func!(v: ControlCombo) -> Bool { !v.isValidPtr() }
public prefix func!(v: ControlButton) -> Bool { !v.isValidPtr() }
public prefix func!(v: ControlSlider) -> Bool { !v.isValidPtr() }
public prefix func!(v: ControlScroll) -> Bool { !v.isValidPtr() }
public prefix func!(v: ControlSplit) -> Bool { !v.isValidPtr() }
public prefix func!(v: ControlArea) -> Bool { !v.isValidPtr() }
public prefix func!(v: ControlTree) -> Bool { !v.isValidPtr() }
public prefix func!(v: ControlEdit) -> Bool { !v.isValidPtr() }
public prefix func!(v: DialogMessage) -> Bool { !v.isValidPtr() }
public prefix func!(v: DialogFileOpen) -> Bool { !v.isValidPtr() }
public prefix func!(v: DialogFileSave) -> Bool { !v.isValidPtr() }
public prefix func!(v: DialogDirectory) -> Bool { !v.isValidPtr() }
public prefix func!(v: DialogProgress) -> Bool { !v.isValidPtr() }
public prefix func!(v: DialogColor) -> Bool { !v.isValidPtr() }
public prefix func!(v: DialogMenu) -> Bool { !v.isValidPtr() }
public prefix func!(v: CubeFilter) -> Bool { !v.isValidPtr() }
public prefix func!(v: DecoderJPEG) -> Bool { !v.isValidPtr() }
public prefix func!(v: EncoderBC15) -> Bool { !v.isValidPtr() }
public prefix func!(v: EncoderBC67) -> Bool { !v.isValidPtr() }
public prefix func!(v: EncoderASTC) -> Bool { !v.isValidPtr() }
public prefix func!(v: SeparableFilter) -> Bool { !v.isValidPtr() }
public prefix func!(v: PrefixScan) -> Bool { !v.isValidPtr() }
public prefix func!(v: RadixSort) -> Bool { !v.isValidPtr() }
public prefix func!(v: BitonicSort) -> Bool { !v.isValidPtr() }
public prefix func!(v: SpatialGrid) -> Bool { !v.isValidPtr() }
public prefix func!(v: SpatialTree) -> Bool { !v.isValidPtr() }
public prefix func!(v: FourierTransform) -> Bool { !v.isValidPtr() }
public prefix func!(v: TensorGraph) -> Bool { !v.isValidPtr() }
public prefix func!(v: Controller) -> Bool { !v.isValidPtr() }
public prefix func!(v: Desktop) -> Bool { !v.isValidPtr() }

// Tellusim::Window
public extension Window {
	class MousePressedFunction : NSObject, MousePressedCallback {
		public init(_ c: @escaping (_ button: Window.Button) -> Void ) { callback = c }
		public func run(_ button: Window.Button) -> Void { callback(button) }
		var callback: (_ button: Window.Button) -> Void
	}
}
public extension Window {
	class MouseReleasedFunction : NSObject, MouseReleasedCallback {
		public init(_ c: @escaping (_ button: Window.Button) -> Void ) { callback = c }
		public func run(_ button: Window.Button) -> Void { callback(button) }
		var callback: (_ button: Window.Button) -> Void
	}
}
public extension Window {
	class MouseChangedFunction : NSObject, MouseChangedCallback {
		public init(_ c: @escaping (_ x: Int32, _ y: Int32) -> Void ) { callback = c }
		public func run(_ x: Int32, _ y: Int32) -> Void { callback(x, y) }
		var callback: (_ x: Int32, _ y: Int32) -> Void
	}
}
public extension Window {
	class MouseRotatedFunction : NSObject, MouseRotatedCallback {
		public init(_ c: @escaping (_ axis: Window.Axis, _ delta: Float32) -> Void ) { callback = c }
		public func run(_ axis: Window.Axis, _ delta: Float32) -> Void { callback(axis, delta) }
		var callback: (_ axis: Window.Axis, _ delta: Float32) -> Void
	}
}
public extension Window {
	class TouchChangedFunction : NSObject, TouchChangedCallback {
		public init(_ c: @escaping () -> Void ) { callback = c }
		public func run() -> Void { callback() }
		var callback: () -> Void
	}
}
public extension Window {
	class KeyboardPressedFunction : NSObject, KeyboardPressedCallback {
		public init(_ c: @escaping (_ key: UInt32, _ code: UInt32) -> Void ) { callback = c }
		public func run(_ key: UInt32, _ code: UInt32) -> Void { callback(key, code) }
		var callback: (_ key: UInt32, _ code: UInt32) -> Void
	}
}
public extension Window {
	class KeyboardReleasedFunction : NSObject, KeyboardReleasedCallback {
		public init(_ c: @escaping (_ key: UInt32) -> Void ) { callback = c }
		public func run(_ key: UInt32) -> Void { callback(key) }
		var callback: (_ key: UInt32) -> Void
	}
}
public extension Window {
	class SizeChangedFunction : NSObject, SizeChangedCallback {
		public init(_ c: @escaping (_ width: UInt32, _ height: UInt32) -> Void ) { callback = c }
		public func run(_ width: UInt32, _ height: UInt32) -> Void { callback(width, height) }
		var callback: (_ width: UInt32, _ height: UInt32) -> Void
	}
}
public extension Window {
	class FocusChangedFunction : NSObject, FocusChangedCallback {
		public init(_ c: @escaping (_ changed: Bool) -> Void ) { callback = c }
		public func run(_ changed: Bool) -> Void { callback(changed) }
		var callback: (_ changed: Bool) -> Void
	}
}
public extension Window {
	class CloseClickedFunction : NSObject, CloseClickedCallback {
		public init(_ c: @escaping () -> Void ) { callback = c }
		public func run() -> Void { callback() }
		var callback: () -> Void
	}
}
public extension Window {
	class PauseChangedFunction : NSObject, PauseChangedCallback {
		public init(_ c: @escaping (_ paused: Bool) -> Void ) { callback = c }
		public func run(_ paused: Bool) -> Void { callback(paused) }
		var callback: (_ paused: Bool) -> Void
	}
}
public extension Window {
	class FileDroppedFunction : NSObject, FileDroppedCallback {
		public init(_ c: @escaping (_ name: String, _ remain: UInt32) -> Void ) { callback = c }
		public func run(_ name: String, _ remain: UInt32) -> Void { callback(name, remain) }
		var callback: (_ name: String, _ remain: UInt32) -> Void
	}
}
public extension Window {
	class UpdateFunction : NSObject, UpdateCallback {
		public init(_ c: @escaping () -> Void ) { callback = c }
		public func run() -> Void { callback() }
		var callback: () -> Void
	}
}
public extension Window {
	class PresentFunction : NSObject, PresentCallback {
		public init(_ c: @escaping () -> Void ) { callback = c }
		public func run() -> Void { callback() }
		var callback: () -> Void
	}
}
public extension Window {
	class MainLoopFunction : NSObject, MainLoopCallback {
		public init(_ c: @escaping () -> Bool ) { callback = c }
		public func run() -> Bool { callback() }
		var callback: () -> Bool
	}
}

// Tellusim::CanvasElement
public extension CanvasElement {
	class DrawFunction : NSObject, DrawCallback {
		public init(_ c: @escaping (_ command: Command, _ element: CanvasElement) -> Bool ) { callback = c }
		public func run(_ command: Command, _ element: CanvasElement) -> Bool { callback(command, element) }
		var callback: (_ command: Command, _ element: CanvasElement) -> Bool
	}
}

// Tellusim::Canvas
public extension Canvas {
	class CreateFunction : NSObject, CreateCallback {
		public init(_ c: @escaping (_ device: Device, _ canvas: Canvas, _ scale: UInt32) -> Bool ) { callback = c }
		public func run(_ device: Device, _ canvas: Canvas, _ scale: UInt32) -> Bool { callback(device, canvas, scale) }
		var callback: (_ device: Device, _ canvas: Canvas, _ scale: UInt32) -> Bool
	}
}
public extension Canvas {
	class PipelineFunction : NSObject, PipelineCallback {
		public init(_ c: @escaping (_ pipeline: Pipeline, _ canvas: Canvas, _ element: CanvasElement) -> Bool ) { callback = c }
		public func run(_ pipeline: Pipeline, _ canvas: Canvas, _ element: CanvasElement) -> Bool { callback(pipeline, canvas, element) }
		var callback: (_ pipeline: Pipeline, _ canvas: Canvas, _ element: CanvasElement) -> Bool
	}
}
public extension Canvas {
	class BeginFunction : NSObject, BeginCallback {
		public init(_ c: @escaping (_ command: Command, _ canvas: Canvas) -> Bool ) { callback = c }
		public func run(_ command: Command, _ canvas: Canvas) -> Bool { callback(command, canvas) }
		var callback: (_ command: Command, _ canvas: Canvas) -> Bool
	}
}
public extension Canvas {
	class DrawFunction : NSObject, DrawCallback {
		public init(_ c: @escaping (_ command: Command, _ canvas: Canvas) -> Bool ) { callback = c }
		public func run(_ command: Command, _ canvas: Canvas) -> Bool { callback(command, canvas) }
		var callback: (_ command: Command, _ canvas: Canvas) -> Bool
	}
}

// Tellusim::ControlRoot
public extension ControlRoot {
	class CopyFunction : NSObject, CopyCallback {
		public init(_ c: @escaping (_ a0: ControlRoot, _ text: String) -> Void ) { callback = c }
		public func run(_ a0: ControlRoot, _ text: String) -> Void { callback(a0, text) }
		var callback: (_ a0: ControlRoot, _ text: String) -> Void
	}
}
public extension ControlRoot {
	class PasteFunction : NSObject, PasteCallback {
		public init(_ c: @escaping (_ a0: ControlRoot) -> String ) { callback = c }
		public func run(_ a0: ControlRoot) -> String { callback(a0) }
		var callback: (_ a0: ControlRoot) -> String
	}
}

// Tellusim::ControlRect
public extension ControlRect {
	class InsideFunction : NSObject, InsideCallback {
		public init(_ c: @escaping (_ a0: ControlRect, _ x: Float32, _ y: Float32) -> Bool ) { callback = c }
		public func run(_ a0: ControlRect, _ x: Float32, _ y: Float32) -> Bool { callback(a0, x, y) }
		var callback: (_ a0: ControlRect, _ x: Float32, _ y: Float32) -> Bool
	}
}
public extension ControlRect {
	class PressedFunction : NSObject, PressedCallback {
		public init(_ c: @escaping (_ a0: ControlRect, _ x: Float32, _ y: Float32) -> Void ) { callback = c }
		public func run(_ a0: ControlRect, _ x: Float32, _ y: Float32) -> Void { callback(a0, x, y) }
		var callback: (_ a0: ControlRect, _ x: Float32, _ y: Float32) -> Void
	}
}
public extension ControlRect {
	class ReleasedFunction : NSObject, ReleasedCallback {
		public init(_ c: @escaping (_ a0: ControlRect, _ x: Float32, _ y: Float32) -> Void ) { callback = c }
		public func run(_ a0: ControlRect, _ x: Float32, _ y: Float32) -> Void { callback(a0, x, y) }
		var callback: (_ a0: ControlRect, _ x: Float32, _ y: Float32) -> Void
	}
}
public extension ControlRect {
	class ClickedFunction : NSObject, ClickedCallback {
		public init(_ c: @escaping (_ a0: ControlRect) -> Void ) { callback = c }
		public func run(_ a0: ControlRect) -> Void { callback(a0) }
		var callback: (_ a0: ControlRect) -> Void
	}
}

// Tellusim::ControlGroup
public extension ControlGroup {
	class ClickedFunction : NSObject, ClickedCallback {
		public init(_ c: @escaping (_ a0: ControlGroup) -> Void ) { callback = c }
		public func run(_ a0: ControlGroup) -> Void { callback(a0) }
		var callback: (_ a0: ControlGroup) -> Void
	}
}

// Tellusim::ControlDialog
public extension ControlDialog {
	class UpdatedFunction : NSObject, UpdatedCallback {
		public init(_ c: @escaping (_ a0: ControlDialog) -> Void ) { callback = c }
		public func run(_ a0: ControlDialog) -> Void { callback(a0) }
		var callback: (_ a0: ControlDialog) -> Void
	}
}

// Tellusim::ControlCheck
public extension ControlCheck {
	class ClickedFunction : NSObject, ClickedCallback {
		public init(_ c: @escaping (_ a0: ControlCheck) -> Void ) { callback = c }
		public func run(_ a0: ControlCheck) -> Void { callback(a0) }
		var callback: (_ a0: ControlCheck) -> Void
	}
}

// Tellusim::ControlCombo
public extension ControlCombo {
	class ClickedFunction : NSObject, ClickedCallback {
		public init(_ c: @escaping (_ a0: ControlCombo) -> Void ) { callback = c }
		public func run(_ a0: ControlCombo) -> Void { callback(a0) }
		var callback: (_ a0: ControlCombo) -> Void
	}
}
public extension ControlCombo {
	class ChangedFunction : NSObject, ChangedCallback {
		public init(_ c: @escaping (_ a0: ControlCombo) -> Void ) { callback = c }
		public func run(_ a0: ControlCombo) -> Void { callback(a0) }
		var callback: (_ a0: ControlCombo) -> Void
	}
}

// Tellusim::ControlButton
public extension ControlButton {
	class PressedFunction : NSObject, PressedCallback {
		public init(_ c: @escaping (_ a0: ControlButton, _ x: Float32, _ y: Float32) -> Void ) { callback = c }
		public func run(_ a0: ControlButton, _ x: Float32, _ y: Float32) -> Void { callback(a0, x, y) }
		var callback: (_ a0: ControlButton, _ x: Float32, _ y: Float32) -> Void
	}
}
public extension ControlButton {
	class ReleasedFunction : NSObject, ReleasedCallback {
		public init(_ c: @escaping (_ a0: ControlButton, _ x: Float32, _ y: Float32) -> Void ) { callback = c }
		public func run(_ a0: ControlButton, _ x: Float32, _ y: Float32) -> Void { callback(a0, x, y) }
		var callback: (_ a0: ControlButton, _ x: Float32, _ y: Float32) -> Void
	}
}
public extension ControlButton {
	class ClickedFunction : NSObject, ClickedCallback {
		public init(_ c: @escaping (_ a0: ControlButton) -> Void ) { callback = c }
		public func run(_ a0: ControlButton) -> Void { callback(a0) }
		var callback: (_ a0: ControlButton) -> Void
	}
}

// Tellusim::ControlSlider
public extension ControlSlider {
	class FormatFunction : NSObject, FormatCallback {
		public init(_ c: @escaping (_ a0: ControlSlider) -> String ) { callback = c }
		public func run(_ a0: ControlSlider) -> String { callback(a0) }
		var callback: (_ a0: ControlSlider) -> String
	}
}
public extension ControlSlider {
	class PressedFunction : NSObject, PressedCallback {
		public init(_ c: @escaping (_ a0: ControlSlider) -> Void ) { callback = c }
		public func run(_ a0: ControlSlider) -> Void { callback(a0) }
		var callback: (_ a0: ControlSlider) -> Void
	}
}
public extension ControlSlider {
	class ReleasedFunction : NSObject, ReleasedCallback {
		public init(_ c: @escaping (_ a0: ControlSlider) -> Void ) { callback = c }
		public func run(_ a0: ControlSlider) -> Void { callback(a0) }
		var callback: (_ a0: ControlSlider) -> Void
	}
}
public extension ControlSlider {
	class ClickedFunction : NSObject, ClickedCallback {
		public init(_ c: @escaping (_ a0: ControlSlider) -> Void ) { callback = c }
		public func run(_ a0: ControlSlider) -> Void { callback(a0) }
		var callback: (_ a0: ControlSlider) -> Void
	}
}
public extension ControlSlider {
	class ChangedFunction : NSObject, ChangedCallback {
		public init(_ c: @escaping (_ a0: ControlSlider) -> Void ) { callback = c }
		public func run(_ a0: ControlSlider) -> Void { callback(a0) }
		var callback: (_ a0: ControlSlider) -> Void
	}
}

// Tellusim::ControlScroll
public extension ControlScroll {
	class ClickedFunction : NSObject, ClickedCallback {
		public init(_ c: @escaping (_ a0: ControlScroll) -> Void ) { callback = c }
		public func run(_ a0: ControlScroll) -> Void { callback(a0) }
		var callback: (_ a0: ControlScroll) -> Void
	}
}
public extension ControlScroll {
	class ChangedFunction : NSObject, ChangedCallback {
		public init(_ c: @escaping (_ a0: ControlScroll) -> Void ) { callback = c }
		public func run(_ a0: ControlScroll) -> Void { callback(a0) }
		var callback: (_ a0: ControlScroll) -> Void
	}
}

// Tellusim::ControlTree
public extension ControlTree {
	class ChangedFunction : NSObject, ChangedCallback {
		public init(_ c: @escaping (_ a0: ControlTree, _ item: UInt32) -> Void ) { callback = c }
		public func run(_ a0: ControlTree, _ item: UInt32) -> Void { callback(a0, item) }
		var callback: (_ a0: ControlTree, _ item: UInt32) -> Void
	}
}
public extension ControlTree {
	class DraggedFunction : NSObject, DraggedCallback {
		public init(_ c: @escaping (_ a0: ControlTree, _ item: UInt32) -> Bool ) { callback = c }
		public func run(_ a0: ControlTree, _ item: UInt32) -> Bool { callback(a0, item) }
		var callback: (_ a0: ControlTree, _ item: UInt32) -> Bool
	}
}
public extension ControlTree {
	class DroppedFunction : NSObject, DroppedCallback {
		public init(_ c: @escaping (_ a0: ControlTree, _ item: UInt32) -> Void ) { callback = c }
		public func run(_ a0: ControlTree, _ item: UInt32) -> Void { callback(a0, item) }
		var callback: (_ a0: ControlTree, _ item: UInt32) -> Void
	}
}
public extension ControlTree {
	class ClickedFunction : NSObject, ClickedCallback {
		public init(_ c: @escaping (_ a0: ControlTree, _ item: UInt32) -> Void ) { callback = c }
		public func run(_ a0: ControlTree, _ item: UInt32) -> Void { callback(a0, item) }
		var callback: (_ a0: ControlTree, _ item: UInt32) -> Void
	}
}
public extension ControlTree {
	class ExpandedFunction : NSObject, ExpandedCallback {
		public init(_ c: @escaping (_ a0: ControlTree, _ item: UInt32) -> Void ) { callback = c }
		public func run(_ a0: ControlTree, _ item: UInt32) -> Void { callback(a0, item) }
		var callback: (_ a0: ControlTree, _ item: UInt32) -> Void
	}
}
public extension ControlTree {
	class SelectedFunction : NSObject, SelectedCallback {
		public init(_ c: @escaping (_ a0: ControlTree) -> Void ) { callback = c }
		public func run(_ a0: ControlTree) -> Void { callback(a0) }
		var callback: (_ a0: ControlTree) -> Void
	}
}

// Tellusim::ControlEdit
public extension ControlEdit {
	class ClickedFunction : NSObject, ClickedCallback {
		public init(_ c: @escaping (_ a0: ControlEdit) -> Void ) { callback = c }
		public func run(_ a0: ControlEdit) -> Void { callback(a0) }
		var callback: (_ a0: ControlEdit) -> Void
	}
}
public extension ControlEdit {
	class ChangedFunction : NSObject, ChangedCallback {
		public init(_ c: @escaping (_ a0: ControlEdit) -> Void ) { callback = c }
		public func run(_ a0: ControlEdit) -> Void { callback(a0) }
		var callback: (_ a0: ControlEdit) -> Void
	}
}
public extension ControlEdit {
	class ReturnedFunction : NSObject, ReturnedCallback {
		public init(_ c: @escaping (_ a0: ControlEdit) -> Void ) { callback = c }
		public func run(_ a0: ControlEdit) -> Void { callback(a0) }
		var callback: (_ a0: ControlEdit) -> Void
	}
}

// Tellusim::DialogMessage
public extension DialogMessage {
	class UpdateFunction : NSObject, UpdateCallback {
		public init(_ c: @escaping () -> Bool ) { callback = c }
		public func run() -> Bool { callback() }
		var callback: () -> Bool
	}
}

// Tellusim::DialogFileOpen
public extension DialogFileOpen {
	class UpdateFunction : NSObject, UpdateCallback {
		public init(_ c: @escaping () -> Bool ) { callback = c }
		public func run() -> Bool { callback() }
		var callback: () -> Bool
	}
}

// Tellusim::DialogFileSave
public extension DialogFileSave {
	class UpdateFunction : NSObject, UpdateCallback {
		public init(_ c: @escaping () -> Bool ) { callback = c }
		public func run() -> Bool { callback() }
		var callback: () -> Bool
	}
}

// Tellusim::DialogDirectory
public extension DialogDirectory {
	class UpdateFunction : NSObject, UpdateCallback {
		public init(_ c: @escaping () -> Bool ) { callback = c }
		public func run() -> Bool { callback() }
		var callback: () -> Bool
	}
}

// Tellusim::DialogColor
public extension DialogColor {
	class ChangedFunction : NSObject, ChangedCallback {
		public init(_ c: @escaping (_ a0: Color) -> Void ) { callback = c }
		public func run(_ a0: Color) -> Void { callback(a0) }
		var callback: (_ a0: Color) -> Void
	}
}
public extension DialogColor {
	class UpdateFunction : NSObject, UpdateCallback {
		public init(_ c: @escaping () -> Bool ) { callback = c }
		public func run() -> Bool { callback() }
		var callback: () -> Bool
	}
}

// Tellusim::DialogMenu
public extension DialogMenu {
	class ClickedFunction : NSObject, ClickedCallback {
		public init(_ c: @escaping () -> Void ) { callback = c }
		public func run() -> Void { callback() }
		var callback: () -> Void
	}
}
public extension DialogMenu {
	class ChangedFunction : NSObject, ChangedCallback {
		public init(_ c: @escaping (_ a0: Bool) -> Void ) { callback = c }
		public func run(_ a0: Bool) -> Void { callback(a0) }
		var callback: (_ a0: Bool) -> Void
	}
}
public extension DialogMenu {
	class UpdateFunction : NSObject, UpdateCallback {
		public init(_ c: @escaping () -> Bool ) { callback = c }
		public func run() -> Bool { callback() }
		var callback: () -> Bool
	}
}

// Tellusim::MeshModel
public extension MeshModel {
	class CreateFunction : NSObject, CreateCallback {
		public init(_ c: @escaping (_ src: UnsafeRawPointer, _ size: Int, _ owner: Bool) -> Bool ) { callback = c }
		public func run(_ src: UnsafeRawPointer, _ size: Int, _ owner: Bool) -> Bool { callback(src, size, owner) }
		var callback: (_ src: UnsafeRawPointer, _ size: Int, _ owner: Bool) -> Bool
	}
}

// Tellusim::Controller
public extension Controller {
	class ButtonPressedFunction : NSObject, ButtonPressedCallback {
		public init(_ c: @escaping (_ controller: Controller, _ button: Controller.Button) -> Void ) { callback = c }
		public func run(_ controller: Controller, _ button: Controller.Button) -> Void { callback(controller, button) }
		var callback: (_ controller: Controller, _ button: Controller.Button) -> Void
	}
}
public extension Controller {
	class ButtonReleasedFunction : NSObject, ButtonReleasedCallback {
		public init(_ c: @escaping (_ controller: Controller, _ button: Controller.Button) -> Void ) { callback = c }
		public func run(_ controller: Controller, _ button: Controller.Button) -> Void { callback(controller, button) }
		var callback: (_ controller: Controller, _ button: Controller.Button) -> Void
	}
}
public extension Controller {
	class ConnectedFunction : NSObject, ConnectedCallback {
		public init(_ c: @escaping (_ controller: Controller) -> Void ) { callback = c }
		public func run(_ controller: Controller) -> Void { callback(controller) }
		var callback: (_ controller: Controller) -> Void
	}
}
public extension Controller {
	class DisconnectedFunction : NSObject, DisconnectedCallback {
		public init(_ c: @escaping (_ controller: Controller) -> Void ) { callback = c }
		public func run(_ controller: Controller) -> Void { callback(controller) }
		var callback: (_ controller: Controller) -> Void
	}
}

// Tellusim::MeshGraph
public extension MeshGraph {
	class ProgressFunction : NSObject, ProgressCallback {
		public init(_ c: @escaping (_ progress: UInt32) -> Bool ) { callback = c }
		public func run(_ progress: UInt32) -> Bool { callback(progress) }
		var callback: (_ progress: UInt32) -> Bool
	}
}

// Tellusim::MeshReduce
public extension MeshReduce {
	class ProgressFunction : NSObject, ProgressCallback {
		public init(_ c: @escaping (_ progress: UInt32) -> Bool ) { callback = c }
		public func run(_ progress: UInt32) -> Bool { callback(progress) }
		var callback: (_ progress: UInt32) -> Bool
	}
}

// Tellusim::MeshSolid
public extension MeshSolid {
	class ProgressFunction : NSObject, ProgressCallback {
		public init(_ c: @escaping (_ progress: UInt32) -> Bool ) { callback = c }
		public func run(_ progress: UInt32) -> Bool { callback(progress) }
		var callback: (_ progress: UInt32) -> Bool
	}
}
