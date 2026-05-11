// Tellusim Engine SDK Application Template

use tellusim::*;
use std::process::exit;
use std::thread::JoinHandle;

/*
 */
struct Application {
	
	app: App,									// Application interface
	window: Window,								// Window interface
	device: Device,								// Device interface
	target: Target,								// Target interface
	
	main_async: Async,							// main Async
	process_async: Async,						// process Async
	process_thread: Option<JoinHandle<()>>,		// process Thread
	
	scene_manager: SceneManager,				// SceneManager interface
	scene: Scene,								// Scene interface
	
	graph: Graph,								// Graph interface
	node_camera: NodeCamera,					// NodeCamera interface
	camera: CameraPerspective,					// CameraPerspective interface
	
	torus_node: NodeObject,						// NodeObject interface
	
	render_manager: RenderManager,				// RenderManager interface
	render_renderer: RenderRenderer,			// RenderRenderer interface
	render_spatial: RenderSpatial,				// RenderSpatial interface
	render_frame: RenderFrame,					// RenderFrame interface
	
	counter: u64,								// frame counter
}

impl Application {
	
	// constructor initializing the application with command-line arguments
	fn new() -> Application {
		Application {
			
			counter: 0,
			
			app: App::new(),
			window: Window::null(),
			device: Device::null(),
			target: Target::null(),
			
			main_async: Async::null(),
			process_async: Async::null(),
			process_thread: None,
			
			scene_manager: SceneManager::null(),
			scene: Scene::null(),
			
			graph: Graph::null(),
			node_camera: NodeCamera::null(),
			camera: CameraPerspective::null(),
			
			torus_node: NodeObject::null(),
			
			render_manager: RenderManager::null(),
			render_renderer: RenderRenderer::null(),
			render_spatial: RenderSpatial::null(),
			render_frame: RenderFrame::null(),
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
		
		// create scene
		if !self.create_scene() {
			return false
		}
		
		// create render
		if !self.create_render() {
			return false
		}
		
		// load scene
		let mut stream = self.scene_manager.stream();
		stream.load_graph_mut(&mut self.scene, &"scene.graphx", |_: u32, graph: Graph| {
			ts_log!(Message, "Application::create(): scene is loaded\n");
			self.torus_node = NodeObject::from_node(&graph.node_with_name("Torus Node"));
		}, SceneStreamFlags::Default);
		
		// additional initialization code can go here
		
		true
	}
	
	// update function for logic updates
	fn update(&mut self) -> bool {
		
		// update scene
		let angle = time::seconds() * 16.0;
		self.node_camera.set_global_transform(&Matrix4x3d::place_to(&(Matrix4x3d::rotate_z(-angle) * Vector3d::new(2.0, 2.0, 1.0)), &Vector3d::zero(), &Vector3d::new(0.0, 0.0, 1.0)));
		self.node_camera.update_scene();
		if self.torus_node.is_valid_ptr() {
			self.torus_node.set_pivot_transform(&(Matrix4x3f::rotate_x(angle as f32 * 3.0) * Matrix4x3f::rotate_z(angle as f32 * 2.0)));
			self.torus_node.update_scene();
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
		
		// stop process thread
		self.scene_manager.terminate();
		
		// finish device
		self.device.finish();
		
		// release render
		self.render_frame.clear_ptr();
		self.render_manager.clear_ptr();
		
		// clear scene
		self.scene.clear();
		self.scene_manager.update(&self.device, &mut self.main_async);
		self.device.finish();
		
		// wait thread
		if let Some(handle) = self.process_thread.take() {
			handle.join().ok();
		}
		
		// release scene
		self.scene.clear_ptr();
		self.scene_manager.clear_ptr();
		
		ts_log!(Message, "Done\n");
		
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
	
	// helper function to create and initialize Scene
	fn create_scene(&mut self) -> bool {
		
		// main async
		self.main_async = Async::new();
		if !self.main_async.init() {
			ts_log!(Error, "Application::create_scene(): can't initialize main Async\n");
			return false
		}
		
		// process async
		self.process_async = Async::new();
		if !self.process_async.init() {
			ts_log!(Error, "Application::create_scene(): can't initialize process Async\n");
			return false
		}
		
		// cache location
		SceneManager::set_shader_cache("shader.cache");
		SceneManager::set_texture_cache("texture.cache");
		
		ts_log!(Verbose, "Application::create_scene(): create SceneManager\n");
		
		// scene flags
		let manager_flags = SceneManagerFlags::Default;
		
		// create scene manager
		self.scene_manager = SceneManager::new();
		if !self.scene_manager.create_with_flags_func_async(&self.device, manager_flags, |_: u32| { }, Some(&self.main_async)) {
			ts_log!(Error, "Application::create_scene(): can't create SceneManager\n");
			return false
		}
		
		ts_log!(Verbose, "Application::create_scene(): SceneManager is ready\n");
		
		// create process thread
		self.process_thread = Some(std::thread::spawn({
			let mut scene_manager = self.scene_manager.copy_ptr();
			let mut process_async = self.process_async.copy_ptr();
			move || {
				while scene_manager.is_valid_ptr() && !scene_manager.is_terminated() {
					if !scene_manager.process(&mut process_async) { time::sleep(1000) }
				}
				ts_log!(Message, "Thread Done\n");
			}
		}));
		
		// initialize scene
		self.scene = Scene::new_with_manager(&mut self.scene_manager);
		
		// create camera
		self.graph = Graph::new_with_scene(&mut self.scene);
		self.camera = CameraPerspective::new_with_scene(&mut self.scene);
		self.node_camera = NodeCamera::new_with_graph_camera(&mut self.graph, &mut self.camera.to_camera());
		
		true
	}
	
	// helper function to create and initialize Render
	fn create_render(&mut self) -> bool {
		
		ts_log!(Verbose, "Application::create_render(): create RenderManager\n");
		
		// render flags
		let manager_flags = RenderManagerFlags::ShadowMap | RenderManagerFlags::Antialiasing | RenderManagerFlags::MotionBuffer;
		let renderer_flags = RenderRendererFlags::MotionBuffer | RenderRendererFlags::ScreenOcclusion | RenderRendererFlags::ScreenReflection | RenderRendererFlags::Antialiasing | RenderRendererFlags::MotionBuffer;
		
		// create render manager
		self.render_manager = RenderManager::new_with_manager(&mut self.scene_manager);
		self.render_manager.set_renderer_flags(&self.device, renderer_flags);
		self.render_manager.set_draw_parameters_with_color_depth_multisample(&self.device, self.window.color_format(), self.window.depth_format(), self.window.multisample());
		if !self.render_manager.create_with_flags_func_async(&self.device, manager_flags, |_: u32| { }, Some(&self.main_async)) {
			ts_log!(Error, "Application::create_render(): can't create manager\n");
			return false
		}
		
		ts_log!(Verbose, "Application::create_render(): RenderManager is ready\n");
		
		self.render_renderer = self.render_manager.renderer();
		self.render_spatial = self.render_manager.spatial();
		
		// create render frame
		self.render_frame = RenderFrame::new_with_manager_node(&mut self.render_manager, &mut self.node_camera);
		
		// scene render
		self.scene.set_render(Some(&self.render_renderer.scene_render()));
		
		true
	}
	
	// helper function to render the Scene
	fn render_scene(&mut self) -> bool {
		
		// update RenderManager
		self.render_manager.update();
		
		// render flags
		let spatial_flags = RenderSpatialFlags::Antialiasing;
		let renderer_flags = self.render_manager.renderer_flags();
		
		// dispatch compute
		{
			let mut compute = self.device.create_compute();
			
			// dispatch frame intersection
			self.render_spatial.dispatch_frame_with_flags(&mut compute, &mut self.render_frame, spatial_flags);
			
			// dispatch shadow map intersection
			self.render_spatial.dispatch_shadow_map_with_flags(&mut compute, &mut self.render_frame, spatial_flags);
			
			// dispatch shadow map command generation
			self.render_renderer.dispatch_shadow_map_with_flags(&mut compute, &mut self.render_frame, renderer_flags);
		}
		
		// render shadow map
		{
			// flush buffers
			self.scene_manager.flush(&self.device);
			self.render_manager.flush(&self.device);
			self.render_frame.flush(&self.device);
			
			// draw deferred
			self.render_renderer.draw_shadow_map_with_flags(&self.device, &mut self.render_frame, renderer_flags);
		}
		
		// dispatch compute
		{
			let mut compute = self.device.create_compute();
			
			// dispatch frame object intersection
			self.render_spatial.dispatch_objects_with_flags(&mut compute, &mut self.render_frame, spatial_flags);
			
			// dispatch draw command generation
			self.render_renderer.dispatch_frame_with_flags(&mut compute, &mut self.render_frame, renderer_flags);
		}
		
		// render frame
		{
			// flush buffers
			self.scene_manager.flush(&self.device);
			self.render_manager.flush(&self.device);
			self.render_frame.flush(&self.device);
			
			// draw deferred
			self.render_renderer.draw_deferred_with_flags(&self.device, &mut self.render_frame, renderer_flags);
		}
		
		// dispatch compute
		{
			let mut compute = self.device.create_compute();
			
			// dispatch render
			self.render_renderer.dispatch_screen_with_flags(&self.device, &mut compute, &mut self.render_frame, renderer_flags);
			self.render_renderer.dispatch_occlusion_with_flags(&self.device, &mut compute, &mut self.render_frame, renderer_flags);
			self.render_renderer.dispatch_light_with_flags(&self.device, &mut compute, &mut self.render_frame, renderer_flags);
			self.render_renderer.dispatch_occluder_with_flags(&self.device, &mut compute, &mut self.render_frame, renderer_flags);
			self.render_renderer.dispatch_feedback_with_flags(&self.device, &mut compute, &mut self.render_frame, renderer_flags);
			self.render_renderer.dispatch_luminance_with_flags(&self.device, &mut compute, &mut self.render_frame, renderer_flags);
			self.render_renderer.dispatch_composite_with_flags(&self.device, &mut compute, &mut self.render_frame, renderer_flags);
		}
		
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
		
		// resize RenderFrame with 200% upscale
		let width = self.window.width();
		let height = self.window.height();
		let texture = self.render_frame.composite_texture();
		if !texture.is_valid_ptr() || texture.width() != width || texture.height() != height {
			if !self.device.finish() { return false }
			self.render_frame.create_with_size(&self.device, &mut self.render_renderer, width / 2, height / 2, &Size::new_2(width, height));
		}
		
		// create Scene
		if !self.scene.create_with_async(&self.device, Some(&self.main_async)) {
			ts_log!(Error, "Application::render_window(): can't create Scene\n");
			return false
		}
		
		// update Scene
		self.scene.set_time(time::seconds());
		self.scene.update(&self.device);
		
		// update SceneManager
		let usec = 10000 as u64;
		let scene_flags = SceneManagerFlags::None;
		if !self.scene_manager.update_with_frame_memory_usec_flags(&self.device, &mut self.main_async, self.counter, 0, usec, scene_flags) {
			ts_log!(Error, "Application::render_window(): can't update SceneManager\n");
			return false
		}
		self.counter += 1;
		
		// dispatch compute
		{
			let mut compute = self.device.create_compute();
			
			// dispatch SceneManager
			self.scene_manager.dispatch(&self.device, &mut compute);
			
			// dispatch Scene
			self.scene.dispatch(&self.device, &mut compute);
		}
		
		// render scene
		if !self.render_scene() {
			ts_log!(Error, "Application::render_window(): can't render RenderFrame\n");
			return false
		}
		
		// window target
		self.target.begin();
		{
			let mut command = self.device.create_command_with_target(&mut self.target);
			let mut texture = self.render_frame.composite_texture();
			let flipped = self.target.is_flipped() ^ self.render_renderer.is_target_flipped();
			self.render_manager.draw().draw_texture_with_mode(&mut command, &mut texture, flipped, RenderDrawMode::Composite);
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
