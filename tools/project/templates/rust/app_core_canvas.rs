// Tellusim Canvas Application Template

use tellusim::*;
use std::process::exit;

/*
 */
struct Application {
	
	app: App,				// Application interface
	window: Window,			// Window interface
	device: Device,			// Device interface
	target: Target,			// Target interface
	canvas: Canvas,			// Canvas interface
	ellipses: Vec<CanvasEllipse>,
}

impl Application {
	
	// constructor initializing the application with command-line arguments
	fn new() -> Application {
		Application {
			app: App::new(),
			window: Window::null(),
			device: Device::null(),
			target: Target::null(),
			canvas: Canvas::null(),
			ellipses: Vec::new(),
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
		
		// update canvas elements
		let hheight = self.canvas.height() * 0.5;
		for i in 0..self.ellipses.len() {
			let len = self.ellipses.len() as f32;
			let angle = PI2 * i as f32 / len + time::seconds() as f32;
			let x = self.canvas.width() * (1 + i) as f32 / (len + 1.0);
			let y0 = hheight + (angle * 2.0 - 0.2).cos() * (angle - 0.1).sin() * hheight * 0.9;
			let y1 = hheight + (angle * 2.0 + 0.2).cos() * (angle + 0.1).sin() * hheight * 0.9;
			self.ellipses[i].set_color_with_color(&Color::hsv(angle * RAD2DEG + y0 * 0.5, 1.0, 1.0));
			self.ellipses[i].set_radius((20.0 * 20.0 + (y1 - y0) * (y1 - y0) * 0.25).sqrt());
			self.ellipses[i].set_position0(&Vector3f::new(x, y0, 0.0));
			self.ellipses[i].set_position1(&Vector3f::new(x, y1, 0.0));
		}
		
		// your update logic here
		
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
		
		// gray background
		self.target.set_clear_color_with_color(&Color::new_s(0.1));
		
		// create canvas
		self.canvas = Canvas::new();
		self.canvas.set_viewportf32(1280.0, 720.0);
		
		// create ellipses
		for _i in 0..32 {
			let mut ellipse = CanvasEllipse::new_with_canvas(&mut self.canvas);
			ellipse.set_stroke_style(&StrokeStyle::new_with_width_color(4.0, Color::white()));
			self.ellipses.push(ellipse);
		}
		
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
		
		// create canvas
		if !self.canvas.create(&self.device, &self.target) { return false }
		
		// window target
		self.target.begin();
		{
			let mut command = self.device.create_command_with_target(&mut self.target);
			
			// draw canvas
			self.canvas.draw_with_target(&mut command, &self.target);
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
