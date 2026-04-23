// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <core/TellusimLog.h>
#include <core/TellusimTime.h>
#include <core/TellusimArray.h>
#include <core/TellusimAsync.h>
#include <core/TellusimString.h>
#include <math/TellusimMath.h>
#include <platform/TellusimPlatforms.h>
#include <graphics/TellusimEncoderBC15.h>
#include <graphics/TellusimEncoderBC67.h>
#include <graphics/TellusimEncoderASTC.h>
#include <format/TellusimParser.h>
#include <format/TellusimImage.h>

/*
 */
#define INDENT_SPACES	48u

/*
 */
using namespace Tellusim;

/*
 */
static Image::Type get_type(const char *name, const String &type) {
	if(type == "2d") return Image::Type2D;
	if(type == "3d") return Image::Type3D;
	if(type == "cube") return Image::TypeCube;
	return Image::TypeUnknown;
}

static Format get_format(const char *name, const char *format) {
	Format ret = findFormatName(format);
	if(ret == FormatUnknown) TS_LOGF(Error, "%s: invalid format \"%s\"\n", name, format);
	return ret;
}

/*
 */
static void print_info(const Image &image, const String &name) {
	String str = name.basename();
	if(!str) str = "null";
	str += ": "; str += image.getDescription(); str += ' ';
	str += String::fromBytes(image.getMemory()); str += '\n';
	str += image.getMetaInfo();
	Log::print(str.get());
}

static void print_verbose(const Image &image, const String &name, const char *desc, uint64_t time) {
	String base = name.basename();
	if(!base) base = "null";
	String info = image.getDescription();
	String base_space = String(INDENT_SPACES - min(base.size(), INDENT_SPACES), ' ');
	String info_space = String(INDENT_SPACES - min(info.size(), INDENT_SPACES), ' ');
	TS_LOGF(Verbose, "%s%s (%s):%s%s %s\n", base_space.get(), base.get(), info.get(), info_space.get(), desc, String::fromTime(time).get());
}

static void print_infos(const Array<Image> &images, const Array<String> &names) {
	TS_ASSERT(images.size() == names.size());
	for(uint32_t i = 0; i < images.size(); i++) {
		print_info(images[i], names[i]);
	}
}

/*
 */
static bool print_compare(const String name_0, const Image &image_0, const String &name_1, const Image &image_1, float64_t threshold) {
	
	// create samplers
	ImageSampler sampler_0, sampler_1;
	if(image_0.getSize() != image_1.getSize()) return false;
	if(image_0.getFormat() != image_1.getFormat()) return false;
	if(!sampler_0.create(image_0, image_0.getSlice()) || !sampler_1.create(image_1)) return false;
	
	// mean squared error
	Vector4d mse = Vector4d(0.0);
	if(image_0.isSignedFormat()) {
		for(uint32_t y = 0; y < image_0.getHeight(); y++) {
			for(uint32_t x = 0; x < image_0.getWidth(); x++) {
				Vector4f d = Vector4f(Vector4i(sampler_0.get2D(x, y).iv)) - Vector4f(Vector4i(sampler_1.get2D(x, y).iv));
				mse += Vector4d(d * d);
			}
		}
	} else if(image_0.isUnsignedFormat()) {
		for(uint32_t y = 0; y < image_0.getHeight(); y++) {
			for(uint32_t x = 0; x < image_0.getWidth(); x++) {
				Vector4f d = Vector4f(Vector4u(sampler_0.get2D(x, y).uv)) - Vector4f(Vector4u(sampler_1.get2D(x, y).uv));
				mse += Vector4d(d * d);
			}
		}
	} else if(image_0.isf16Format()) {
		for(uint32_t y = 0; y < image_0.getHeight(); y++) {
			for(uint32_t x = 0; x < image_0.getWidth(); x++) {
				ImageColor c0 = sampler_0.get2D(x, y);
				ImageColor c1 = sampler_1.get2D(x, y);
				Vector4f v0 = Vector4f((float32_t)c0.h.r, (float32_t)c0.h.g, (float32_t)c0.h.b, (float32_t)c0.h.a);
				Vector4f v1 = Vector4f((float32_t)c1.h.r, (float32_t)c1.h.g, (float32_t)c1.h.b, (float32_t)c1.h.a);
				Vector4f d = (v0 - v1) * 255.0f;
				mse += Vector4d(d * d);
			}
		}
	} else {
		return false;
	}
	
	// rmse and psnr
	float64_t max = 1.0, rmse = 0.0;
	if(image_0.isf16Format()) max = 255.0f;
	else if(image_0.is8BitFormat()) max = (float64_t)Maxu8;
	else if(image_0.is16BitFormat()) max = (float64_t)Maxu16;
	else if(image_0.is32BitFormat()) max = (float64_t)Maxu32;
	for(uint32_t i = 0; i < image_0.getComponents(); i++) rmse += mse.v[i];
	rmse = Tellusim::sqrt(rmse / (float64_t)(image_0.getWidth() * image_0.getHeight() * image_0.getComponents()));
	float64_t psnr = 20.0f * Tellusim::log10(max / (rmse + Minf32));
	
	// print result
	String base_0 = name_0.basename();
	String base_1 = name_1.basename();
	if(!base_0) base_0 = "null";
	if(!base_1) base_1 = "null";
	if(threshold < rmse) {
		TS_LOGF(Error, "%s VS %s RMSE: %.5f PSNR: %.5f dB\n", base_0.get(), base_1.get(), rmse, psnr);
		return false;
	}
	if(Log::getLevel() == Log::Verbose) {
		String base_space = String(32 - min(base_0.size(), 32u), ' ');
		String info_space = String(32 - min(base_1.size() + 2, 32u), ' ');
		TS_LOGF(Verbose, "%s%s  VS  %s%sRMSE: %.5f PSNR: %.5f dB\n", base_space.get(), base_0.get(), base_1.get(), info_space.get(), rmse, psnr);
	} else {
		Log::printf("%s VS %s RMSE: %.5f PSNR: %.5f dB\n", base_0.get(), base_1.get(), rmse, psnr);
	}
	return true;
}

/*
 */
#define DECLARE_IS(NAME, SHORT) static bool is_ ## NAME(const String &name) { return (name == #NAME || name == #SHORT); }
DECLARE_IS(fast, f)
DECLARE_IS(best, b)
DECLARE_IS(array, a)
DECLARE_IS(panorama, p)
DECLARE_IS(perceptual, p)
DECLARE_IS(normalize, n)
DECLARE_IS(point, p)
DECLARE_IS(linear, l)
DECLARE_IS(cubic, c)
DECLARE_IS(sinc, si)
DECLARE_IS(box, b)
DECLARE_IS(min, min)
DECLARE_IS(max, max)
DECLARE_IS(mip, mip)
DECLARE_IS(gamma, g)
DECLARE_IS(srgb, s)
DECLARE_IS(gpu, gpu)
#undef DECLARE_IS

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	// print help
	if(argc < 2 || String(argv[1]) == "-h") {
		Log::printf("Tellusim Image Processing Tool (build " __DATE__ " https://tellusim.com/)\nUsage: %s file.png <commands> -o file.jpg\n", argv[0]);
		if(ImageStream::getLoadFormats()) Log::printf("Load file formats: %s\n", ImageStream::getLoadFormats().replace(".", ", ").remove(0, 2).get());
		if(ImageStream::getSaveFormats()) Log::printf("Save file formats: %s\n", ImageStream::getSaveFormats().replace(".", ", ").remove(0, 2).get());
		Log::print("  -verbose                   Verbose output\n");
		Log::print("  -info                      Get images info\n");
		Log::print("  -list                      Print image formats\n");
		Log::print("  -end                       End batch processing\n");
		Log::print("  -remove                    Remove last image\n");
		Log::print("  -clone                     Clone last image\n");
		Log::print("  -push                      Push last image\n");
		Log::print("  -pop                       Pop last image\n");
		Log::print("  -o <filename> (options)    Output image (fast, best)\n");
		Log::print("  -e <extension> (options)   Output extension (fast, best)\n");
		Log::print("  -p <postfix>               Output postfix\n");
		Log::print("  -prefix <prefix>           Output prefix\n");
		Log::print("  -quality <quality>         Output quality\n");
		Log::print("  -swap <c0> <c1>            Swap components\n");
		Log::print("  -copy <c0> <c1>            Copy component\n");
		Log::print("  -flipx                     Flip horizontally\n");
		Log::print("  -flipy                     Flip vertically\n");
		Log::print("  -2d (options)              Convert to 2D type (panorama)\n");
		Log::print("  -3d                        Convert to 3D type\n");
		Log::print("  -cube                      Convert to Cube type\n");
		Log::print("  -array                     Convert to array\n");
		Log::print("  -combine                   Combine components\n");
		Log::print("  -decombine                 Decombine components\n");
		Log::print("  -grid <w>                  Convert to grid\n");
		Log::print("  -format <fmt> (options)    Convert to format (fast, best, perceptual, normalize, gamma, srgb, gpu)\n");
		Log::print("  -face <face>               Get image face\n");
		Log::print("  -layer <layer>             Get image layer\n");
		Log::print("  -mipmap <mipmap>           Get image mipmap\n");
		Log::print("  -component <index>         Get image component\n");
		Log::print("  -region <x> <y> <w> <h>    Get image region\n");
		Log::print("  -resize <w> <h> (options)  Resize image (point, linear, *cubic*, *sinc*, box, max, min, gamma)\n");
		Log::print("  -scale <factor> (options)  Scale image (point, linear, *cubic*, *sinc*, box, max, min, gamma)\n");
		Log::print("  -rotate <angle>            Rotate image in degrees\n");
		Log::print("  -mipmaps (options)         Create mipmaps (point, box, max, min, *mip*, gamma)\n");
		Log::print("  -insert <x> <y>            Insert last image data at offset\n");
		Log::print("  -clear <r> <g> <b> <a>     Clear image color\n");
		Log::print("  -mul <r> <g> <b> <a>       Multiply image color\n");
		Log::print("  -add <r> <g> <b> <a>       Add image color\n");
		Log::print("  -create (type) <fmt> <...> Create 2D or type image\n");
		Log::print("  -compare (threshold)       Compare images\n");
		Log::print("  -meta                      Print meta info\n");
		return 0;
	}
	
	// async
	Async async;
	if(!async.init()) {
		TS_LOGF(Error, "%s: can't init Async\n", argv[0]);
		return 1;
	}
	
	// batch images
	String prefix;
	String postfix;
	Array<Image> images;
	Array<String> names;
	
	// stack images
	Array<Image> stack_images;
	Array<String> stack_names;
	
	// image info
	bool info = false;
	
	// image quality
	uint32_t quality = 95;
	
	// message log level
	Log::setLevel(Log::Message);
	
	// run command for all images
	#define DECLARE_COMMAND(COMMAND, INFO) { \
		for(uint32_t index = 0; index < images.size(); index++) {\
			uint64_t begin = Time::current(); \
			Image &image = images[index]; \
			COMMAND; \
			if(!image.isLoaded()) return 1; \
			print_verbose(image, names[index], INFO, Time::current() - begin); \
		} \
	}
	
	// command line arguments
	for(int32_t i = 1; i < argc; i++) {
		const char *s = argv[i];
		
		// commands
		if(s[0] == '-') {
			while(*s == '-') s++;
			String command = String(s);
			
			// verbose output
			if(command == "verbose" || command == "v") {
				Log::setLevel(Log::Verbose);
			}
			
			// info output
			else if((command == "info" || command == "i") && !images) {
				Log::setLevel(Log::Verbose);
				info = true;
			}
			
			// image formats
			else if(command == "list") {
				String formats;
				for(uint32_t i = FormatUnknown + 1; i < NumFormats; i++) {
					if(formats) formats += ", ";
					formats += String(getFormatName((Format)i)).lower();
				}
				Log::printf("%s\n", formats.get());
			}
			
			// end images processing
			else if(command == "end") {
				TS_LOG(Verbose, "\n");
				for(uint32_t j = 0; j < images.size(); j++) {
					images[j].clear();
				}
				prefix.clear();
				postfix.clear();
				images.clear();
				names.clear();
				info = false;
			}
			
			// pop last image
			else if(command == "pop") {
				if(!stack_images) {
					TS_LOGF(Error, "%s: stack underflow\n", argv[0]);
					return 1;
				}
				images.append(stack_images.back());
				names.append(stack_names.back());
				stack_images.removeBack();
				stack_names.removeBack();
				print_verbose(images.back(), names.back(), "pop image", 0);
			}
			
			// create image
			else if(command == "create" && i + 2 < argc) {
				Image::Type type = get_type(argv[0], String(argv[i + 1]));
				if(type != Image::TypeUnknown) i += 1;
				else type = Image::Type2D;
				Format format = get_format(argv[0], argv[++i]);
				if(format == FormatUnknown) return 1;
				Size size = Size(1, 1);
				if(i + 1 < argc) size.width = String::tou32(argv[++i]);
				if(type == Image::TypeCube) size.height = size.width;
				else if(i + 1 < argc) size.height = String::tou32(argv[++i]);
				if(type == Image::Type3D && i + 1 < argc) size.depth = String::tou32(argv[++i]);
				uint64_t begin = Time::current();
				names.append(String::null);
				if(!images.append().create(type, format, size)) return 1;
				print_verbose(images.back(), names.back(), "create", Time::current() - begin);
			}
			
			// process image
			else {
				
				// check image
				if(!images || !images[0].isLoaded()) {
					TS_LOGF(Error, "%s: no images are loaded for \"%s\" command\n", argv[0], command.get());
					return 1;
				}
				
				// remove last image
				else if(command == "remove") {
					print_verbose(images.back(), names.back(), "remove image", 0);
					images.back().clear();
					images.removeBack();
					names.removeBack();
				}
				
				// clone last image
				else if(command == "clone") {
					uint64_t begin = Time::current();
					images.append(images.back());
					names.append(names.back());
					print_verbose(images.back(), names.back(), "clone image", Time::current() - begin);
				}
				
				// push last image
				else if(command == "push") {
					print_verbose(images.back(), names.back(), "push image", 0);
					stack_images.append(images.back());
					stack_names.append(names.back());
					images.removeBack();
					names.removeBack();
				}
				
				// print info
				else if(command == "info" || command == "i") {
					print_infos(images, names);
				}
				
				// output file
				else if(command == "o" && i + 1 < argc) {
					const char *name = argv[i + 1];
					Image::Flags flags = Image::FlagNone;
					while(i + 2 < argc) {
						command = argv[i + 2];
						if(is_fast(command)) { flags |= Image::FlagFast; i += 1; }
						else if(is_best(command)) { flags |= Image::FlagBest; i += 1; }
						else break;
					}
					uint64_t begin = Time::current();
					if(!images.back().save(name, flags, quality)) {
						TS_LOGF(Error, "%s: can't save \"%s\" file\n", argv[0], name);
						return 1;
					}
					print_verbose(images.back(), String(name), "save image", Time::current() - begin);
					i += 1;
				}
				// output extension
				else if(command == "e" && i + 1 < argc) {
					const char *extension = argv[i + 1];
					Image::Flags flags = Image::FlagNone;
					while(i + 2 < argc) {
						command = argv[i + 2];
						if(is_fast(command)) { flags |= Image::FlagFast; i += 1; }
						else if(is_best(command)) { flags |= Image::FlagBest; i += 1; }
						else break;
					}
					for(uint32_t j = 0; j < images.size(); j++) {
						if(!names[j]) {
							TS_LOGF(Error, "%s: unnamed image is loaded\n", argv[0]);
							return 1;
						}
						uint64_t begin = Time::current();
						String name = prefix + names[j].extension(extension);
						if(postfix) name = name.extension(nullptr) + postfix.extension(name.extension().get());
						if(!images[j].save(name.get(), flags, quality)) {
							TS_LOGF(Error, "%s: can't save \"%s\" file\n", argv[0], name.get());
							return 1;
						}
						print_verbose(images[j], name, "save image", Time::current() - begin);
					}
					i += 1;
				}
				// output postfix
				else if((command == "postfix" || command == "p") && i + 1 < argc) {
					postfix = argv[i + 1];
					i += 1;
				}
				// output prefix
				else if((command == "prefix" || command == "pre") && i + 1 < argc) {
					prefix = argv[i + 1];
					i += 1;
				}
				// output quality
				else if((command == "quality" || command == "q") && i + 1 < argc) {
					quality = String::tou32(argv[i + 1]);
					i += 1;
				}
				
				// swap components
				else if(command == "swap" && i + 2 < argc) {
					uint32_t c0 = String::tou32(argv[i + 1]);
					uint32_t c1 = String::tou32(argv[i + 2]);
					String desc = String::format("swap %u %u components", c0, c1);
					DECLARE_COMMAND(image.swap(c0, c1), desc.get())
					i += 2;
				}
				// copy component
				else if(command == "copy" && i + 2 < argc) {
					uint32_t c0 = String::tou32(argv[i + 1]);
					uint32_t c1 = String::tou32(argv[i + 2]);
					String desc = String::format("copy %u %u components", c0, c1);
					DECLARE_COMMAND(image.copy(image, c0, c1), desc.get())
					i += 2;
				}
				
				// flip image
				else if(command == "flipx" || command == "fx") {
					DECLARE_COMMAND(image.flipX(), "flip horizontally")
				}
				// flip vertically
				else if(command == "flipy" || command == "fy") {
					DECLARE_COMMAND(image.flipY(), "flip vertically")
				}
				
				// convert to type
				else if(command == "2d") {
					Image::Flags flags = Image::FlagNone;
					while(i + 1 < argc) {
						command = argv[i + 1];
						if(is_array(command)) { flags |= Image::FlagArray; i += 1; }
						else if(is_panorama(command)) { flags |= Image::FlagPanorama; i += 1; }
						else break;
					}
					DECLARE_COMMAND(image = image.toType(Image::Type2D, flags, &async), "convert to 2D type")
				}
				else if(command == "3d") {
					DECLARE_COMMAND(image = image.toType(Image::Type3D, &async), "convert to 3D type");
				}
				else if(command == "cube") {
					DECLARE_COMMAND(image = image.toType(Image::TypeCube, &async), "convert to Cube type")
				}
				else if(command == "array") {
					bool is_array = true;
					is_array &= !images[0].is3DType();
					is_array &= !images[0].hasLayers();
					for(uint32_t j = 1; j < images.size(); j++) {
						is_array &= (images[j].getType() == images[0].getType());
						is_array &= (images[j].getSize() == images[0].getSize());
						is_array &= (images[j].getLayers() == images[0].getLayers());
						is_array &= (images[j].getMipmaps() == images[0].getMipmaps());
					}
					if(images.size() < 2 || !is_array) {
						TS_LOGF(Error, "%s: can't create array from input images\n", argv[0]);
						print_infos(images, names);
						return 1;
					}
					uint64_t begin = Time::current();
					Image array(images[0].getType(), images[0].getFormat(), images[0].getSize(), images.size(), (images[0].hasMipmaps()) ? Image::FlagMipmaps : Image::FlagNone);
					for(uint32_t j = 0; j < images.size(); j++) {
						if(!array.copy(images[j], Layer(j), images[j].getSlice())) {
							TS_LOGF(Error, "%s: can't create array from input images\n", argv[0]);
							print_infos(images, names);
							return 1;
						}
					}
					images.clear();
					names.clear();
					images.append(array);
					names.append(String::null);
					print_verbose(images[0], names[0], "create array", Time::current() - begin);
				}
				else if(command == "combine") {
					bool is_combine = true;
					uint32_t components = 0;
					is_combine &= images[0].isPlainFormat();
					components += images[0].getComponents();
					for(uint32_t j = 1; j < images.size(); j++) {
						is_combine &= (images[j].getType() == images[0].getType());
						is_combine &= (images[j].getSize() == images[0].getSize());
						is_combine &= (images[j].getLayers() == images[0].getLayers());
						is_combine &= (images[j].getMipmaps() == images[0].getMipmaps());
						components += images[j].getComponents();
					}
					if(images.size() < 2 || !is_combine || components > 4) {
						TS_LOGF(Error, "%s: can't create combined image from input images\n", argv[0]);
						print_infos(images, names);
						return 1;
					}
					uint64_t begin = Time::current();
					Format format = toFormatComponents(images[0].getFormat(), components);
					Image combine(images[0].getType(), format, images[0].getSize(), images[0].getLayers(), (images[0].hasMipmaps()) ? Image::FlagMipmaps : Image::FlagNone);
					components = 0;
					for(uint32_t j = 0; j < images.size(); j++) {
						for(uint32_t k = 0; k < images[j].getComponents(); k++) {
							if(!combine.copy(images[j], components++, k)) {
								print_infos(images, names);
								return 1;
							}
						}
					}
					images.clear();
					names.clear();
					images.append(combine);
					names.append(String::null);
					print_verbose(images[0], names[0], "create combined image", Time::current() - begin);
				}
				else if(command == "decombine") {
					Array<Image> components;
					uint64_t begin = Time::current();
					for(uint32_t j = 0; j < images.size(); j++) {
						Format format = toFormatComponents(images[j].getFormat(), 1);
						for(uint32_t k = 0; k < images[j].getComponents(); k++) {
							Image component(images[j].getType(), format, images[j].getSize(), images[j].getLayers(), (images[j].hasMipmaps()) ? Image::FlagMipmaps : Image::FlagNone);
							if(!component.copy(images[j], 0, k)) {
								print_infos(images, names);
								return 1;
							}
							components.append(component);
						}
					}
					images.clear();
					names.clear();
					images.append(components);
					names.resize(components.size(), String::null);
					print_verbose(images[0], names[0], "create decombined images", Time::current() - begin);
				}
				else if(command == "grid" && i + 1 < argc) {
					Image grid;
					bool is_grid = true;
					is_grid &= images[0].is2DType();
					uint64_t begin = Time::current();
					uint32_t width = max(String::tou32(argv[i + 1]), 1u);
					if(images.size() == 1 && images[0].hasLayers()) {
						if(images[0].getLayers() < width || !is_grid) {
							TS_LOGF(Error, "%s: can't create grid from input image\n", argv[0]);
							print_infos(images, names);
							return 1;
						}
						grid = Image(images[0].getType(), images[0].getFormat(), images[0].getSize() * Size(width, udiv(images[0].getLayers(), width)));
						for(uint32_t j = 0; j < images[0].getLayers(); j++) {
							if(!grid.copy(images[0].getSlice(Layer(j)), Origin(images[0].getWidth() * (j % width), images[0].getHeight() * (j / width)))) {
								TS_LOGF(Error, "%s: can't create grid from input images\n", argv[0]);
								print_infos(images, names);
								return 1;
							}
						}
					} else {
						is_grid &= !images[0].hasLayers();
						for(uint32_t j = 1; j < images.size(); j++) {
							is_grid &= (images[j].getType() == images[0].getType());
							is_grid &= (images[j].getSize() == images[0].getSize());
							is_grid &= (images[j].getLayers() == images[0].getLayers());
							is_grid &= (images[j].getMipmaps() == images[0].getMipmaps());
						}
						if(images.size() < width || !is_grid) {
							TS_LOGF(Error, "%s: can't create grid from input images\n", argv[0]);
							print_infos(images, names);
							return 1;
						}
						grid = Image(images[0].getType(), images[0].getFormat(), images[0].getSize() * Size(width, udiv(images.size(), width)));
						for(uint32_t j = 0; j < images.size(); j++) {
							if(!grid.copy(images[j], Origin(images[0].getWidth() * (j % width), images[0].getHeight() * (j / width)))) {
								TS_LOGF(Error, "%s: can't create grid from input images\n", argv[0]);
								print_infos(images, names);
								return 1;
							}
						}
					}
					images.clear();
					names.clear();
					images.append(grid);
					names.append(String::null);
					print_verbose(images[0], names[0], "create grid ", Time::current() - begin);
					i += 1;
				}
				
				// convert to format
				else if((command == "format" || command == "f") && i + 1 < argc) {
					Format format = get_format(argv[0], argv[i + 1]);
					Image::Flags flags = Image::FlagNone;
					bool gpu_encoder = false;
					while(i + 2 < argc) {
						command = argv[i + 2];
						if(is_fast(command)) { flags |= Image::FlagFast; i += 1; }
						else if(is_best(command)) { flags |= Image::FlagBest; i += 1; }
						else if(is_perceptual(command)) { flags |= Image::FlagPerceptual; i += 1; }
						else if(is_normalize(command)) { flags |= Image::FlagNormalize; i += 1; }
						else if(is_gamma(command)) { flags |= Image::FlagGamma; i += 1; }
						else if(is_srgb(command)) { flags |= Image::FlagSRGB; i += 1; }
						else if(is_gpu(command)) { gpu_encoder = true; i += 1; }
						else break;
					}
					if(gpu_encoder) {
						Format dest_format = FormatRGBAu32;
						EncoderBC15::Mode bc15_mode = EncoderBC15::NumModes;
						EncoderBC67::Mode bc67_mode = EncoderBC67::NumModes;
						EncoderASTC::Mode astc_mode = EncoderASTC::NumModes;
						if(format == FormatBC1RGBu8n) { bc15_mode = EncoderBC15::ModeBC1RGBu8n; dest_format = FormatRGBAu16; }
						else if(format == FormatBC2RGBAu8n) { bc15_mode = EncoderBC15::ModeBC2RGBAu8n; dest_format = FormatRGBAu32; }
						else if(format == FormatBC3RGBAu8n) { bc15_mode = EncoderBC15::ModeBC3RGBAu8n; dest_format = FormatRGBAu32; }
						else if(format == FormatBC4Ru8n) { bc15_mode = EncoderBC15::ModeBC4Ru8n; dest_format = FormatRGBAu16; }
						else if(format == FormatBC5RGu8n) { bc15_mode = EncoderBC15::ModeBC5RGu8n; dest_format = FormatRGBAu32; }
						else if(format == FormatBC6RGBf16s) { bc67_mode = EncoderBC67::ModeBC6RGBf16s; dest_format = FormatRGBAu32; }
						else if(format == FormatBC6RGBf16u) { bc67_mode = EncoderBC67::ModeBC6RGBf16u; dest_format = FormatRGBAu32; }
						else if(format == FormatBC7RGBAu8n) { bc67_mode = EncoderBC67::ModeBC7RGBAu8n; dest_format = FormatRGBAu32; }
						else if(format == FormatASTC44RGBAu8n) { astc_mode = EncoderASTC::ModeASTC44RGBAu8n; dest_format = FormatRGBAu32; }
						else if(format == FormatASTC54RGBAu8n) { astc_mode = EncoderASTC::ModeASTC54RGBAu8n; dest_format = FormatRGBAu32; }
						else if(format == FormatASTC55RGBAu8n) { astc_mode = EncoderASTC::ModeASTC55RGBAu8n; dest_format = FormatRGBAu32; }
						else {
							TS_LOGF(Error, "%s: unknown format %s\n", argv[0], getFormatName(format));
							return 1;
						}
						Context context(PlatformAny);
						if(!context || !context.create()) {
							TS_LOGF(Error, "%s: can't create context\n", argv[0]);
							return 1;
						}
						Device device(context);
						if(!device) {
							TS_LOGF(Error, "%s: can't create device\n", argv[0]);
							return 1;
						}
						EncoderBC15 bc15_encoder;
						EncoderBC67 bc67_encoder;
						EncoderASTC astc_encoder;
						if((bc15_mode != EncoderBC15::NumModes && !bc15_encoder.create(device, bc15_mode)) ||
							(bc67_mode != EncoderBC67::NumModes && !bc67_encoder.create(device, bc67_mode)) ||
							(astc_mode != EncoderASTC::NumModes && !astc_encoder.create(device, astc_mode))) {
							TS_LOGF(Error, "%s: can't create encoder\n", argv[0]);
							return 1;
						}
						Array<Image> dest_images(images.size());
						Array<Texture> src_textures(images.size());
						Array<Texture> dest_textures(images.size());
						uint32_t block_width = getFormatBlockWidth(format);
						uint32_t block_height = getFormatBlockHeight(format);
						{
							Compute compute = device.createCompute();
							DECLARE_COMMAND(
								Image::Flags image_flags = Image::FlagNoClear;
								Texture::Flags texture_flags = Texture::FlagNone;
								if(image.hasMipmaps()) {
									image_flags |= Image::FlagMipmaps;
									texture_flags |= Texture::FlagMipmaps;
								}
								Size size = Size(udiv(image.getWidth(), block_width), udiv(image.getHeight(), block_height), image.getDepth());
								for(uint32_t m = 0; m < image.getMipmaps(); m++) {
									if(image.getWidth(m) < block_width) continue;
									if(image.getHeight(m) < block_height) continue;
									uint32_t width = udiv(image.getWidth(m), block_width);
									uint32_t height = udiv(image.getHeight(m), block_height);
									while((size.width >> m) < width) size.width++;
									while((size.height >> m) < height) size.height++;
								}
								dest_images[index] = Image(image.getType(), dest_format, size, image.getLayers(), image_flags);
								src_textures[index] = device.createTexture(image, texture_flags);
								if(!src_textures[index]) {
									TS_LOGF(Error, "%s: can't create src texture from %s image\n", argv[0], image.getDescription().get());
									return 1;
								}
								dest_textures[index] = device.createTexture(dest_images[index], Texture::FlagSurface | Texture::FlagSource | texture_flags);
								if(!dest_textures[index]) {
									TS_LOGF(Error, "%s: can't create dest texture from %s image\n", argv[0], dest_images[index].getDescription().get());
									return 1;
								}
								Slice slice = src_textures[index].getSlice();
								slice.mipmaps = min(slice.mipmaps, dest_textures[index].getMipmaps());
								if((bc15_mode != EncoderBC15::NumModes && !bc15_encoder.dispatch(compute, bc15_mode, dest_textures[index], src_textures[index], slice)) ||
									(bc67_mode != EncoderBC67::NumModes && !bc67_encoder.dispatch(compute, bc67_mode, dest_textures[index], src_textures[index], slice, image.getComponents())) ||
									(astc_mode != EncoderASTC::NumModes && !astc_encoder.dispatch(compute, astc_mode, dest_textures[index], src_textures[index], slice, image.getComponents()))) {
									TS_LOGF(Error, "%s: can't dispatch encoder\n", argv[0]);
									return 1;
								}
							, "encode image")
						}
						context.finish();
						DECLARE_COMMAND(
							uint32_t block_size = getFormatBlockSize(format);
							uint32_t block_width = getFormatBlockWidth(format);
							uint32_t block_height = getFormatBlockHeight(format);
							if(!device.getTexture(dest_textures[index], dest_images[index])) {
								TS_LOGF(Error, "%s: can't get %s texture\n", argv[0], dest_textures[index].getDescription().get());
								return 1;
							}
							Image::Flags image_flags = Image::FlagNoClear;
							if(image.hasMipmaps()) image_flags |= Image::FlagMipmaps;
							image = Image(image.getType(), format, image.getSize(), image.getLayers(), image_flags);
							for(uint32_t mipmap = 0; mipmap < image.getMipmaps(); mipmap++) {
								uint32_t width = udiv(image.getWidth(mipmap), block_width);
								uint32_t height = udiv(image.getHeight(mipmap), block_height);
								uint32_t dest_mipmap = min(mipmap, dest_images[index].getMipmaps() - 1);
								const uint8_t *dest_data = dest_images[index].getData(Mipmap(dest_mipmap));
								uint32_t dest_width = dest_images[index].getWidth(dest_mipmap);
								uint8_t *data = image.getData(Mipmap(mipmap));
								for(uint32_t y = 0; y < height; y++) {
									memcpy(data, dest_data, block_size * width);
									dest_data += block_size * dest_width;
									data += block_size * width;
								}
							}
							, "copy image")
						context.finish();
					} else {
						DECLARE_COMMAND(if(image.getFormat() != format) image = image.toFormat(format, flags, &async), "convert to format")
					}
					i += 1;
				}
				
				// get image face
				else if(command == "face" && i + 1 < argc) {
					uint32_t face = String::tou32(argv[i + 1]);
					String desc = String::format("get %u face", face);
					DECLARE_COMMAND(image = image.getSlice(image.getSlice().setFace(face)), desc.get())
					i += 1;
				}
				// get image layer
				else if(command == "layer" && i + 1 < argc) {
					uint32_t layer = String::tou32(argv[i + 1]);
					String desc = String::format("get %u layer", layer);
					DECLARE_COMMAND(image = image.getSlice(image.getSlice().setLayer(layer)), desc.get())
					i += 1;
				}
				// get image mipmap
				else if(command == "mipmap" && i + 1 < argc) {
					uint32_t mipmap = String::tou32(argv[i + 1]);
					String desc = String::format("get %u mipmap", mipmap);
					DECLARE_COMMAND(image = image.getSlice(image.getSlice().setMipmap(mipmap)), desc.get())
					i += 1;
				}
				// get image component
				else if(command == "component" && i + 1 < argc) {
					uint32_t component = String::tou32(argv[i + 1]);
					String desc = String::format("get %u component", component);
					DECLARE_COMMAND(image = image.getComponent(component), desc.get())
					i += 1;
				}
				// get image region
				else if(command == "region" && i + 4 < argc) {
					uint32_t x = String::tou32(argv[i + 1]);
					uint32_t y = String::tou32(argv[i + 2]);
					uint32_t width = String::tou32(argv[i + 3]);
					uint32_t height = String::tou32(argv[i + 4]);
					String desc = String::format("get %ux%u %ux%u region", x, y, width, height);
					DECLARE_COMMAND(image = image.getRegion(Region(x, y, width, height)), desc.get())
					i += 4;
				}
				// resize image
				else if((command == "resize" || command == "r") && i + 2 < argc) {
					Image::Flags flags = Image::FlagNone;
					Image::Filter min = Image::FilterSinc;
					Image::Filter mag = Image::FilterCubic;
					uint32_t width = String::tou32(argv[i + 1]);
					uint32_t height = String::tou32(argv[i + 2]);
					if((width == 0 && height == 0) || (size_t)width * height > Maxu32) {
						TS_LOGF(Error, "%s: invalid size %u %u\n", argv[0], width, height);
						return 1;
					}
					while(i + 3 < argc) {
						command = argv[i + 3];
						if(is_point(command)) { min = mag = Image::FilterPoint; i += 1; }
						else if(is_linear(command)) { mag = Image::FilterLinear; i += 1; }
						else if(is_cubic(command)) { mag = Image::FilterCubic; i += 1; }
						else if(is_sinc(command)) { min = Image::FilterSinc; i += 1; }
						else if(is_box(command)) { min = Image::FilterBox; i += 1; }
						else if(is_max(command)) { min = Image::FilterMax; i += 1; }
						else if(is_min(command)) { min = Image::FilterMin; i += 1; }
						else if(is_gamma(command)) { flags = Image::FlagGamma; i += 1; }
						else break;
					}
					String desc = String::format("resize to %ux%u%s", width, height, (flags & Image::FlagGamma) ? " gamma" : "");
					DECLARE_COMMAND(if(image.getSize() != Size(width, height)) image = image.getResized(Size(width, height), min, mag, flags, &async), desc.get())
					i += 2;
				}
				// scale image
				else if((command == "scale" || command == "s") && i + 1 < argc) {
					Image::Flags flags = Image::FlagNone;
					Image::Filter min = Image::FilterSinc;
					Image::Filter mag = Image::FilterCubic;
					float32_t scale = max(String::tof32(argv[i + 1]), 1e-3f);
					if(scale < 1e-6f || scale > 128.0f) {
						TS_LOGF(Error, "%s: invalid scale %f\n", argv[0], scale);
						return 1;
					}
					while(i + 2 < argc) {
						command = argv[i + 2];
						if(is_point(command)) { min = mag = Image::FilterPoint; i += 1; }
						else if(is_linear(command)) { mag = Image::FilterLinear; i += 1; }
						else if(is_cubic(command)) { mag = Image::FilterCubic; i += 1; }
						else if(is_sinc(command)) { min = Image::FilterSinc; i += 1; }
						else if(is_box(command)) { min = Image::FilterBox; i += 1; }
						else if(is_max(command)) { min = Image::FilterMax; i += 1; }
						else if(is_min(command)) { min = Image::FilterMin; i += 1; }
						else if(is_gamma(command)) { flags = Image::FlagGamma; i += 1; }
						else break;
					}
					String desc = String::format("scale by %.3g%s", scale, (flags & Image::FlagGamma) ? " gamma" : "");
					DECLARE_COMMAND(image = image.getResized(Size(max((uint32_t)(image.getWidth() * scale), 1u), max((uint32_t)(image.getHeight() * scale), 1u), max((uint32_t)(image.getDepth() * scale), 1u)), min, mag, flags, &async), desc.get())
					i += 1;
				}
				// rotate image
				else if(command == "rotate" && i + 1 < argc) {
					int32_t angle = String::toi32(argv[i + 1]);
					if(angle != (angle / 90) * 90) {
						TS_LOGF(Error, "%s: invalid angle %d\n", argv[0], angle);
						return 1;
					}
					String desc = String::format("rotate by %d degrees", angle);
					DECLARE_COMMAND(image = image.getRotated(angle / 90), desc.get())
					i += 1;
				}
				// create mipmaps
				else if(command == "mipmaps" || command == "m") {
					Image::Flags flags = Image::FlagNone;
					Image::Filter filter = Image::FilterMip;
					while(i + 1 < argc) {
						command = argv[i + 1];
						if(is_point(command)) { filter = Image::FilterPoint; i += 1; }
						else if(is_max(command)) { filter = Image::FilterMax; i += 1; }
						else if(is_min(command)) { filter = Image::FilterMin; i += 1; }
						else if(is_mip(command)) { filter = Image::FilterMip; i += 1; }
						else if(is_box(command)) { filter = Image::FilterBox; i += 1; }
						else if(is_gamma(command)) { flags = Image::FlagGamma; i += 1; }
						else break;
					}
					const char *filter_name = "";
					if(filter == Image::FilterPoint) filter_name = "point";
					else if(filter == Image::FilterBox) filter_name = "box";
					else if(filter == Image::FilterMax) filter_name = "max";
					else if(filter == Image::FilterMin) filter_name = "min";
					else if(filter == Image::FilterMip) filter_name = "mip";
					String desc = String::format("create mipmaps %s%s", filter_name, (flags & Image::FlagGamma) ? " gamma" : "");
					DECLARE_COMMAND(image = image.getMipmapped(filter, flags, &async), desc.get())
				}
				
				// insert image data
				else if(command == "insert" && i + 2 < argc) {
					uint32_t x = String::tou32(argv[i + 1]);
					uint32_t y = String::tou32(argv[i + 2]);
					if(images.size() < 2) {
						TS_LOGF(Error, "%s: no images are loaded for \"%s\" command\n", argv[0], command.get());
						return 1;
					}
					Image &dest = images.back(1);
					const Image &src = images.back();
					uint64_t begin = Time::current();
					if(!dest.copy(src, Origin(x, y), src.getRegion())) {
						TS_LOGF(Error, "%s: can't copy %s image\n", argv[0], dest.getFormatName());
						return 1;
					}
					print_verbose(images.back(), names.back(), "insert image", Time::current() - begin);
					i += 2;
				}
				
				// clear image
				else if(command == "clear" && i + 4 < argc) {
					for(uint32_t j = 0; j < images.size(); j++) {
						ImageColor color;
						for(uint32_t k = 0; k < 4; k++) {
							const char *s = argv[i + k + 1];
							if(images[j].isSignedFormat()) color.iv[k] = String::toi32(s);
							else if(images[j].isUnsignedFormat()) color.uv[k] = String::tou32(s);
							else if(images[j].isf16Format()) color.hv[k] = String::tof32(s);
							else if(images[j].isf32Format()) color.fv[k] = String::tof32(s);
							else TS_LOGF(Warning, "%s: can't clear %s image\n", argv[0], images[j].getFormatName());
						}
						ImageSampler sampler;
						uint64_t begin = Time::current();
						for(uint32_t l = 0; l < images[j].getLayers(); l++) {
							for(uint32_t m = 0; m < images[j].getMipmaps(); m++) {
								if(!sampler.create(images[j], Slice(Layer(l), Mipmap(m))) || !sampler.clear(color)) {
									TS_LOGF(Error, "%s: can't clear %s image\n", argv[0], images[j].getFormatName());
									return 1;
								}
							}
						}
						print_verbose(images[j], names[j], "clear image", Time::current() - begin);
					}
					i += 4;
				}
				
				// multiply and add image
				else if((command == "mul" || command == "add") && i + 4 < argc) {
					Color color;
					color.r = String::tof32(argv[i + 1]);
					color.g = String::tof32(argv[i + 2]);
					color.b = String::tof32(argv[i + 3]);
					color.a = String::tof32(argv[i + 4]);
					for(uint32_t j = 0; j < images.size(); j++) {
						ImageSampler sampler;
						uint64_t begin = Time::current();
						Format format = images[j].getFormat();
						for(uint32_t l = 0; l < images[j].getLayers(); l++) {
							for(uint32_t m = 0; m < images[j].getMipmaps(); m++) {
								if(sampler.create(images[j], Slice(Layer(l), Mipmap(m)))) {
									size_t texels = sampler.getTexels();
									if(command == "mul") {
										for(size_t t = 0; t < texels; t++) {
											Color texel_color = sampler.getTexel(t).get(format);
											sampler.setTexel(t, ImageColor(texel_color * color, format));
										}
									} else if(command == "add") {
										for(size_t t = 0; t < texels; t++) {
											Color texel_color = sampler.getTexel(t).get(format);
											sampler.setTexel(t, ImageColor(texel_color + color, format));
										}
									} else {
										TS_ASSERT(0 && "main(): unknown command");
									}
								} else {
									TS_LOGF(Error, "%s: can't modify %s image\n", argv[0], images[j].getFormatName());
									return 1;
								}
							}
						}
						print_verbose(images[j], names[j], "modify image", Time::current() - begin);
					}
					i += 4;
				}
				
				// compare images
				else if(command == "compare") {
					if(images.size() < 2) {
						TS_LOGF(Error, "%s: no images are loaded for \"%s\" command\n", argv[0], command.get());
						return 1;
					}
					float64_t threshold = Maxf32;
					if(i + 1 < argc && Parser::isNumber(argv[i + 1])) {
						threshold = String::tof64(argv[i + 1]);
						i += 1;
					}
					for(uint32_t j = 1; j < images.size(); j++) {
						Image compare = images[j].toFormat(images[0].getFormat(), &async);
						if(!compare.isLoaded() || !print_compare(names[0], images[0], names[j], compare, threshold)) {
							TS_LOGF(Error, "%s: can't compare %s and %s images\n", argv[0], images[0].getDescription().get(), images[j].getDescription().get());
							return 1;
						}
					}
				}
				
				// image meta info
				else if(command == "meta") {
					for(uint32_t j = 0; j < images.size(); j++) {
						if(images[j].getMetaInfo()) {
							TS_LOGF(Message, "%s:\n", names[j].get());
							TS_LOGF(Message, "%s\n", images[j].getMetaInfo().get());
						}
					}
				}
				
				// unknown command
				else {
					TS_LOGF(Error, "%s: invalid command line option \"%s\"\n", argv[0], argv[i]);
					return 1;
				}
			}
		}
		
		// info image
		else if(info) {
			uint64_t begin = Time::current();
			if(!images.append().info(s, &async)) {
				TS_LOGF(Error, "%s: can't info \"%s\" file\n", argv[0], argv[i]);
				return 1;
			}
			names.append(String(s));
			print_verbose(images.back(), names.back(), "load image", Time::current() - begin);
		}
		// load image
		else {
			uint64_t begin = Time::current();
			if(!images.append().load(s, &async)) {
				TS_LOGF(Error, "%s: can't load \"%s\" file\n", argv[0], argv[i]);
				return 1;
			}
			names.append(String(s));
			print_verbose(images.back(), names.back(), "load image", Time::current() - begin);
		}
	}
	
	return 0;
}
