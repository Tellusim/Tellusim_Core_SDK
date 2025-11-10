// Tellusim Canvas Application Template

#include <TellusimApp.h>
#include <core/TellusimCore.h>
#include <platform/TellusimPlatforms.h>
#include <interface/TellusimCanvas.h>

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
			
			using Tellusim::sin;
			using Tellusim::cos;
			using Tellusim::sqrt;
			
			// update canvas elements
			float32_t hheight = canvas.getHeight() * 0.5f;
			for(uint32_t i = 0; i < ellipses.size(); i++) {
				float32_t angle = Pi2 * i / ellipses.size() + (float32_t)Time::seconds();
				float32_t x = canvas.getWidth() * (1 + i) / (ellipses.size() + 1);
				float32_t y0 = hheight + cos(angle * 2.0f - 0.2f) * sin(angle - 0.1f) * hheight * 0.9f;
				float32_t y1 = hheight + cos(angle * 2.0f + 0.2f) * sin(angle + 0.1f) * hheight * 0.9f;
				ellipses[i].setColor(Color::hsv(angle * Rad2Deg + y0 * 0.5f, 1.0f, 1.0f));
				ellipses[i].setRadius(sqrt(20.0f * 20.0f + (y1 - y0) * (y1 - y0) * 0.25f));
				ellipses[i].setPosition0(Vector3f(x, y0, 0.0f));
				ellipses[i].setPosition1(Vector3f(x, y1, 0.0f));
			}
			
			// your update logic here
			
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
			
			// gray background
			target.setClearColor(Color(0.1f));
			
			// create canvas
			canvas.setViewport(1280.0f, 720.0f);
			
			// create ellipses
			for(uint32_t i = 0; i < 32; i++) {
				CanvasEllipse ellipse = CanvasEllipse(canvas);
				ellipse.setStrokeStyle(StrokeStyle(4.0f, Color::white));
				ellipses.append(ellipse);
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
			
			// create canvas
			if(!canvas.create(device, target)) return false;
			
			// window target
			target.begin();
			{
				Command command = device.createCommand(target);
				
				// draw canvas
				canvas.draw(command, target);
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
		Canvas canvas;			// Canvas interface
		
		Array<CanvasEllipse> ellipses;
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
