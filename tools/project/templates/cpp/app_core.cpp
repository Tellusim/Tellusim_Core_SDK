// Tellusim Core SDK Application Template

#include <TellusimApp.h>
#include <core/TellusimCore.h>
#include <math/TellusimMath.h>
#include <platform/TellusimPlatforms.h>

/*
 */
using namespace Tellusim;

/*
 */
#define RENDER_TRIANGLE	1

/*
 */
class Application {
		
	public:
		
		// constructor initializing the application with command-line arguments
		Application(int32_t argc, char **argv) : app(argc, argv) {
			
		}
		
		// destructor cleans up resources
		virtual ~Application() {
			
			// finish context
			if(window) window.finish();
		}
		
		// create function responsible for initialization
		virtual bool create() {
			
			// create app
			if(!app.create()) {
				TS_LOG(Error, "Application::create(): can't create App\n");
				return false;
			}
			
			// create window
			if(!create_window()) return false;
			
			// create pipeline
			#if RENDER_TRIANGLE
				if(!create_pipeline()) return false;
			#endif
			
			// additional initialization code can go here
			
			return true;
		}
		
		// update function for logic updates
		virtual bool update() {
			
			// your update logic here
			
			return true;
		}
		
		// render function to handle the drawing commands
		virtual bool render(Command &command) {
			
			// render pipeline
			#if RENDER_TRIANGLE
				command.setPipeline(pipeline);
				float32_t angle = (float32_t)Time::seconds() * 64.0f;
				float32_t iaspect = (float32_t)window.getHeight() / window.getWidth();
				command.setUniform(0, Matrix4x4f::rotateZ(angle) * Matrix4x4f::scale(iaspect, 1.0f, 1.0f));
				command.drawArrays(3);
			#endif
			
			// your rendering code here
			
			return true;
		}
		
		// main run loop
		virtual bool run() {
			
			// run application
			if(window) return window.run([this]() {
				return render_window();
			});
			
			return true;
		}
		
	private:
		
		// helper function to create and initialize the Window
		virtual bool create_window() {
			
			// create Window
			window = Window(app.getPlatform(), app.getDevice());
			if(!window || !window.setSize(app.getWidth(), app.getHeight()) ||
				!window.create(String(window.getPlatformName()) + " @NAME@") || !window.setHidden(false)) {
				TS_LOG(Error, "Application::create_window(): can't create Window\n");
				return false;
			}
			
			// set Window callbacks
			window.setKeyboardPressedCallback([this](uint32_t key, uint32_t code) {
				if(key == Window::KeyF4 && window.getKeyboardKey(Window::KeyAlt)) window.stop();
				if(key == Window::KeyEsc) window.stop();
			});
			window.setCloseClickedCallback([&]() { window.stop(); });
			
			// create Device
			device = Device(window);
			if(!device) {
				TS_LOG(Error, "Application::create_window(): can't create Device\n");
				return false;
			}
			
			// create Target
			target = device.createTarget(window);
			if(!target) {
				TS_LOG(Error, "Application::create_window(): can't create Target\n");
				return false;
			}
			
			return true;
		}
		
		// helper function to create the Pipeline
		#if RENDER_TRIANGLE
			virtual bool create_pipeline() {
				
				// create and configure the rendering pipeline
				pipeline = device.createPipeline();
				pipeline.setUniformMask(0, Shader::MaskVertex);
				pipeline.setColorFormat(window.getColorFormat());
				pipeline.setDepthFormat(window.getDepthFormat());
				pipeline.setMultisample(window.getMultisample());
				pipeline.setDepthFunc(Pipeline::DepthFuncAlways);
				
				// vertex Shader that defines a triangle and transforms its position
				if(!pipeline.createShaderGLSL(Shader::TypeVertex, R"(
					layout(std140, binding = 0) uniform Parameters { mat4 transform; };
					layout(location = 0) out vec4 s_color;
					void main() {
						float height = 2.0f * sqrt(5.0f);
						vec2 position = vec2(0.0f, height);
						if(gl_VertexIndex == 0) position = vec2(-sqrt(15.0f), -sqrt(5.0f));
						if(gl_VertexIndex == 1) position = vec2( sqrt(15.0f), -sqrt(5.0f));
						position /= height;
						gl_Position = transform * vec4(position, 0.0f, 1.0f);
						s_color = max(vec4(position + 0.5f, -position.x - position.y, 1.0f), vec4(0.0f));
					}
				)")) return false;
				
				// fragment shader
				if(!pipeline.createShaderGLSL(Shader::TypeFragment, R"(
					layout(location = 0) in vec4 s_color;
					layout(location = 0) out vec4 out_color;
					void main() {
						out_color = s_color;
					}
				)")) return false;
				
				if(!pipeline.create()) return false;
				
				target.setClearColor(Color(0.2f));
				
				return true;
			}
		#endif
		
		// helper function to render the Window
		virtual bool render_window() {
			
			// update events
			Window::update();
			
			// update application
			if(!update()) return false;
			
			// render window
			if(!window.render()) return false;
			
			// window target
			target.begin();
			{
				Command command = device.createCommand(target);
				
				// render application
				if(!render(command)) {
					target.end();
					return false;
				}
			}
			target.end();
			
			// present window
			if(!window.present()) return false;
			
			// check errors
			if(!device.check()) return false;
			
			return true;
		}
		
		App app;				// Application interface
		Window window;			// Window interface
		Device device;			// Device interface
		Target target;			// Target interface
		
		#if RENDER_TRIANGLE
			Pipeline pipeline;	// Pipeline for triangle rendering
		#endif
};

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	// instantiate the application
	Application application(argc, argv);
	
	// create the application
	if(!application.create()) return 1;
	
	// run the application
	if(!application.run()) return 1;
	
	return 0;
}

/*
 */
#if _WIN32
	#include <system/TellusimWindows.h>
	TS_DECLARE_WINDOWS_HIGH_PERFORMANCE
#elif _ANDROID
	#include <system/TellusimAndroid.h>
	TS_DECLARE_ANDROID_NATIVE_ACTIVITY
#endif
