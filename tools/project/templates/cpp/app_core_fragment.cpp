// Tellusim Fragment Application Template

#include <TellusimApp.h>
#include <core/TellusimCore.h>
#include <math/TellusimMath.h>
#include <platform/TellusimPlatforms.h>

/*
 */
using namespace Tellusim;

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
			
			// create resources
			if(!create_resources()) return false;
			
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
			
			// fragment uniform parameters
			struct FragmentParameters {
				float32_t aspect;
				float32_t time;
			};
			
			FragmentParameters parameters;
			parameters.aspect = (float32_t)window.getWidth() / (float32_t)window.getHeight();
			parameters.time = (float32_t)Time::seconds();
			
			// draw fullscreen triangle
			command.setPipeline(pipeline);
			command.setUniform(0, parameters);
			command.drawArrays(3);
			
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
		
		// helper function to create and load resources
		virtual bool create_resources() {
			
			// create pipeline
			pipeline = device.createPipeline();
			pipeline.setUniformMask(0, Shader::MaskFragment);
			pipeline.setColorFormat(window.getColorFormat());
			pipeline.setDepthFormat(window.getDepthFormat());
			if(!pipeline.loadShaderGLSL(Shader::TypeVertex, "main.shader", "VERTEX_SHADER=1")) {
				TS_LOG(Error, "Application::create_resources(): can't load Vertex shader\n");
				return false;
			}
			if(!pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "FRAGMENT_SHADER=1")) {
				TS_LOG(Error, "Application::create_resources(): can't load Fragment shader\n");
				return false;
			}
			if(!pipeline.create()) {
				TS_LOG(Error, "Application::create_resources(): can't create Pipeline\n");
				return false;
			}
			
			// your resource creation code here
			
			return true;
		}
		
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
		
		Pipeline pipeline;		// Pipeline interface
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
