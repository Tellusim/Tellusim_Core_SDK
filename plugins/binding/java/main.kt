// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.main

import com.tellusim.*

import kotlin.math.*

import java.nio.ByteOrder
import java.nio.ByteBuffer

/*
 */
fun main(args: Array<String>) {
	
	// load library
	Base.loadDebug()
	
	// create app
	val app = App(args)
	if(!app.create(Platform.Any)) return
	
	// create window
	val window = Window(app.platform, app.device)
	if(!window.isValidPtr()) return
	
	window.setSize(app.width, app.height)
	window.setCloseClickedCallback(object: Window.CloseClickedCallback() {
		override fun run() { window.stop() }
	})
	window.setKeyboardPressedCallback(object: Window.KeyboardPressedCallback() {
		override fun run(key: Int, code: Int) {
			if(key == Window.Key.Esc.value) window.stop()
			if(key == Window.Key.F12.value) {
				val image = Image()
				if(window.grab(image) && image.save("screenshot.png")) {
					Log.print(Log.Level.Message, "Screenshot\n")
				}
			}
		}
	})
	
	val title = window.platformName + " Tellusim::Kotlin"
	val flags = Window.Flags.DefaultFlags.or(Window.Flags.VerticalSync)
	if(!window.create(title, flags) || !window.setHidden(false)) return
	
	// create device
	val device = Device(window)
	if(!device.isValidPtr()) return
	
	// device features
	Log.printf(Log.Level.Message, "Features:\n%s\n", device.features)
	Log.printf(Log.Level.Message, "Device: %s\n", device.name)
	
	// build info
	Log.printf(Log.Level.Message, "Build: %s\n", App.getBuildInfo())
	
	// create target
	val target = device.createTarget(window)
	if(!target.isValidPtr()) return
	
	////////////////////////////////
	// core test
	////////////////////////////////
	
	val blob = Blob()
	blob.writeString(title)
	
	blob.seek(0)
	Log.printf(Log.Level.Message, "Stream: %s\n", blob.readString())
	
	////////////////////////////////
	// platform test
	////////////////////////////////
	
	// create pipeline
	val pipeline = device.createPipeline()
	pipeline.setUniformMask(0, Shader.Mask.Fragment)
	pipeline.setColorFormat(window.colorFormat)
	pipeline.setDepthFormat(window.depthFormat)
	pipeline.addAttribute(Pipeline.Attribute.Position, Format.RGf32, 0, 0, 8)
	if(!pipeline.loadShaderGLSL(Shader.Type.Vertex, "main.shader", "VERTEX_SHADER=1")) return
	if(!pipeline.loadShaderGLSL(Shader.Type.Fragment, "main.shader", "FRAGMENT_SHADER=1")) return
	if(!pipeline.create()) return
	
	// geometry vertices
	val vertices = arrayOf( Vector2f(3.0f, -1.0f), Vector2f(-1.0f, -1.0f), Vector2f(-1.0f, 3.0f) )
	
	// geometry indices
	val indices = shortArrayOf( 0, 1, 2 )
	
	////////////////////////////////
	// interface test
	////////////////////////////////
	
	// create canvas
	val canvas = Canvas()
	
	// create root controls
	val root = ControlRoot(canvas, true)
	root.fontSize = 24
	
	// create dialog
	val dialog = ControlDialog(root.ref(), 1, 8.0f, 8.0f)
	dialog.setUpdatedCallback(object: ControlDialog.UpdatedCallback() {
		override fun run(dialog: ControlDialog) {
			val x = dialog.positionX.toInt()
			val y = dialog.positionY.toInt()
			val width = dialog.width.toInt()
			val height = dialog.height.toInt()
			Log.printf(Log.Level.Message, "Dialog Updated %d %d %dx%d\n", x, y, width, height)
		}
	})
	dialog.setAlign(Control.Align.Center)
	dialog.setSize(240.0f, 180.0f)
	
	// create text
	val text = ControlText(dialog.ref(), title)
	text.setAlign(Control.Align.CenterX)
	
	// create button
	val button = ControlButton(dialog.ref(), "Button")
	button.setClickedCallback(object: ControlButton.ClickedCallback() {
		override fun run(button: ControlButton) {
			Log.printf(Log.Level.Message, "%s Clicked\n", button.text)
		}
	})
	button.setAlign(Control.Align.Expand)
	button.setMargin(0.0f, 0.0f, 0.0f, 16.0f)
	
	// create sliders
	val color = Color.white()
	val slider_r = ControlSlider(dialog.ref(), "R", 2, color.r.toDouble(), 0.0, 1.0)
	val slider_g = ControlSlider(dialog.ref(), "G", 2, color.g.toDouble(), 0.0, 1.0)
	val slider_b = ControlSlider(dialog.ref(), "B", 2, color.b.toDouble(), 0.0, 1.0)
	slider_r.setChangedCallback(object: ControlSlider.ChangedCallback() { override fun run(slider: ControlSlider) { color.r = slider.valuef32 } })
	slider_g.setChangedCallback(object: ControlSlider.ChangedCallback() { override fun run(slider: ControlSlider) { color.g = slider.valuef32 } })
	slider_b.setChangedCallback(object: ControlSlider.ChangedCallback() { override fun run(slider: ControlSlider) { color.b = slider.valuef32 } })
	slider_r.setAlign(Control.Align.ExpandX)
	slider_g.setAlign(Control.Align.ExpandX)
	slider_b.setAlign(Control.Align.ExpandX)
	
	////////////////////////////////
	// main loop
	////////////////////////////////
	
	// main loop
	window.run(object: Window.MainLoopCallback() {
		override fun run(): Boolean {
			
			Window.update()
			
			// render window
			if(!window.render()) return false
			
			// update interface
			if(true) {
				
				// window size
				val height = app.height.toFloat()
				val width = floor(height * window.width / window.height)
				val mouse_x = width * window.mouseX / window.width
				val mouse_y = height * window.mouseY / window.height
				
				// mouse button
				var buttons = 0
				if((window.mouseButtons.value and Window.Button.Left.value) != 0) buttons = buttons or Control.Button.Left.value
				if((window.mouseButtons.value and Window.Button.Left2.value) != 0) buttons = buttons or Control.Button.Left.value
				
				// update controls
				root.setViewport(width, height)
				root.setMouse(mouse_x, mouse_y, Control.Button(buttons))
				while(root.update(canvas.getScale(target))) { }
				
				// create canvas
				canvas.create(device, target)
			}
			
			// window target
			if(target.begin()) {
				
				val command = device.createCommand(target)
				
				// common parameters
				val time = Time.seconds().toFloat()
				val parameters = ByteBuffer.allocate(64 + 32).order(ByteOrder.LITTLE_ENDIAN)
				parameters.put(Matrix4x4f.rotateZ(time * 16.0f).bytes)
				parameters.put(color.bytes)
				parameters.putFloat(time)
				
				// draw background
				command.setPipeline(pipeline)
				command.setUniform(0, parameters)
				command.setVertices(0, vertices)
				command.setIndices(indices)
				command.drawElements(3)
				
				// draw canvas
				canvas.draw(command, target)
				
				// destroy pointer
				command.destroyPtr()
				
				target.end()
			}
			
			// present window
			if(!window.present()) return false
			
			// check device
			if(!device.check()) return false
			
			return true
		}
	})
	
	// finish context
	window.finish()
	
	// destroy resources
	root.destroyPtr()
	
	// done
	Log.print(Log.Level.Message, "Done\n")
}
