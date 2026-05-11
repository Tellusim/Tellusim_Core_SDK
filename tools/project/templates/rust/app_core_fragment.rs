// Tellusim Fragment Application Template

use tellusim::*;
use std::process::exit;

/*
 */
struct Application {
	
	app: App,				// Application interface
	window: Window,			// Window interface
	device: Device,			// Device interface
	target: Target,			// Target interface
	
	pipeline: Pipeline,		// Pipeline interface
}

impl Application {
	
	// constructor initializing the application with command-line arguments
	fn new() -> Application {
		Application {
			app: App::new(),
			window: Window::null(),
			device: Device::null(),
			target: Target::null(),
			pipeline: Pipeline::null(),
		}
	}
	
	// create function responsible for initialization
	fn create(&mut self) -> bool {
		
		// create app
		if !self.app.create() {
			ts_log!(Error, "Application::create(): can't create App\n");
			return false
		}
		
		// create window
		if !self.create_window() {
			return false
		}
		
		// create resources
		if !self.create_resources() {
			return false
		}
		
		// additional initialization code can go here
		
		true
	}
	
	// update function for logic updates
	fn update(&mut self) -> bool {
		
		// your update logic here
		
		true
	}
	
	// render function to handle the drawing commands
	fn render(&mut self, command: &mut Command) -> bool {
		
		// fragment uniform parameters
		#[repr(C)]
		#[derive(Default)]
		struct FragmentParameters {
			aspect: f32,
			time: f32,
		}
		let mut parameters = FragmentParameters::default();
		parameters.aspect = self.window.width() as f32 / self.window.height() as f32;
		parameters.time = time::seconds() as f32;
		
		// draw fullscreen triangle
		command.set_pipeline(&mut self.pipeline);
		command.set_uniform(0, &parameters);
		command.draw_arrays(3);
		
		// your rendering code here
		
		true
	}
	
	// main run loop
	fn run(&mut self) -> bool {
		
		// run application
		let mut window = self.window.copy_ptr();
		window.run(|| -> bool {
			self.render_window()
		});
		
		// finish context
		self.window.finish();
		
		true
	}
	
	// helper function to create and initialize the Window
	fn create_window(&mut self) -> bool {
		
		// create Window
		let mut window = Window::new_with_platform_index(self.app.platform(), self.app.device());
		if !window.is_valid_ptr() || !window.set_size(self.app.width(), self.app.height()) ||
			!window.create_with_title(&(window.platform_name() + &" Rust @NAME@")) || !window.set_hidden(false) {
			ts_log!(Error, "Application::create_window(): can't create Window\n");
			return false
		}
		
		// set Window callbacks
		window.set_keyboard_pressed_callback({
			let mut window = window.copy_ptr();
			move |key: u32, _code: u32| {
				if key == WindowKey::F4 && window.keyboard_key(WindowKey::Alt.value()) { window.stop() }
				if key == WindowKey::Esc { window.stop() }
			}
		});
		window.set_close_clicked_callback({
			let mut window = window.copy_ptr();
			move || { window.stop() }
		});
		
		// create Device
		let device = Device::new_with_window(&mut window);
		if !device.is_valid_ptr() {
			ts_log!(Error, "Application::create_window(): can't create Device\n");
			return false
		}
		
		// create Target
		let target = device.create_target_with_window(&mut window);
		if !target.is_valid_ptr() {
			ts_log!(Error, "Application::create_window(): can't create Target\n");
			return false
		}
		
		self.window = window;
		self.device = device;
		self.target = target;
		
		true
	}
	
	// helper function to create and load resources
	fn create_resources(&mut self) -> bool {
		
		// create pipeline
		let mut pipeline = self.device.create_pipeline();
		pipeline.set_uniform_mask(0, ShaderMask::Fragment);
		pipeline.set_color_format(0, self.window.color_format());
		pipeline.set_depth_format(self.window.depth_format());
		if !pipeline.load_shader_glsl(ShaderType::Vertex, "main.shader", "VERTEX_SHADER=1") {
			ts_log!(Error, "Application::create_resources(): can't load Vertex shader\n");
			return false;
		}
		if !pipeline.load_shader_glsl(ShaderType::Fragment, "main.shader", "FRAGMENT_SHADER=1") {
			ts_log!(Error, "Application::create_resources(): can't load Fragment shader\n");
			return false
		}
		if !pipeline.create() {
			ts_log!(Error, "Application::create_resources(): can't create Pipeline\n");
			return false
		}
		
		self.pipeline = pipeline;
		
		// your resource creation code here
		
		true
	}
	
	// helper function to render the Window
	fn render_window(&mut self) -> bool {
		
		// update events
		Window::update();
		
		// update application
		if !self.update() { return false }
		
		// render window
		if !self.window.render() { return false }
		
		// window target
		self.target.begin();
		{
			let mut command = self.device.create_command_with_target(&mut self.target);
			
			// render application
			if !self.render(&mut command) {
				self.target.end();
				return false
			}
		}
		self.target.end();
		
		// present window
		if !self.window.present() { return false }
		
		// check errors
		if !self.device.check() { return false }
		
		true
	}
}

/*
 */
fn main() {
	
	// instantiate the application
	let mut application = Application::new();
	
	// create the application
	if !application.create() { exit(1) }
	
	// run the application
	if !application.run() { exit(1) }
}
