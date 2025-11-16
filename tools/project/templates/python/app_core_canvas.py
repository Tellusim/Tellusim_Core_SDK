#!/usr/bin/env python3

# Tellusim Canvas Application Template

import sys
import math

from tellusimd import *

#
# main
#
def main(argv):
	
	app = None
	window = None
	device = None
	target = None
	canvas = None
	
	ellipses = []
	
	#
	# create function responsible for initialization
	#
	def create():
		
		nonlocal app
		
		# create app
		app = App(argv)
		if not app.create():
			Log.print(Log.Error, 'create(): can\'t create App\n')
			return False
		
		# create window
		if not create_window():
			return False
		
		# create pipeline
		if not create_resources():
			return False
		
		# additional initialization code can go here
		
		return True
	
	#
	# update function for logic updates
	#
	def update():
		
		# update canvas elements
		hheight = canvas.height * 0.5
		for i in range(len(ellipses)):
			angle = Pi2 * i / len(ellipses) + Time.seconds()
			x = canvas.width * (1 + i) / (len(ellipses) + 1)
			y0 = hheight + math.cos(angle * 2.0 - 0.2) * math.sin(angle - 0.1) * hheight * 0.9
			y1 = hheight + math.cos(angle * 2.0 + 0.2) * math.sin(angle + 0.1) * hheight * 0.9
			ellipses[i].setColor(Color.hsv(angle * Rad2Deg + y0 * 0.5, 1.0, 1.0))
			ellipses[i].setRadius(math.sqrt(20.0 * 20.0 + (y1 - y0) * (y1 - y0) * 0.25))
			ellipses[i].setPosition0(Vector3f(x, y0, 0.0))
			ellipses[i].setPosition1(Vector3f(x, y1, 0.0))
		
		# your update logic here
		
		return True
	
	#
	# helper function to create and initialize the Window
	#
	def create_window():
		
		nonlocal window, device, target
		
		# create Window
		window = Window(app.platform, app.device)
		if not window or not window.setSize(app.width, app.height) \
			or not window.create(window.platform_name + ' Python @NAME@') or not window.setHidden(False):
			Log.print(Log.Error, 'create_window(): can\'t create Window\n')
			return False
		
		# set Window callbacks
		def pressed_callback(key, code):
			if key == Window.KeyF4 and window.getKeyboardKey(Window.Key.Alt): window.stop()
			if key == Window.KeyEsc: window.stop()
		window.setKeyboardPressedCallback(pressed_callback)
		window.setCloseClickedCallback(lambda: window.stop())
		
		# create Device
		device = Device(window)
		if not device:
			Log.print(Log.Error, 'create_window(): can\'t create Device\n')
			return False
		
		# create Target
		target = device.createTarget(window)
		if not target:
			Log.print(Log.Error, 'create_window(): can\'t create Target\n')
			return False
		
		return True
	
	#
	# helper function to create and load resources
	#
	def create_resources():
		
		nonlocal canvas
		
		# gray background
		target.setClearColor(Color(0.1))
		
		# create canvas
		canvas = Canvas()
		canvas.setViewport(1280.0, 720.0)
		
		# create ellipses
		for i in range(32):
			ellipse = CanvasEllipse(canvas)
			ellipse.setStrokeStyle(StrokeStyle(width = 4.0, color = Color.white))
			ellipses.append(ellipse)
		
		# your resource creation code here
		
		return True
	
	#
	# helper function to render the Window
	#
	def render_window():
		
		# update events
		Window.update()
		
		# update application
		if not update(): return False
		
		# render window
		if not window.render(): return False
		
		# create canvas
		if not canvas.create(device, target): return False
		
		# window target
		if target.begin():
			
			command = device.createCommand(target)
			
			# draw canvas
			canvas.draw(command, target)
			
			command = None
			
			target.end()
		
		# present window
		if not window.present(): return False
		
		# check errors
		if not device.check(): return False
		
		return True
	
	# create the application
	if not create():
		return 1
	
	# run the application
	window.run(render_window)
	
	# finish context
	window.finish()
	
	return 0
	
#
# entry point
#
if __name__ == '__main__':
	try:
		exit(main(sys.argv))
	except Exception as error:
		print('\n' + str(error))
		exit(1)
