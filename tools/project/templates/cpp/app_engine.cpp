// Tellusim Engine SDK Application Template

#include "Application.h"

/*
 */
#define LOAD_SCENE	1

/*
 */
using namespace Tellusim;

/*
 */
class MyApplication : public Application {
		
	public:
		
		// constructor initializing the application with command-line arguments
		MyApplication(int32_t argc, char **argv) : Application(argc, argv) {
			
		}
		
		// destructor cleans up resources
		virtual ~MyApplication() {
			
			TS_LOG(Verbose, "MyApplication::~MyApplication(): Done\n");
		}
		
		// create function responsible for initialization
		virtual bool create() {
			
			// create application
			if(!Application::create()) return false;
			
			// load scene
			#if LOAD_SCENE
				SceneStream stream = scene_manager.getStream();
				stream.loadGraph(scene, "scene.graphx", [&](uint32_t stream_id, Graph graph) {
					TS_LOG(Message, "MyApplication::create(): scene is loaded\n");
					torus_node = NodeObject(graph.getNode("Torus Node"));
				}, SceneStream::DefaultFlags);
			#endif
			
			// additional initialization code can go here
			
			return true;
		}
		
		// update function for logic updates
		virtual bool update() {
			
			// update scene
			#if LOAD_SCENE
				float32_t angle = (float32_t)Time::seconds() * 16.0f;
				node_camera.setGlobalTransform(Matrix4x3d::placeTo(Matrix4x3d::rotateZ(-angle) * Vector3d(2.0, 2.0, 1.0), Vector3d::zero, Vector3d(0.0, 0.0, 1.0)));
				node_camera.updateScene();
				if(torus_node) {
					torus_node.setPivotTransform(Matrix4x3f::rotateX(angle * 3.0f) * Matrix4x3f::rotateZ(angle * 2.0f));
					torus_node.updateScene();
				}
			#endif
			
			// your update logic here
			
			return true;
		}
		
	private:
		
		#if LOAD_SCENE
			NodeObject torus_node;	// torus node
		#endif
};

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	// instantiate the application
	MyApplication application(argc, argv);
	
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
