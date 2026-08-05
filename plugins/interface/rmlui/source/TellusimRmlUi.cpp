// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#if _WIN32
	#pragma comment(lib, "rmlui.lib")
	#pragma comment(lib, "freetype.lib")
	#pragma comment(lib, "user32.lib")
#endif

#include <core/TellusimLog.h>
#include <core/TellusimMap.h>
#include <core/TellusimSet.h>
#include <core/TellusimTime.h>
#include <core/TellusimBlob.h>
#include <core/TellusimSource.h>
#include <math/TellusimMath.h>
#include <platform/TellusimWindow.h>
#include <platform/TellusimTarget.h>
#include <platform/TellusimCommand.h>
#include <platform/TellusimSampler.h>
#include <platform/TellusimPipeline.h>

#include "../include/TellusimRmlUi.h"

/*
 */
namespace Tellusim {
	
	/*
	 */
	class FileInterface : public Rml::FileInterface {
			
		public:
			
			FileInterface() {
				
			}
			virtual ~FileInterface() {
				
			}
			
			// open file
			virtual Rml::FileHandle Open(const Rml::String &path) {
				Source *source = new Source();
				if(source->open(path.c_str())) return (Rml::FileHandle)source;
				delete source;
				return 0;
			}
			virtual void Close(Rml::FileHandle file) {
				delete (Source*)file;
			}
			
			// read file
			virtual size_t Read(void *buffer, size_t size, Rml::FileHandle file) {
				return ((Source*)file)->read(buffer, size);
			}
			virtual bool Seek(Rml::FileHandle file, long offset, int origin) {
				if(origin == SEEK_SET) return ((Source*)file)->seek((size_t)offset);
				if(origin == SEEK_END) return ((Source*)file)->seekBack((size_t)offset);
				if(origin == SEEK_CUR) return ((Source*)file)->seekCur((size_t)offset);
				return false;
			}
			virtual size_t Tell(Rml::FileHandle file) {
				return ((Source*)file)->tell();
			}
			
			// file size
			virtual size_t Length(Rml::FileHandle file) {
				return ((Source*)file)->getSize();
			}
			
			// load file
			virtual bool LoadFile(const Rml::String &path, Rml::String &out_data) {
				Source source;
				if(source.open(path.c_str())) {
					out_data = source.gets().get();
					return true;
				}
				return false;
			}
	};
	
	/*
	 */
	class SystemInterface : public Rml::SystemInterface {
			
		public:
			
			explicit SystemInterface(Window &window) : window(window) {
				
			}
			virtual ~SystemInterface() {
				
			}
			
			// application time
			virtual float64_t GetElapsedTime() {
				return Time::seconds();
			}
			
			// string translation
			virtual int TranslateString(Rml::String &translated, const Rml::String &input) {
				return Rml::SystemInterface::TranslateString(translated, input);
			}
			
			// combined path
			virtual void JoinPath(Rml::String &translated_path, const Rml::String &document_path, const Rml::String &path) {
				Rml::SystemInterface::JoinPath(translated_path, document_path, path);
			}
			
			// log message
			virtual bool LogMessage(Rml::Log::Type type, const Rml::String &message) {
				Log::Level level = Log::Level::Unknown;
				if(type == Rml::Log::LT_ERROR) level = Log::Error;
				else if(type == Rml::Log::LT_ASSERT) level = Log::Fatal;
				else if(type == Rml::Log::LT_WARNING) level = Log::Warning;
				else if(type == Rml::Log::LT_INFO) level = Log::Message;
				else if(type == Rml::Log::LT_DEBUG) level = Log::Verbose;
				Log::printf(level, "%s\n", message.c_str());
				return true;
			}
			
			// window cursor
			virtual void SetMouseCursor(const Rml::String &cursor_name) {
				Window::Cursor cursor = Window::CursorArrow;
				if(cursor_name == "move") cursor = Window::CursorAll;
				if(cursor_name == "resize") cursor = Window::CursorAll;
				if(cursor_name == "cross") cursor = Window::CursorInvalid;
				window.setMouseCursor(cursor);
			}
			
			// window clipboard
			virtual void SetClipboardText(const Rml::String &text) {
				window.setCopyText(text.c_str());
			}
			virtual void GetClipboardText(Rml::String &text) {
				text = window.getPasteText().get();
			}
			
			// touch keyboard
			virtual void ActivateKeyboard(Rml::Vector2f caret_position, float32_t line_height) {
				Rml::SystemInterface::ActivateKeyboard(caret_position, line_height);
			}
			virtual void DeactivateKeyboard() {
				Rml::SystemInterface::DeactivateKeyboard();
			}
		
		private:
			
			Window window;
	};
	
	/*
	 */
	class RenderInterface : public Rml::RenderInterface {
			
		public:
			
			explicit RenderInterface(Device &device) : device(device) {
				
			}
			virtual ~RenderInterface() {
				clear();
			}
			
			// clear interface
			void clear() {
				release_commands();
				release_resources();
				shader_source.clear();
				texture_target.clearPtr();
				linear_sampler.clearPtr();
				pipelines.clear();
				textures.clear();
				frames.clear();
			}
			
			// create interface
			bool create() {
				
				// RmlUi shader source
				#ifndef RMLUI_PATH
					#include "TellusimRmlUi.blob"
					shader_source = Blob(TellusimRmlUi_blob_src).gets();
				#else
					Source source;
					if(!source.open(TS_STRING(RMLUI_PATH) "source/TellusimRmlUi.shader")) return false;
					shader_source = source.gets();
				#endif
				
				// create texture target
				texture_target = device.createTarget();
				if(!texture_target) {
					TS_LOG(Error, "RmlUi::RenderInterface::create(): can't create Target\n");
					return false;
				}
				texture_target.setClearColor(0.0f, 0.0f, 0.0f, 0.0f);
				
				// create linear sampler
				linear_sampler = device.createSampler(Sampler::FilterLinear, Sampler::WrapModeRepeat);
				if(!linear_sampler) {
					TS_LOG(Error, "RmlUi::RenderInterface::create(): can't create Sampler\n");
					return false;
				}
				
				return true;
			}
			
			// update context
			bool update(Rml::Context *context) {
				
				// update frame
				frame++;
				
				// release old textures
				ArrayStack<uint32_t, 1024> remove_indices;
				for(uint32_t i = 0; i < textures.size(); i++) {
					if(frames[i] + NumTextureFrames < frame && textures[i].getCountPtr() == 1) {
						device.releaseTexture(textures[i]);
						remove_indices.append(i);
					}
				}
				for(uint32_t i = remove_indices.size(); i > 0; i--) {
					textures.removeFast(remove_indices[i - 1]);
					frames.removeFast(remove_indices[i - 1]);
				}
				
				// release commands
				release_commands();
				
				// release resources
				release_resources();
				
				// current viewport
				Rml::Vector2i viewport = context->GetDimensions();
				render_width = viewport.x;
				render_height = viewport.y;
				
				// update context
				if(!context->Update()) {
					TS_LOG(Error, "RmlUi::RenderInterface::update(): can't update Context\n");
					return false;
				}
				
				// render context
				if(!context->Render()) {
					TS_LOG(Error, "RmlUi::RenderInterface::update(): can't render Context\n");
					for(Texture &texture : command_textures) {
						release_texture(texture);
					}
					return false;
				}
				
				// check the layers
				if(command_textures) {
					TS_LOG(Error, "RmlUi::RenderInterface::update(): stack is not zero\n");
					for(Texture &texture : command_textures) {
						release_texture(texture);
					}
					return false;
				}
				
				return true;
			}
			
			// render context into target
			bool render(const Target &target, Command &command, Rml::Context *context) {
				
				// current transform
				Matrix4x4f render_transform = Matrix4x4f(Rml::Matrix4f::ProjectOrtho(0.0f, (float32_t)render_width, (float32_t)render_height, 0.0f, -10000.0f, 10000.0f).data());
				Matrix4x4f current_transform = render_transform;
				bool update_transform = false;
				
				// scissor state
				Scissor render_scissor = Scissor(0, 0, render_width, render_height);
				Scissor current_scissor = render_scissor;
				bool update_scissor = false;
				bool enable_scissor = false;
				
				// render state
				uint32_t render_flags = ShaderFlagNone;
				uint32_t render_stencil = 0;
				Pipeline render_pipeline;
				Texture render_texture;
				
				// render commands
				for(const CommandArgs &args : commands) {
					if(args.type == CommandSetScissor) {
						current_scissor = args.scissor.scissor;
						enable_scissor = args.scissor.enable;
						update_scissor = true;
					}
					else if(args.type == CommandSetStencil) {
						if(args.stencil.enable) render_flags |= ShaderFlagStencil;
						else render_flags = render_flags & ~ShaderFlagStencil;
					}
					else if(args.type == CommandSetTransform) {
						if(args.transform.identity) current_transform = render_transform;
						else current_transform = render_transform * args.transform.transform;
						update_transform = true;
					}
					else if(args.type == CommandRenderGeometry) {
						ShaderType type = ShaderSolid;
						uint32_t flags = render_flags;
						if(args.render.stencil == ShaderUnknown) {
							if(args.render.texture) type = ShaderTexture;
							if(args.render.shader) type = args.render.shader->type;
							if(args.render.shader) flags |= args.render.shader->flags;
						} else {
							type = args.render.stencil;
							if(type == ShaderStencilInverse) render_flags |= ShaderFlagInverse;
							else render_flags = render_flags & ~ShaderFlagInverse;
							flags |= ShaderFlagStencil;
							render_stencil++;
						}
						Pipeline pipeline = get_pipeline(target, type, flags);
						if(pipeline) {
							if(render_pipeline != pipeline) {
								command.setPipeline(pipeline);
								if(args.render.texture && pipeline.getNumSamplers()) command.setSampler(0, linear_sampler);
								render_pipeline = pipeline;
								render_texture.clearPtr();
								update_transform = true;
								update_scissor = true;
							}
							if(args.render.texture && render_texture != args.render.texture->texture) {
								if(pipeline.getNumTextures()) command.setTexture(0, args.render.texture->texture);
								render_texture = args.render.texture->texture;
							}
							if(update_transform) {
								command.setUniform(0, current_transform);
								update_transform = false;
							}
							if(update_scissor) {
								if(enable_scissor) command.setScissor(0, current_scissor);
								else command.setScissor(0, render_scissor);
								update_scissor = false;
							}
							if(flags & ShaderFlagStencil) {
								if(type == ShaderStencilIntersect) command.setStencilRef(render_stencil - 1);
								else command.setStencilRef(render_stencil);
							}
							render_geometry(command, args);
						}
					}
					else {
						TS_LOGF(Error, "RmlUi::RenderInterface::render(): unknown render command %u\n", args.type);
						return false;
					}
				}
				
				return true;
			}
			
			// render context into texture
			bool render(Texture &color_texture, Texture &depth_texture, Rml::Context *context) {
				
				// check color texture
				if(color_texture.getWidth() != render_width || color_texture.getHeight() != render_height) {
					TS_LOGF(Error, "RmlUi::RenderInterface::render(): invalid color texture size %ux%u\n", color_texture.getWidth(), color_texture.getHeight());
					return false;
				}
				
				// check depth texture
				if(depth_texture && (depth_texture.getWidth() != render_width || depth_texture.getHeight() != render_height)) {
					TS_LOGF(Error, "RmlUi::RenderInterface::render(): invalid depth texture size %ux%u\n", depth_texture.getWidth(), depth_texture.getHeight());
					return false;
				}
				
				// current transform
				Matrix4x4f render_transform = Matrix4x4f(Rml::Matrix4f::ProjectOrtho(0.0f, (float32_t)render_width, (float32_t)render_height, 0.0f, -10000.0f, 10000.0f).data());
				Matrix4x4f current_transform = render_transform;
				bool update_transform = false;
				
				// scissor state
				Scissor render_scissor = Scissor(0, 0, (int32_t)render_width, (int32_t)render_height);
				Scissor current_scissor = render_scissor;
				bool update_scissor = false;
				bool enable_scissor = false;
				
				// render state
				uint32_t render_flags = ShaderFlagNone;
				uint32_t render_stencil = 0;
				Pipeline render_pipeline;
				Texture render_texture;
				
				// target state
				Target target = texture_target;
				Texture current_texture = color_texture;
				Target::Operation current_op = Target::OpClearStore;
				target.setColorTexture(current_texture, current_op);
				
				// depth texture
				if(depth_texture) {
					device.clearTexture(depth_texture, nullptr);
					target.setDepthTexture(depth_texture, Target::OpLoadStore);
				}
				
				// render command
				Command command;
				
				// begin texture target
				auto begin_target = [&](Texture &texture, Target::Operation op) {
					if(!command) {
						target.setColorTexture(texture, op);
						if(!target.begin()) {
							TS_LOG(Error, "RmlUi::RenderInterface::render(): can't begin Target\n");
							return false;
						}
						command = device.createCommand(target);
					}
					return true;
				};
				
				// end texture target
				auto end_target = [&]() {
					if(command) {
						render_pipeline.clearPtr();
						render_texture.clearPtr();
						command.clearPtr();
						target.end();
					}
				};
				
				// render commands
				for(const CommandArgs &args : commands) {
					if(args.type == CommandSetTarget) {
						end_target();
						if(args.target.texture) current_texture = *args.target.texture;
						else current_texture = color_texture;
						current_op = args.target.operation;
					}
					else if(args.type == CommandSetScissor) {
						current_scissor = args.scissor.scissor;
						enable_scissor = args.scissor.enable;
						update_scissor = true;
					}
					else if(args.type == CommandSetStencil) {
						if(args.stencil.enable) render_flags |= ShaderFlagStencil;
						else render_flags = render_flags & ~ShaderFlagStencil;
					}
					else if(args.type == CommandSetTransform) {
						if(args.transform.identity) current_transform = render_transform;
						else current_transform = render_transform * args.transform.transform;
						update_transform = true;
					}
					else if(args.type == CommandRenderGeometry) {
						ShaderType type = ShaderSolid;
						uint32_t flags = render_flags;
						if(args.render.stencil == ShaderUnknown) {
							if(args.render.texture) type = ShaderTexture;
							if(args.render.shader) type = args.render.shader->type;
							if(args.render.shader) flags |= args.render.shader->flags;
						} else {
							type = args.render.stencil;
							if(type == ShaderStencilInverse) render_flags |= ShaderFlagInverse;
							else render_flags = render_flags & ~ShaderFlagInverse;
							flags |= ShaderFlagStencil;
							render_stencil++;
						}
						Pipeline pipeline = get_pipeline(target, type, flags);
						if(pipeline && begin_target(current_texture, current_op)) {
							if(render_pipeline != pipeline) {
								command.setPipeline(pipeline);
								if(args.render.texture && pipeline.getNumSamplers()) command.setSampler(0, linear_sampler);
								render_pipeline = pipeline;
								render_texture.clearPtr();
								update_transform = true;
								update_scissor = true;
							}
							if(args.render.texture && render_texture != args.render.texture->texture) {
								if(pipeline.getNumTextures()) command.setTexture(0, args.render.texture->texture);
								render_texture = args.render.texture->texture;
							}
							if(update_transform) {
								command.setUniform(0, current_transform);
								update_transform = false;
							}
							if(update_scissor) {
								if(enable_scissor) command.setScissor(0, current_scissor);
								else command.setScissor(0, render_scissor);
								update_scissor = false;
							}
							if(flags & ShaderFlagStencil) {
								if(type == ShaderStencilIntersect) command.setStencilRef(render_stencil - 1);
								else command.setStencilRef(render_stencil);
							}
							render_geometry(command, args);
						}
					}
					else if(args.type == CommandBlendLayers) {
						end_target();
						Texture &src_texture = (args.blend.src) ? *args.blend.src : color_texture;
						Texture &dest_texture = (args.blend.dest) ? *args.blend.dest : color_texture;
						device.flushTexture(src_texture);
						uint32_t blend_flags = ShaderFlagNone;
						if(args.blend.mode == Rml::BlendMode::Replace) blend_flags = ShaderFlagOpaque;
						if(args.blend.num_filters == 0) {
							Pipeline pipeline = get_pipeline(target, ShaderFilterCopy, blend_flags);
							if(pipeline && begin_target(dest_texture, Target::OpLoadStore)) {
								command.setPipeline(pipeline);
								command.setScissor(0, args.blend.scissor);
								command.setSampler(0, linear_sampler);
								command.setTexture(0, src_texture);
								command.setUniform(0, 1.0f);
								command.drawArrays(3);
								end_target();
							}
						} else {
							Texture textures[2];
							uint32_t num_filters = args.blend.num_filters;
							InitializerList<Texture> excludes = { dest_texture, src_texture };
							for(uint32_t i = 0; i < num_filters; i++) {
								const FilterArgs &filter = *command_filters[args.blend.base_filter + i];
								bool is_last = (i == num_filters - 1);
								Texture &src = (i == 0) ? src_texture : textures[0];
								if(!src) src = create_texture(render_width, render_height, excludes);
								if(!src) return false;
								uint32_t flags = (is_last) ? blend_flags : ShaderFlagOpaque;
								Texture &dest = (is_last) ? dest_texture : textures[1];
								if(!dest) dest = create_texture(render_width, render_height, excludes);
								if(!dest) return false;
								if(filter.type == ShaderFilterColor) {
									FilterArgs combined_filter;
									memcpy(&combined_filter, &filter, sizeof(filter));
									for(; i + 1 < num_filters; i++) {
										const FilterArgs *filter = command_filters[args.blend.base_filter + i + 1];
										if(filter->type == ShaderFilterColor) combined_filter.color.matrix *= filter->color.matrix;
										else break;
									}
									bool is_last = (i + 1 == num_filters);
									uint32_t flags = (is_last) ? blend_flags : ShaderFlagOpaque;
									Texture &dest = (is_last) ? dest_texture : textures[1];
									if(!render_filter(target, combined_filter, args.blend.scissor, dest, src, flags, excludes)) return false;
								} else {
									if(!render_filter(target, filter, args.blend.scissor, dest, src, flags, excludes)) return false;
								}
								swap(textures[0], textures[1]);
							}
							release_texture(textures[0]);
							release_texture(textures[1]);
						}
						device.flushTexture(dest_texture);
					}
					else if(args.type == CommandCopyTexture) {
						end_target();
						Texture &src_texture = *args.copy.src;
						Texture &dest_texture = *args.copy.dest;
						device.flushTexture(src_texture, Texture::FlagSource);
						device.copyTexture(dest_texture, Origin(0, 0), src_texture, args.copy.region);
						device.flushTexture(dest_texture);
					}
					else {
						TS_LOGF(Error, "RmlUi::RenderInterface::render(): unknown render command %u\n", args.type);
						end_target();
						return false;
					}
				}
				
				// end target
				end_target();
				
				// flush texture
				device.flushTexture(color_texture);
				
				return true;
			}
			
			// draw fullscreen texture
			bool draw(const Target &target, Command &command, Texture &texture) {
				
				// get filter copy pipeline
				Pipeline pipeline = get_pipeline(target, ShaderFilterCopy);
				if(!pipeline) {
					TS_LOG(Error, "RmlUi::RenderInterface::draw(): can't get Pipeline\n");
					return false;
				}
				
				// draw texture
				command.setPipeline(pipeline);
				command.setSampler(0, linear_sampler);
				command.setTexture(0, texture);
				command.setUniform(0, 1.0f);
				command.drawArrays(3);
				
				return true;
			}
			
			// render geometry
			virtual Rml::CompiledGeometryHandle CompileGeometry(Rml::Span<const Rml::Vertex> vertices, Rml::Span<const int> indices) {
				GeometryArgs *geometry = new GeometryArgs();
				geometry->vertices.copy(vertices.data(), (uint32_t)vertices.size());
				geometry->indices.copy((const uint32_t*)indices.data(), (uint32_t)indices.size());
				return (Rml::CompiledGeometryHandle)geometry;
			}
			virtual void RenderGeometry(Rml::CompiledGeometryHandle geometry, Rml::Vector2f translate, Rml::TextureHandle texture) {
				CommandArgs &args = commands.append();
				args.type = CommandRenderGeometry;
				args.render.translate = translate;
				args.render.geometry = (GeometryArgs*)geometry;
				args.render.texture = (TextureArgs*)texture;
				args.render.shader = nullptr;
				args.render.stencil = ShaderUnknown;
			}
			virtual void ReleaseGeometry(Rml::CompiledGeometryHandle geometry) {
				released_geometries.append(geometry);
			}
			
			// render texture
			virtual Rml::TextureHandle LoadTexture(Rml::Vector2i &texture_dimensions, const Rml::String &source) {
				Image image;
				if(image.load(source.c_str())) {
					if(image.getFormat() == FormatRGBAu8n) {
						ImageSampler sampler(image);
						for(size_t i = 0; i < sampler.getTexels(); i++) {
							ImageColor color = sampler.getTexel(i);
							if(color.u.a == 0) {
								sampler.setTexel(i, ImageColor(0));
							} else if(color.u.a != 255) {
								color.u.r = color.u.r * color.u.a / 255;
								color.u.g = color.u.g * color.u.a / 255;
								color.u.b = color.u.b * color.u.a / 255;
								sampler.setTexel(i, color);
							}
						}
					}
					texture_dimensions.x = image.getWidth();
					texture_dimensions.y = image.getHeight();
					TextureArgs *texture = new TextureArgs();
					texture->texture = device.createTexture(image);
					if(texture->texture) return (Rml::TextureHandle)texture;
					delete texture;
				}
				return 0;
			}
			virtual Rml::TextureHandle GenerateTexture(Rml::Span<const Rml::byte> source, Rml::Vector2i source_dimensions) {
				Image image(Image::Type2D, FormatRGBAu8n, Size(source_dimensions.x, source_dimensions.y), Image::FlagNoClear);
				if(image.getDataSize() == source.size()) {
					image.setData(source.data());
					TextureArgs *texture = new TextureArgs();
					texture->texture = device.createTexture(image);
					if(texture->texture) return (Rml::TextureHandle)texture;
					delete texture;
				}
				return 0;
			}
			virtual void ReleaseTexture(Rml::TextureHandle texture) {
				released_textures.append(texture);
			}
			
			// scissor rect
			virtual void EnableScissorRegion(bool enable) {
				command_scissor_enable = enable;
				CommandArgs &args = commands.append();
				args.type = CommandSetScissor;
				args.scissor.scissor = command_scissor;
				args.scissor.enable = command_scissor_enable;
			}
			virtual void SetScissorRegion(Rml::Rectanglei region) {
				int32_t left = clamp(region.Left(), 0, (int32_t)render_width);
				int32_t top = clamp(region.Top(), 0, (int32_t)render_height);
				int32_t right = clamp(region.Right(), left, (int32_t)render_width);
				int32_t bottom = clamp(region.Bottom(), top, (int32_t)render_height);
				command_scissor = Scissor(left, render_height - bottom, right - left, bottom - top);
				command_region = Region((uint32_t)left, (uint32_t)(render_height - bottom), (uint32_t)(right - left), (uint32_t)(bottom - top));
				CommandArgs &args = commands.append();
				args.type = CommandSetScissor;
				args.scissor.scissor = command_scissor;
				args.scissor.enable = command_scissor_enable;
			}
			
			// clip mask
			virtual void EnableClipMask(bool enable) {
				CommandArgs &args = commands.append();
				args.type = CommandSetStencil;
				args.stencil.enable = enable;
			}
			virtual void RenderToClipMask(Rml::ClipMaskOperation operation, Rml::CompiledGeometryHandle geometry, Rml::Vector2f translate) {
				CommandArgs &args = commands.append();
				args.type = CommandRenderGeometry;
				args.render.translate = translate;
				args.render.geometry = (GeometryArgs*)geometry;
				args.render.texture = nullptr;
				args.render.shader = nullptr;
				args.render.stencil = ShaderUnknown;
				if(operation == Rml::ClipMaskOperation::Set) args.render.stencil = ShaderStencil;
				else if(operation == Rml::ClipMaskOperation::SetInverse) args.render.stencil = ShaderStencilInverse;
				else if(operation == Rml::ClipMaskOperation::Intersect) args.render.stencil = ShaderStencilIntersect;
				else TS_LOGF(Error, "RmlUi::RenderInterface::RenderToClipMask(): unknown operation %d\n", (int32_t)operation);
			}
			
			// transformation matrix
			virtual void SetTransform(const Rml::Matrix4f *transform) {
				CommandArgs &args = commands.append();
				args.type = CommandSetTransform;
				if(transform) args.transform.transform.set(transform->data());
				args.transform.identity = (transform == nullptr);
			}
			
			// layers
			virtual Rml::LayerHandle PushLayer() {
				command_textures.append(create_texture(render_width, render_height));
				CommandArgs &args = commands.append();
				args.type = CommandSetTarget;
				args.target.texture = new Texture(command_textures.back());
				args.target.operation = Target::OpClearStore;
				return (Rml::LayerHandle)command_textures.size();
			}
			virtual void CompositeLayers(Rml::LayerHandle src_handle, Rml::LayerHandle dest_handle, Rml::BlendMode blend_mode, Rml::Span<const Rml::CompiledFilterHandle> filters) {
				if(command_scissor.width && command_scissor.height) {
					CommandArgs &args = commands.append();
					args.type = CommandBlendLayers;
					args.blend.src = (src_handle) ? new Texture(command_textures[(uint32_t)src_handle - 1]) : nullptr;
					args.blend.dest = (dest_handle) ? new Texture(command_textures[(uint32_t)dest_handle - 1]) : nullptr;
					args.blend.region = command_region;
					args.blend.scissor = command_scissor;
					args.blend.mode = blend_mode;
					args.blend.base_filter = command_filters.size();
					args.blend.num_filters = (uint32_t)filters.size();
					for(const Rml::CompiledFilterHandle &handle : filters) {
						command_filters.append((FilterArgs*)handle);
					}
				}
			}
			virtual void PopLayer() {
				TS_ASSERT(command_textures && "RmlUi::RenderInterface::PopLayer(): stack underflow");
				release_texture(command_textures.back());
				command_textures.removeBack();
				CommandArgs &args = commands.append();
				args.type = CommandSetTarget;
				args.target.texture = (command_textures) ? new Texture(command_textures.back()) : nullptr;
				args.target.operation = Target::OpLoadStore;
			}
			virtual Rml::TextureHandle SaveLayerAsTexture() {
				TS_ASSERT(command_textures && "RmlUi::RenderInterface::SaveLayerAsTexture(): stack underflow");
				if(command_region.width && command_region.height) {
					TextureArgs *texture = new TextureArgs();
					texture->texture = create_texture(command_region.width, command_region.height);
					texture->is_flipped = true;
					CommandArgs &args = commands.append();
					args.type = CommandCopyTexture;
					args.copy.src = new Texture(command_textures.back());
					args.copy.dest = new Texture(texture->texture);
					args.copy.region = command_region;
					return (Rml::TextureHandle)texture;
				}
				return 0;
			}
			virtual Rml::CompiledFilterHandle SaveLayerAsMaskImage() {
				TS_ASSERT(command_textures && "RmlUi::RenderInterface::SaveLayerAsMaskImage(): stack underflow");
				if(command_region.width && command_region.height) {
					Texture texture = create_texture(command_region.width, command_region.height);
					FilterArgs *filter = new FilterArgs();
					filter->type = ShaderFilterMask;
					filter->mask.texture = new Texture(texture);
					float32_t scale_x = (float32_t)render_width / command_region.width;
					float32_t scale_y = (float32_t)render_height / command_region.height;
					float32_t offset_x = -scale_x * command_region.x / render_width;
					float32_t offset_y = -scale_y * command_region.y / render_height;
					filter->mask.transform = Vector4f(scale_x, scale_y, offset_x, offset_y);
					CommandArgs &args = commands.append();
					args.type = CommandCopyTexture;
					args.copy.src = new Texture(command_textures.back());
					args.copy.dest = new Texture(texture);
					args.copy.region = command_region;
					return (Rml::CompiledFilterHandle)filter;
				}
				return 0;
			}
			
			// filters
			virtual Rml::CompiledFilterHandle CompileFilter(const Rml::String &name, const Rml::Dictionary &parameters) {
				FilterArgs *filter = new FilterArgs();
				if(name == "blur") {
					filter->type = ShaderFilterBlur;
					filter->blur.sigma = Rml::Get(parameters, "sigma", 1.0f);
				} else if(name == "drop-shadow") {
					filter->type = ShaderFilterShadow;
					Rml::ColourbPremultiplied color = Rml::Get(parameters, "color", Rml::Colourb()).ToPremultiplied();
					Vector2f offset = Rml::Get(parameters, "offset", Rml::Vector2f(0.0f));
					filter->shadow.color = Color(color.red, color.green, color.blue, color.alpha);
					filter->shadow.offset = offset;
					filter->shadow.sigma = Rml::Get(parameters, "sigma", 1.0f);
				} else if(name == "opacity") {
					filter->type = ShaderFilterCopy;
					filter->copy.value = Rml::Get(parameters, "value", 1.0f);
				} else if(name == "brightness") {
					filter->type = ShaderFilterColor;
					float32_t value = Rml::Get(parameters, "value", 1.0f);
					filter->color.matrix.row_0 = Vector4f(value, 0.0f, 0.0f, 0.0f);
					filter->color.matrix.row_1 = Vector4f(0.0f, value, 0.0f, 0.0f);
					filter->color.matrix.row_2 = Vector4f(0.0f, 0.0f, value, 0.0f);
					filter->color.matrix.row_3 = Vector4f(0.0f, 0.0f, 0.0f, 1.0f);
				} else if(name == "contrast") {
					filter->type = ShaderFilterColor;
					float32_t value = Rml::Get(parameters, "value", 1.0f);
					float32_t offset = 0.5f - value * 0.5f;
					filter->color.matrix.row_0 = Vector4f(value, 0.0f, 0.0f, offset);
					filter->color.matrix.row_1 = Vector4f(0.0f, value, 0.0f, offset);
					filter->color.matrix.row_2 = Vector4f(0.0f, 0.0f, value, offset);
					filter->color.matrix.row_3 = Vector4f(0.0f, 0.0f, 0.0f, 1.0f);
				} else if(name == "invert") {
					filter->type = ShaderFilterColor;
					float32_t value = Rml::Get(parameters, "value", 1.0f);
					float32_t scale = 1.0f - value * 2.0f;
					filter->color.matrix.row_0 = Vector4f(scale, 0.0f, 0.0f, value);
					filter->color.matrix.row_1 = Vector4f(0.0f, scale, 0.0f, value);
					filter->color.matrix.row_2 = Vector4f(0.0f, 0.0f, scale, value);
					filter->color.matrix.row_3 = Vector4f(0.0f, 0.0f, 0.0f, 1.0f);
				} else if(name == "grayscale") {
					filter->type = ShaderFilterColor;
					float32_t value = Rml::Get(parameters, "value", 1.0f);
					float32_t scale = 1.0f - value;
					filter->color.matrix.row_0 = Vector4f(0.2126f * value + scale, 0.7152f * value, 0.0722f * value, 0.0f);
					filter->color.matrix.row_1 = Vector4f(0.2126f * value, 0.7152f * value + scale, 0.0722f * value, 0.0f);
					filter->color.matrix.row_2 = Vector4f(0.2126f * value, 0.7152f * value, 0.0722f * value + scale, 0.0f);
					filter->color.matrix.row_3 = Vector4f(0.0f, 0.0f, 0.0f, 1.0f);
				} else if(name == "sepia") {
					filter->type = ShaderFilterColor;
					float32_t value = Rml::Get(parameters, "value", 1.0f);
					float32_t scale = 1.0f - value;
					filter->color.matrix.row_0 = Vector4f(0.393f * value + scale, 0.769f * value, 0.189f * value, 0.0f);
					filter->color.matrix.row_1 = Vector4f(0.349f * value, 0.686f * value + scale, 0.168f * value, 0.0f);
					filter->color.matrix.row_2 = Vector4f(0.272f * value, 0.534f * value, 0.131f * value + scale, 0.0f);
					filter->color.matrix.row_3 = Vector4f(0.0f, 0.0f, 0.0f, 1.0f);
				} else if(name == "saturate") {
					filter->type = ShaderFilterColor;
					float32_t value = Rml::Get(parameters, "value", 1.0f);
					filter->color.matrix.row_0 = Vector4f(0.213f + 0.787f * value, 0.715f - 0.715f * value, 0.072f - 0.072f * value, 0.0f);
					filter->color.matrix.row_1 = Vector4f(0.213f - 0.213f * value, 0.715f + 0.285f * value, 0.072f - 0.072f * value, 0.0f);
					filter->color.matrix.row_2 = Vector4f(0.213f - 0.213f * value, 0.715f - 0.715f * value, 0.072f + 0.928f * value, 0.0f);
					filter->color.matrix.row_3 = Vector4f(0.0f, 0.0f, 0.0f, 1.0f);
				} else if(name == "hue-rotate") {
					filter->type = ShaderFilterColor;
					float32_t value = Rml::Get(parameters, "value", 1.0f);
					float32_t s = sin(value);
					float32_t c = cos(value);
					filter->color.matrix.row_0 = Vector4f(0.213f + 0.787f * c - 0.213f * s, 0.715f - 0.715f * c - 0.715f * s, 0.072f - 0.072f * c + 0.928f * s, 0.0f);
					filter->color.matrix.row_1 = Vector4f(0.213f - 0.213f * c + 0.143f * s, 0.715f + 0.285f * c + 0.140f * s, 0.072f - 0.072f * c - 0.283f * s, 0.0f);
					filter->color.matrix.row_2 = Vector4f(0.213f - 0.213f * c - 0.787f * s, 0.715f - 0.715f * c + 0.715f * s, 0.072f + 0.928f * c + 0.072f * s, 0.0f);
					filter->color.matrix.row_3 = Vector4f(0.0f, 0.0f, 0.0f, 1.0f);
				} else {
					TS_LOGF(Error, "RmlUi::RenderInterface::CompileFilter(): unknown filter \"%s\"\n", name.c_str());
					delete filter;
					return 0;
				}
				return (Rml::CompiledFilterHandle)filter;
			}
			virtual void ReleaseFilter(Rml::CompiledFilterHandle filter) {
				released_filters.append(filter);
			}
			
			// shaders
			virtual Rml::CompiledShaderHandle CompileShader(const Rml::String &name, const Rml::Dictionary &parameters) {
				ShaderArgs *shader = new ShaderArgs();
				if(name == "linear-gradient") {
					bool repeating = Rml::Get(parameters, "repeating", false);
					shader->type = ShaderGradientLinear;
					shader->flags = (repeating) ? ShaderFlagRepeat : ShaderFlagNone;
					Vector2f p0 = Rml::Get(parameters, "p0", Rml::Vector2f(0.0f));
					Vector2f p1 = Rml::Get(parameters, "p1", Rml::Vector2f(0.0f));
					shader->parameters = Vector4f(p0, p1);
				} else if(name == "radial-gradient") {
					bool repeating = Rml::Get(parameters, "repeating", false);
					shader->type = ShaderGradientRadial;
					shader->flags = (repeating) ? ShaderFlagRepeat : ShaderFlagNone;
					Vector2f center = Rml::Get(parameters, "center", Rml::Vector2f(0.0f));
					Vector2f radius = Rml::Get(parameters, "radius", Rml::Vector2f(1.0f));
					shader->parameters = Vector4f(center, Vector2f::one / radius);
				} else if(name == "conic-gradient") {
					bool repeating = Rml::Get(parameters, "repeating", false);
					shader->type = ShaderGradientConic;
					shader->flags = (repeating) ? ShaderFlagRepeat : ShaderFlagNone;
					Vector2f center = Rml::Get(parameters, "center", Rml::Vector2f(0.0f));
					float32_t angle = Rml::Get(parameters, "angle", 0.0f);
					shader->parameters = Vector4f(center, cos(angle), sin(angle));
				} else if(name == "shader") {
					const Rml::String &value = Rml::Get(parameters, "value", Rml::String());
					TS_LOGF(Error, "RmlUi::RenderInterface::CompileShader(): unknown shader \"%s\"\n", value.c_str());
					delete shader;
					return 0;
				} else {
					TS_LOGF(Error, "RmlUi::RenderInterface::CompileShader(): unknown shader \"%s\"\n", name.c_str());
					delete shader;
					return 0;
				}
				auto it = parameters.find("color_stop_list");
				if(it != parameters.end() && it->second.GetType() == Rml::Variant::COLORSTOPLIST) {
					const Rml::ColorStopList &stops = it->second.GetReference<Rml::ColorStopList>();
					shader->num_colors = min((uint32_t)stops.size(), (uint32_t)NumShaderColors);
					for(uint32_t i = 0; i < shader->num_colors; i++) {
						const Rml::ColorStop &stop = stops[i];
						shader->colors[i] = Color(stop.color.red, stop.color.green, stop.color.blue, stop.color.alpha);
						shader->values[i] = stop.position.number;
					}
				}
				return (Rml::CompiledShaderHandle)shader;
			}
			virtual void RenderShader(Rml::CompiledShaderHandle shader, Rml::CompiledGeometryHandle geometry, Rml::Vector2f translate, Rml::TextureHandle texture) {
				CommandArgs &args = commands.append();
				args.type = CommandRenderGeometry;
				args.render.translate = translate;
				args.render.geometry = (GeometryArgs*)geometry;
				args.render.texture = (TextureArgs*)texture;
				args.render.shader = (ShaderArgs*)shader;
				args.render.stencil = ShaderUnknown;
			}
			virtual void ReleaseShader(Rml::CompiledShaderHandle shader) {
				released_shaders.append(shader);
			}
			
		private:
			
			struct FilterArgs;
			struct CommandArgs;
			
			// release commands
			void release_commands() {
				for(CommandArgs &args : commands) {
					if(args.type == CommandSetTarget) {
						delete args.target.texture;
					} else if(args.type == CommandBlendLayers) {
						delete args.blend.src;
						delete args.blend.dest;
					} else if(args.type == CommandCopyTexture) {
						delete args.copy.src;
						delete args.copy.dest;
					}
				}
				command_textures.clear();
				command_filters.clear();
				commands.clear();
			}
			
			// release resources
			void release_resources() {
				for(Rml::CompiledGeometryHandle handle : released_geometries) {
					delete (GeometryArgs*)handle;
				}
				for(Rml::CompiledFilterHandle handle : released_filters) {
					FilterArgs *filter = (FilterArgs*)handle;
					if(filter->type == ShaderFilterMask && filter->mask.texture) {
						release_texture(*filter->mask.texture);
						delete filter->mask.texture;
					}
					delete filter;
				}
				for(Rml::CompiledShaderHandle handle : released_shaders) {
					delete (ShaderArgs*)handle;
				}
				for(Rml::TextureHandle handle : released_textures) {
					TextureArgs *texture = (TextureArgs*)handle;
					release_texture(texture->texture);
					delete texture;
				}
				released_geometries.clear();
				released_filters.clear();
				released_shaders.clear();
				released_textures.clear();
			}
			
			// shader types
			enum ShaderType {
				ShaderUnknown = 0,
				ShaderSolid,
				ShaderTexture,
				ShaderStencil,
				ShaderStencilInverse,
				ShaderStencilIntersect,
				ShaderFilterCopy,
				ShaderFilterMask,
				ShaderFilterBlur,
				ShaderFilterColor,
				ShaderFilterShadow,
				ShaderGradientLinear,
				ShaderGradientRadial,
				ShaderGradientConic,
				NumShaders,
			};
			
			// shader flags
			enum ShaderFlag {
				ShaderFlagNone = 0,
				ShaderFlagOpaque	= (1 << 0),		// opaque shader
				ShaderFlagRepeat	= (1 << 1),		// repeat shader
				ShaderFlagFlipped	= (1 << 2),		// flipped shader
				ShaderFlagStencil	= (1 << 3),		// stencil shader
				ShaderFlagInverse	= (1 << 4),		// inverse shader
			};
			
			// create pipeline
			Pipeline get_pipeline(const Target &target, ShaderType type, uint32_t flags = ShaderFlagNone) {
				
				// flipped target
				if(target.isFlipped()) flags |= ShaderFlagFlipped;
				
				// pipeline hash
				uint64_t hash = flags;
				hash = hash * NumShaders + type;
				hash = hash * NumFormats + target.getColorFormat();
				hash = hash * NumFormats + target.getDepthFormat();
				hash = hash * 16 + target.getMultisample();
				
				// find pipeline
				auto it = pipelines.find(hash);
				if(it) return it->data;
				
				// shader type macros
				static const char *shader_type_macros[] = {
					nullptr,
					"; SOLID_SHADER=1",
					"; TEXTURE_SHADER=1",
					"; STENCIL_SHADER=1",
					"; STENCIL_SHADER=1",
					"; STENCIL_SHADER=1",
					"; FILTER_SHADER=1; FILTER_COPY_SHADER=1",
					"; FILTER_SHADER=1; FILTER_MASK_SHADER=1",
					"; FILTER_SHADER=1; FILTER_BLUR_SHADER=1",
					"; FILTER_SHADER=1; FILTER_COLOR_SHADER=1",
					"; FILTER_SHADER=1; FILTER_SHADOW_SHADER=1",
					"; GRADIENT_SHADER=1; GRADIENT_LINEAR_SHADER=1",
					"; GRADIENT_SHADER=1; GRADIENT_RADIAL_SHADER=1",
					"; GRADIENT_SHADER=1; GRADIENT_CONIC_SHADER=1",
				};
				TS_STATIC_ASSERT(TS_COUNTOF(shader_type_macros) == NumShaders);
				
				// shader macros
				String shader_macros;
				shader_macros = shader_type_macros[type];
				bool is_texture = shader_macros.contains("TEXTURE_SHADER");
				bool is_filter = shader_macros.contains("FILTER_SHADER");
				bool is_gradient = shader_macros.contains("GRADIENT_SHADER");
				if(flags & ShaderFlagOpaque) shader_macros += "; FLAG_OPAQUE=1";
				if(flags & ShaderFlagRepeat) shader_macros += "; FLAG_REPEAT=1";
				if(flags & ShaderFlagFlipped) shader_macros += "; FLAG_FLIPPED=1";
				if(is_filter) shader_macros += String::format("; NUM_SHADER_SAMPLES=%uu", NumShaderSamples);
				if(is_gradient) shader_macros += String::format("; NUM_SHADER_COLORS=%uu", NumShaderColors);
				
				// create pipeline
				Pipeline pipeline = device.createPipeline();
				if(!is_filter) {
					pipeline.setUniformMasks(0, 2, Shader::MaskVertex);
					pipeline.addAttribute(Pipeline::AttributePosition, FormatRGf32, 0, offsetof(Rml::Vertex, position), sizeof(Rml::Vertex));
					pipeline.addAttribute(Pipeline::AttributeTexCoord, FormatRGf32, 0, offsetof(Rml::Vertex, tex_coord), sizeof(Rml::Vertex));
					pipeline.addAttribute(Pipeline::AttributeColor, FormatRGBAu8n, 0, offsetof(Rml::Vertex, colour), sizeof(Rml::Vertex));
				} else {
					pipeline.setUniformMask(0, Shader::MaskFragment);
				}
				if(is_gradient) pipeline.setUniformMask(2, Shader::MaskFragment);
				if(is_texture || is_filter) pipeline.setSamplerMask(0, Shader::MaskFragment);
				if(is_texture || is_filter) pipeline.setTextureMask(0, Shader::MaskFragment);
				if(type == ShaderFilterMask) pipeline.setTextureMask(1, Shader::MaskFragment);
				if(!(flags & ShaderFlagOpaque)) pipeline.setBlend(Pipeline::BlendOpAdd, Pipeline::BlendFuncOne, Pipeline::BlendFuncInvSrcAlpha);
				pipeline.setMultisample(target.getMultisample());
				pipeline.setColorFormat(target.getColorFormat());
				pipeline.setDepthFormat(target.getDepthFormat());
				pipeline.setDepthFunc(Pipeline::DepthFuncAlways);
				pipeline.setScissorTest(true);
				if(type == ShaderStencil) {
					pipeline.setColorMask(Pipeline::ColorMaskNone);
					pipeline.setStencilFunc(Pipeline::StencilFuncAlways, Pipeline::StencilOpReplace);
					pipeline.setStencilMask(0xff);
				} else if(type == ShaderStencilInverse) {
					pipeline.setColorMask(Pipeline::ColorMaskNone);
					pipeline.setStencilFunc(Pipeline::StencilFuncAlways, Pipeline::StencilOpReplace);
					pipeline.setStencilMask(0xff);
				} else if(type == ShaderStencilIntersect) {
					pipeline.setColorMask(Pipeline::ColorMaskNone);
					pipeline.setStencilFunc(Pipeline::StencilFuncEqual, Pipeline::StencilOpIncrWrap);
					pipeline.setStencilMask(0xff);
				} else if(flags & ShaderFlagStencil) {
					if(flags & ShaderFlagInverse) pipeline.setStencilFunc(Pipeline::StencilFuncNotEqual, Pipeline::StencilOpKeep);
					else pipeline.setStencilFunc(Pipeline::StencilFuncEqual, Pipeline::StencilOpKeep);
					pipeline.setStencilMask(0xff);
				}
				if(!pipeline.createShaderGLSL(Shader::TypeVertex, shader_source.get(), "VERTEX_SHADER=1%s", shader_macros.get()) ||
					!pipeline.createShaderGLSL(Shader::TypeFragment, shader_source.get(), "FRAGMENT_SHADER=1%s", shader_macros.get()) ||
					!pipeline.create()) {
					TS_LOG(Error, "RmlUi::RenderInterface::create(): can't create pipeline\n");
					pipeline.clearPtr();
				}
				pipelines.append(hash, pipeline);
				
				return pipeline;
			}
			
			// render geometry
			void render_geometry(Command &command, const CommandArgs &args) {
				
				// transform parameters
				struct TS_ALIGNAS16 TransformParameters {
					Vector4f transform;
					Vector2f translate;
				};
				
				TransformParameters parameters;
				parameters.transform = Vector4f(1.0f, 1.0f, 0.0f, 0.0f);
				if(args.render.texture && args.render.texture->is_flipped) {
					parameters.transform = Vector4f(1.0f, -1.0f, 0.0f, 1.0f);
				}
				parameters.translate = args.render.translate;
				command.setUniform(1, parameters);
				
				// shader uniforms
				if(args.render.shader) {
					ShaderType type = args.render.shader->type;
					if(type >= ShaderGradientLinear && type <= ShaderGradientConic) {
						command.setUniformData(2, args.render.shader, sizeof(ShaderArgs));
					}
				}
				
				// render geometry
				GeometryArgs *geometry = args.render.geometry;
				command.setVertexData(0, geometry->vertices.get(), geometry->vertices.bytes());
				command.setIndexData(FormatRu32, geometry->indices.get(), geometry->indices.bytes());
				command.drawElements(geometry->indices.size());
			}
			
			// render filter
			bool render_filter(Target &target, const FilterArgs &args, const Scissor &scissor, Texture &dest_texture, Texture &src_texture, uint32_t flags, const InitializerList<Texture> &excludes = {}) {
				
				ShaderType type = args.type;
				
				// blur is two pass filter
				if(type == ShaderFilterBlur && args.blur.sigma > 0.1f) {
					
					// blur parameters
					struct TS_ALIGNAS16 BlurParameters {
						float32_t weights[NumShaderSamples];
						Vector4f texcoords;
						Vector2f direction;
					};
					
					BlurParameters parameters;
					parameters.weights[0] = 1.0f;
					
					// texcoords range
					float32_t texcoord_dx = 1.0f / src_texture.getWidth();
					float32_t texcoord_dy = 1.0f / src_texture.getHeight();
					parameters.texcoords.x = (scissor.x + 0.5f) * texcoord_dx;
					parameters.texcoords.y = (scissor.y + 0.5f) * texcoord_dy;
					parameters.texcoords.z = (scissor.x + scissor.width - 0.5f) * texcoord_dx;
					parameters.texcoords.w = (scissor.y + scissor.height - 0.5f) * texcoord_dy;
					
					// blur weights
					float32_t weight = 1.0f;
					float32_t isigma = -1.0f / max(args.blur.sigma * args.blur.sigma * 2.0f, 1e-12f);
					for(uint32_t i = 1; i < NumShaderSamples; i++) {
						float32_t d = i * 2.0f - 0.5f;
						parameters.weights[i] = exp(d * d * isigma);
						if(parameters.weights[i] < 1e-3f) parameters.weights[i] = 0.0f;
						else weight += parameters.weights[i] * 2.0f;
					}
					float32_t iweight = 1.0f / max(weight, 1e-12f);
					for(uint32_t i = 0; i < NumShaderSamples; i++) {
						parameters.weights[i] *= iweight;
					}
					
					// temporal texture
					Texture blur_texture = create_texture(render_width, render_height, excludes);
					if(!blur_texture) return false;
					
					// first pass
					parameters.direction.x = texcoord_dx;
					parameters.direction.y = texcoord_dy;
					Pipeline pipeline = get_pipeline(target, type, ShaderFlagOpaque);
					target.setColorTexture(blur_texture, Target::OpClearStore);
					if(!pipeline || !target.begin()) {
						release_texture(blur_texture);
						return false;
					}
					{
						Command command = device.createCommand(target);
						command.setPipeline(pipeline);
						command.setScissor(0, scissor);
						command.setUniform(0, parameters);
						command.setSampler(0, linear_sampler);
						command.setTexture(0, src_texture);
						command.drawArrays(3);
					}
					target.end();
					
					// flush texture
					device.flushTexture(blur_texture);
					
					// second pass
					parameters.direction.x = -texcoord_dx;
					parameters.direction.y = texcoord_dy;
					pipeline = get_pipeline(target, type, flags);
					target.setColorTexture(dest_texture, Target::OpLoadStore);
					if(!pipeline || !target.begin()) {
						release_texture(blur_texture);
						return false;
					}
					{
						Command command = device.createCommand(target);
						command.setPipeline(pipeline);
						command.setScissor(0, scissor);
						command.setUniform(0, parameters);
						command.setSampler(0, linear_sampler);
						command.setTexture(0, blur_texture);
						command.drawArrays(3);
					}
					target.end();
					
					// flush texture
					device.flushTexture(dest_texture);
					
					release_texture(blur_texture);
					return true;
				}
				
				// if source and destination are the same
				if(src_texture == dest_texture) {
					
					// temporal texture
					Texture copy_texture = create_texture(render_width, render_height, excludes);
					if(!copy_texture) return false;
					
					// copy source texture
					Pipeline pipeline = get_pipeline(target, ShaderFilterCopy, ShaderFlagOpaque);
					target.setColorTexture(copy_texture, Target::OpClearStore);
					if(!pipeline || !target.begin()) {
						release_texture(copy_texture);
						return false;
					}
					{
						Command command = device.createCommand(target);
						command.setPipeline(pipeline);
						command.setScissor(0, scissor);
						command.setUniform(0, 1.0f);
						command.setSampler(0, linear_sampler);
						command.setTexture(0, src_texture);
						command.drawArrays(3);
					}
					target.end();
					
					// flush texture
					device.flushTexture(copy_texture);
					
					// run filter
					bool ret = render_filter(target, args, scissor, dest_texture, copy_texture, flags);
					release_texture(copy_texture);
					return ret;
				}
				
				// shadow is multi pass filter
				if(type == ShaderFilterShadow) {
					
					// create shadow texture
					Texture shadow_texture;
					if(args.shadow.sigma > 0.2f) {
						shadow_texture = create_texture(render_width, render_height, excludes);
						if(!shadow_texture) return false;
					}
					
					// filter parameters
					struct TS_ALIGNAS16 ShadowParameters {
						Color shadow_color;
						Vector4f texcoords;
						Vector2f offset;
					};
					
					ShadowParameters parameters;
					parameters.shadow_color = args.shadow.color;
					
					// texcoords range
					float32_t texcoord_dx = 1.0f / src_texture.getWidth();
					float32_t texcoord_dy = 1.0f / src_texture.getHeight();
					parameters.texcoords.x = (scissor.x + 0.5f) * texcoord_dx;
					parameters.texcoords.y = (scissor.y + 0.5f) * texcoord_dy;
					parameters.texcoords.z = (scissor.x + scissor.width - 0.5f) * texcoord_dx;
					parameters.texcoords.w = (scissor.y + scissor.height - 0.5f) * texcoord_dy;
					parameters.offset.x = args.shadow.offset.x * texcoord_dx;
					parameters.offset.y = -args.shadow.offset.y * texcoord_dy;
					
					// shadow texture
					Pipeline pipeline = get_pipeline(target, type, flags);
					if(shadow_texture) target.setColorTexture(shadow_texture, Target::OpClearStore);
					else target.setColorTexture(dest_texture, Target::OpLoadStore);
					if(!pipeline || !target.begin()) {
						release_texture(shadow_texture);
						return false;
					}
					{
						Command command = device.createCommand(target);
						command.setPipeline(pipeline);
						command.setScissor(0, scissor);
						command.setUniform(0, parameters);
						command.setSampler(0, linear_sampler);
						command.setTexture(0, src_texture);
						command.drawArrays(3);
					}
					target.end();
					
					// blur shadow texture
					if(shadow_texture) {
						
						// flush texture
						device.flushTexture(shadow_texture);
						
						// blur shadow texture
						FilterArgs blur_filter;
						blur_filter.type = ShaderFilterBlur;
						blur_filter.blur.sigma = args.shadow.sigma;
						if(!render_filter(target, blur_filter, scissor, dest_texture, shadow_texture, flags, excludes)) {
							release_texture(shadow_texture);
							return false;
						}
						
						release_texture(shadow_texture);
					}
					
					// flush texture
					device.flushTexture(dest_texture);
					
					// blend source on top of the shadow
					pipeline = get_pipeline(target, ShaderFilterCopy, flags & ~ShaderFlagOpaque);
					target.setColorTexture(dest_texture, Target::OpLoadStore);
					if(!pipeline || !target.begin()) return false;
					{
						Command command = device.createCommand(target);
						command.setPipeline(pipeline);
						command.setScissor(0, scissor);
						command.setUniform(0, 1.0f);
						command.setSampler(0, linear_sampler);
						command.setTexture(0, src_texture);
						command.drawArrays(3);
					}
					target.end();
					
					// flush texture
					device.flushTexture(dest_texture);
					
					return true;
				}
				
				// replace blur with copy shader
				if(type == ShaderFilterBlur) type = ShaderFilterCopy;
				
				// run filter
				Pipeline pipeline = get_pipeline(target, type, flags);
				target.setColorTexture(dest_texture, Target::OpLoadStore);
				if(!pipeline || !target.begin()) return false;
				{
					Command command = device.createCommand(target);
					command.setPipeline(pipeline);
					command.setScissor(0, scissor);
					command.setSampler(0, linear_sampler);
					command.setTexture(0, src_texture);
					if(args.type == ShaderFilterBlur) {
						command.setUniform(0, 1.0f);
					} else if(type == ShaderFilterCopy) {
						command.setUniform(0, args.copy.value);
					} else if(type == ShaderFilterMask && args.mask.texture) {
						command.setTexture(1, *args.mask.texture);
						command.setUniform(0, args.mask.transform);
					} else if(type == ShaderFilterColor) {
						command.setUniform(0, args.color.matrix);
					} else {
						TS_LOGF(Error, "RmlUi::RenderInterface::render_filter(): unknown shader %u\n", type);
						return false;
					}
					command.drawArrays(3);
				}
				target.end();
				
				// flush texture
				device.flushTexture(dest_texture);
				
				return true;
			}
			
			// dynamic textures
			Texture create_texture(uint32_t width, uint32_t height, const InitializerList<Texture> &excludes = {}) {
				for(uint32_t i = 0; i < textures.size(); i++) {
					if(textures[i].getWidth() != width) continue;
					if(textures[i].getHeight() != height) continue;
					bool is_exclude = false;
					for(const Texture &exclude : excludes) {
						if(textures[i] == exclude) {
							is_exclude = true;
							break;
						}
					}
					if(is_exclude) continue;
					Texture texture = textures[i];
					textures.removeFast(i);
					frames.removeFast(i);
					return texture;
				}
				Texture texture = device.createTexture2D(FormatRGBAu8n, width, height, Texture::FlagTarget | Texture::FlagSource);
				if(texture) {
					device.clearTexture(texture, nullptr);
					return texture;
				}
				TS_LOGF(Error, "RmlUi::RenderInterface::create_texture(): can't create %ux%u texture\n", width, height);
				return texture;
			}
			void release_texture(Texture &texture) {
				if(texture && texture.hasFlag(Texture::FlagTarget)) {
					if(!textures.find(texture)) {
						textures.append(texture);
						frames.append(frame);
					}
				} else {
					device.releaseTexture(texture);
				}
			}
			
			// command types
			enum CommandType {
				CommandUnknown = 0,
				CommandSetTarget,
				CommandSetScissor,
				CommandSetStencil,
				CommandSetTransform,
				CommandRenderGeometry,
				CommandBlendLayers,
				CommandCopyTexture,
				NumCommands,
			};
			
			enum {
				NumShaderColors		= 32,
				NumShaderSamples	= 32,
				NumTextureFrames	= 16,
			};
			
			struct GeometryArgs {
				Array<Rml::Vertex> vertices;			// geometry vertices
				Array<uint32_t> indices;				// geometry indices
			};
			
			struct TextureArgs {
				Texture texture;						// texture pointer
				bool is_flipped = false;				// flipped flag
			};
			
			struct FilterArgs {
				FilterArgs() { }
				ShaderType type = ShaderUnknown;		// shader type
				union {
					struct {
						float32_t value;				// copy value
					} copy;
					struct {
						float32_t sigma;				// gaussian sigma
					} blur;
					struct {
						Matrix4x4f matrix;				// color matrix
					} color;
					struct {
						Texture *texture;				// mask texture
						Vector4f transform;				// mask transform
					} mask;
					struct {
						Color color;					// shadow color
						Vector2f offset;				// shadow offset
						float32_t sigma;				// gaussian sigma
					} shadow;
				};
			};
			
			struct ShaderArgs {
				ShaderType type = ShaderUnknown;		// shader type
				uint32_t flags = ShaderFlagNone;		// shader flags
				uint32_t num_colors;					// number of colors
				Vector4f parameters;					// shader parameters
				Color colors[NumShaderColors];			// color values
				float32_t values[NumShaderColors];		// step values
			};
			
			struct CommandArgs {
				CommandArgs() { }
				CommandType type = CommandUnknown;
				union {
					struct {
						Texture *texture;				// target texture
						Target::Operation operation;	// target operation
					} target;
					struct {
						Scissor scissor;				// scissor rectangle
						bool enable;					// scissor enable
					} scissor;
					struct {
						bool enable;					// stencil enable
					} stencil;
					struct {
						Matrix4x4f transform;			// transformation matrix
						bool identity;					// identity transform
					} transform;
					struct {
						Vector2f translate;				// translation vector
						GeometryArgs *geometry;			// render geometry
						TextureArgs *texture;			// render texture
						ShaderArgs *shader;				// render shader
						ShaderType stencil;				// render stencil
					} render;
					struct {
						Texture *src;					// source texture
						Texture *dest;					// destination texture
						Region region;					// blend region
						Scissor scissor;				// blend scissor
						Rml::BlendMode mode;			// blending mode
						uint32_t base_filter;			// base filter index
						uint32_t num_filters;			// number of filters
					} blend;
					struct {
						Texture *src;					// source texture
						Texture *dest;					// destination texture
						Region region;					// copy region
					} copy;
				};
			};
			
			Device device;
			
			String shader_source;
			Target texture_target;
			Sampler linear_sampler;
			
			uint32_t render_width = 0;
			uint32_t render_height = 0;
			
			Map<uint64_t, Pipeline> pipelines;
			
			uint32_t frame = 0;
			ArrayStack<Texture, 128> textures;
			ArrayStack<uint32_t, 128> frames;
			
			Region command_region;
			Scissor command_scissor;
			bool command_scissor_enable = false;
			ArrayStack<Texture, 128> command_textures;
			ArrayStack<FilterArgs*, 128> command_filters;
			ArrayStack<CommandArgs, 1024> commands;
			
			ArrayStack<Rml::CompiledGeometryHandle, 1024> released_geometries;
			ArrayStack<Rml::CompiledFilterHandle, 128> released_filters;
			ArrayStack<Rml::CompiledShaderHandle, 128> released_shaders;
			ArrayStack<Rml::TextureHandle, 128> released_textures;
	};
	
	/*
	 */
	RmlUi::RmlUi() {
		
	}
	
	RmlUi::RmlUi(Window &window, Device &device) {
		init(window, device);
	}
	
	RmlUi::~RmlUi() {
		clear();
	}
	
	/*
	 */
	void RmlUi::clear() {
		
		// shutdown RmlUi
		if(isInitialized()) {
			context = nullptr;
			Rml::Shutdown();
		}
		
		// clear interfaces
		file_interface.clear();
		system_interface.clear();
		render_interface.clear();
		
		// restore callbacks
		if(mouse_pressed) window.setMousePressedCallback(mouse_pressed);
		if(mouse_released) window.setMouseReleasedCallback(mouse_released);
		if(mouse_changed) window.setMouseChangedCallback(mouse_changed);
		if(mouse_rotated) window.setMouseRotatedCallback(mouse_rotated);
		if(keyboard_pressed) window.setKeyboardPressedCallback(keyboard_pressed);
		if(keyboard_released) window.setKeyboardReleasedCallback(keyboard_released);
		mouse_pressed.clear();
		mouse_released.clear();
		mouse_changed.clear();
		mouse_rotated.clear();
		keyboard_pressed.clear();
		keyboard_released.clear();
		
		// clear pointers
		window.clearPtr();
		device.clearPtr();
	}
	
	/*
	 */
	bool RmlUi::init(Window &w, Device &d, const char *name, float32_t scale) {
		
		TS_ASSERT(!isInitialized() && "RmlUi::init(): is already initialized");
		
		window = w;
		device = d;
		
		// create interfaces
		file_interface = makeAutoPtr(new FileInterface());
		system_interface = makeAutoPtr(new SystemInterface(window));
		render_interface = makeAutoPtr(new RenderInterface(device));
		if(!render_interface->create()) {
			TS_LOG(Error, "RmlUi::init(): can't create RenderInterface\n");
			clear();
			return false;
		}
		
		// set interfaces
		Rml::SetFileInterface(file_interface.get());
		Rml::SetSystemInterface(system_interface.get());
		Rml::SetRenderInterface(render_interface.get());
		
		// initialize RmlUi
		if(!Rml::Initialise()) {
			TS_LOG(Error, "RmlUi::init(): can't initialize RmlUi\n");
			clear();
			return false;
		}
		
		// create context
		if(name == nullptr) name = "main";
		context = Rml::CreateContext(name, Rml::Vector2i(window.getWidth(), window.getHeight()));
		if(context == nullptr) {
			TS_LOG(Error, "RmlUi::init(): can't create Context\n");
			clear();
			return false;
		}
		
		// window scale factor
		if(scale == 0.0f) scale = window.getScale();
		context->SetDensityIndependentPixelRatio(scale);
		
		// save callbacks
		mouse_pressed = window.getMousePressedCallback();
		mouse_released = window.getMouseReleasedCallback();
		mouse_changed = window.getMouseChangedCallback();
		mouse_rotated = window.getMouseRotatedCallback();
		keyboard_pressed = window.getKeyboardPressedCallback();
		keyboard_released = window.getKeyboardReleasedCallback();
		
		// mouse callbacks
		window.setMousePressedCallback([this](Window::Button button) {
			if(isInitialized() && isEnabled()) context->ProcessMouseButtonDown(translate_mouse(button), get_key_state());
			if(mouse_pressed) mouse_pressed(button);
		});
		window.setMouseReleasedCallback([this](Window::Button button) {
			if(isInitialized() && isEnabled()) context->ProcessMouseButtonUp(translate_mouse(button), get_key_state());
			if(mouse_released) mouse_released(button);
		});
		window.setMouseChangedCallback([this](int32_t x, int32_t y) {
			if(isInitialized() && isEnabled()) context->ProcessMouseMove(x, window.getHeight() - y - 1, get_key_state());
			if(mouse_changed) mouse_changed(x, y);
		});
		window.setMouseRotatedCallback([this](Window::Axis axis, float32_t delta) {
			if(isInitialized() && isEnabled()) {
				if(axis == Window::AxisX) context->ProcessMouseWheel(Rml::Vector2f(delta, 0.0f), get_key_state());
				if(axis == Window::AxisY) context->ProcessMouseWheel(Rml::Vector2f(0.0f, -delta), get_key_state());
			}
			if(mouse_rotated) mouse_rotated(axis, delta);
		});
		
		// keyboard callbacks
		window.setKeyboardPressedCallback([this](uint32_t key, uint32_t code) {
			if(isInitialized() && isEnabled()) {
				context->ProcessKeyDown(translate_keyboard(key), get_key_state());
				if(code && (code < Window::KeyNone || code > Window::NumKeys)) context->ProcessTextInput((Rml::Character)code);
			}
			if(keyboard_pressed) keyboard_pressed(key, code);
		});
		window.setKeyboardReleasedCallback([this](uint32_t key) {
			if(isInitialized() && isEnabled()) context->ProcessKeyUp(translate_keyboard(key), get_key_state());
			if(keyboard_released) keyboard_released(key);
		});
		
		return true;
	}
	
	/*
	 */
	bool RmlUi::update() {
		
		// check status
		if(!isInitialized()) {
			TS_LOG(Error, "RmlUi::render(): is not initialized\n");
			return false;
		}
		
		// resize context
		uint32_t width = window.getWidth();
		uint32_t height = window.getHeight();
		context->SetDimensions(Rml::Vector2i(width, height));
		
		// update context
		return render_interface->update(context);
	}
	
	/*
	 */
	bool RmlUi::render(const Target &target, Command &command) {
		
		// check status
		if(!isInitialized()) {
			TS_LOG(Error, "RmlUi::render(): is not initialized\n");
			return false;
		}
		
		// render context
		return render_interface->render(target, command, context);
	}
	
	bool RmlUi::render(Texture &color_texture, Texture &depth_texture) {
		
		// check status
		if(!isInitialized()) {
			TS_LOG(Error, "RmlUi::render(): is not initialized\n");
			return false;
		}
		
		// render context
		return render_interface->render(color_texture, depth_texture, context);
	}
	
	/*
	 */
	bool RmlUi::draw(const Target &target, Command &command, Texture &texture) {
		
		// check status
		if(!isInitialized()) {
			TS_LOG(Error, "RmlUi::draw(): is not initialized\n");
			return false;
		}
		
		// draw texture
		return render_interface->draw(target, command, texture);
	}
	
	/*
	 */
	void RmlUi::setEnabled(bool enabled) {
		is_enabled = enabled;
	}
	
	/*
	 */
	int32_t RmlUi::get_key_state() const {
		int32_t state = 0;
		if(window.getKeyboardKey(Window::KeyCtrl)) state |= Rml::Input::KM_CTRL;
		if(window.getKeyboardKey(Window::KeyShift)) state |= Rml::Input::KM_SHIFT;
		if(window.getKeyboardKey(Window::KeyAlt)) state |= Rml::Input::KM_ALT;
		if(window.getKeyboardKey(Window::KeyCaps)) state |= Rml::Input::KM_CAPSLOCK;
		if(window.getKeyboardKey(Window::KeyNum)) state |= Rml::Input::KM_NUMLOCK;
		return state;
	}
	
	int32_t RmlUi::translate_mouse(Window::Button button) {
		if(button == Window::ButtonLeft) return 0;
		if(button == Window::ButtonLeft2) return 0;
		if(button == Window::ButtonRight) return 1;
		if(button == Window::ButtonRight2) return 1;
		if(button == Window::ButtonMiddle) return 2;
		if(button == Window::ButtonMiddle2) return 2;
		if(button == Window::ButtonBack) return 3;
		if(button == Window::ButtonBack2) return 3;
		if(button == Window::ButtonForward) return 4;
		if(button == Window::ButtonForward2) return 4;
		return -1;
	}
	
	Rml::Input::KeyIdentifier RmlUi::translate_keyboard(uint32_t key) {
		switch(key) {
			case ' ': return Rml::Input::KI_SPACE;
			case '1': return Rml::Input::KI_1;
			case '2': return Rml::Input::KI_2;
			case '3': return Rml::Input::KI_3;
			case '4': return Rml::Input::KI_4;
			case '5': return Rml::Input::KI_5;
			case '6': return Rml::Input::KI_6;
			case '7': return Rml::Input::KI_7;
			case '8': return Rml::Input::KI_8;
			case '9': return Rml::Input::KI_9;
			case '0': return Rml::Input::KI_0;
			case 'a': return Rml::Input::KI_A;
			case 'b': return Rml::Input::KI_B;
			case 'c': return Rml::Input::KI_C;
			case 'd': return Rml::Input::KI_D;
			case 'e': return Rml::Input::KI_E;
			case 'f': return Rml::Input::KI_F;
			case 'g': return Rml::Input::KI_G;
			case 'h': return Rml::Input::KI_H;
			case 'i': return Rml::Input::KI_I;
			case 'j': return Rml::Input::KI_J;
			case 'k': return Rml::Input::KI_K;
			case 'l': return Rml::Input::KI_L;
			case 'm': return Rml::Input::KI_M;
			case 'n': return Rml::Input::KI_N;
			case 'o': return Rml::Input::KI_O;
			case 'p': return Rml::Input::KI_P;
			case 'q': return Rml::Input::KI_Q;
			case 'r': return Rml::Input::KI_R;
			case 's': return Rml::Input::KI_S;
			case 't': return Rml::Input::KI_T;
			case 'u': return Rml::Input::KI_U;
			case 'v': return Rml::Input::KI_V;
			case 'w': return Rml::Input::KI_W;
			case 'x': return Rml::Input::KI_X;
			case 'y': return Rml::Input::KI_Y;
			case 'z': return Rml::Input::KI_Z;
			case ';': return Rml::Input::KI_OEM_1;
			case '=': return Rml::Input::KI_OEM_PLUS;
			case ',': return Rml::Input::KI_OEM_COMMA;
			case '-': return Rml::Input::KI_OEM_MINUS;
			case '.': return Rml::Input::KI_OEM_PERIOD;
			case '/': return Rml::Input::KI_OEM_2;
			case '`': return Rml::Input::KI_OEM_3;
			case '[': return Rml::Input::KI_OEM_4;
			case '\\': return Rml::Input::KI_OEM_5;
			case ']': return Rml::Input::KI_OEM_6;
			case '\'': return Rml::Input::KI_OEM_7;
			case Window::KeyBackspace: return Rml::Input::KI_BACK;
			case Window::KeyTab: return Rml::Input::KI_TAB;
			case Window::KeyReturn: return Rml::Input::KI_RETURN;
			case Window::KeyEsc: return Rml::Input::KI_ESCAPE;
			case Window::KeyPrior: return Rml::Input::KI_PRIOR;
			case Window::KeyNext: return Rml::Input::KI_NEXT;
			case Window::KeyEnd: return Rml::Input::KI_END;
			case Window::KeyHome: return Rml::Input::KI_HOME;
			case Window::KeyLeft: return Rml::Input::KI_LEFT;
			case Window::KeyUp: return Rml::Input::KI_UP;
			case Window::KeyRight: return Rml::Input::KI_RIGHT;
			case Window::KeyDown: return Rml::Input::KI_DOWN;
			case Window::KeyInsert: return Rml::Input::KI_INSERT;
			case Window::KeyDelete: return Rml::Input::KI_DELETE;
			case Window::KeyF1: return Rml::Input::KI_F1;
			case Window::KeyF2: return Rml::Input::KI_F2;
			case Window::KeyF3: return Rml::Input::KI_F3;
			case Window::KeyF4: return Rml::Input::KI_F4;
			case Window::KeyF5: return Rml::Input::KI_F5;
			case Window::KeyF6: return Rml::Input::KI_F6;
			case Window::KeyF7: return Rml::Input::KI_F7;
			case Window::KeyF8: return Rml::Input::KI_F8;
			case Window::KeyF9: return Rml::Input::KI_F9;
			case Window::KeyF10: return Rml::Input::KI_F10;
			case Window::KeyF11: return Rml::Input::KI_F11;
			case Window::KeyF12: return Rml::Input::KI_F12;
		}
		return Rml::Input::KI_UNKNOWN;
	}
}
