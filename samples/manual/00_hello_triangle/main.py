#!/usr/bin/env python3

# Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
# https://tellusim.com/

from tellusimd import *

#
# main
#
def main():
	
	# create window
	window = Window(PlatformAny)
	if not window or not window.create('00 Hello Triangle Python') or not window.setHidden(False): return 1
	window.setKeyboardPressedCallback(lambda key, code: window.stop() if key == Window.KeyEsc else None)
	
	# create device
	device = Device(window)
	if not device: return 1
	
	# create pipeline
	pipeline = device.createPipeline()
	pipeline.addAttribute(Pipeline.AttributePosition, FormatRGf32, 0, offset = 0, stride = 24)
	pipeline.addAttribute(Pipeline.AttributeColor, FormatRGBAf32, 0, offset = 8, stride = 24)
	pipeline.setColorFormat(window.getColorFormat())
	pipeline.setDepthFormat(window.getDepthFormat())
	pipeline.setDepthFunc(Pipeline.DepthFuncAlways)
	
	# vertex shader
	if not pipeline.createShaderGLSL(Shader.TypeVertex, '''
		layout(location = 0) in vec4 in_position;
		layout(location = 1) in vec4 in_color;
		layout(location = 0) out vec4 s_color;
		void main() {
			gl_Position = in_position;
			s_color = in_color;
		}
	'''): return 1
	
	# fragment shader
	if not pipeline.createShaderGLSL(Shader.TypeFragment, '''
		layout(location = 0) in vec4 s_color;
		layout(location = 0) out vec4 out_color;
		void main() {
			out_color = s_color;
		}
	'''): return 1
	
	if not pipeline.create(): return 1
	
	# create target
	target = device.createTarget(window)
	target.setClearColor(Color.gray)
	
	# vertex data
	vertices  = bytearray(Vector2f( 1.0, -1.0)) + Color.red
	vertices += bytearray(Vector2f(-1.0, -1.0)) + Color.green
	vertices += bytearray(Vector2f( 0.0,  1.0)) + Color.blue
	
	# main loop
	def main_loop():
		
		Window.update()
		
		if not window.render(): return False
		
		# window target
		if target.begin():
			
			# create command list
			command = device.createCommand(target)
			
			# set pipeline
			command.setPipeline(pipeline)
			
			# set vertex data
			command.setVertices(0, vertices)
			
			# draw triangle
			command.drawArrays(3)
			
			command = None
			
			target.end()
		
		if not window.present(): return False
		
		if not device.check(): return False
		
		return True
	
	window.run(main_loop)
	
	# finish context
	window.finish()
	
	# done
	Log.print('Done\n')
	
	return 0

#
# entry point
#
if __name__ == '__main__':
	try:
		exit(main())
	except Exception as error:
		print('\n' + str(error))
		exit(1)
