/******************************************************************************
 *
 * Oak game engine
 * Copyright (c) 2013 Remi Papillie
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 * 
 *****************************************************************************/

#pragma once

#include <engine/app/Application.hpp>

#include <android_native_app_glue.h>
#include <EGL/egl.h>

namespace oak {

class AndroidActivity
{
	public:
		void run(android_app *app);
	
	private:
		void createWindow(ANativeWindow* window);
		void destroyWindow();
		
		void startAnimating();
		void stopAnimating();
		
		static void onAppCmd(android_app *app, int32_t command);
		static int32_t onInputEvent(android_app *app, AInputEvent* event);
		
		Application gameApplication;
		bool initialized; // app can render frames
		bool animating; // app is in focus, the game is running at 60fps
		
		// EGL parameters
		EGLDisplay eglDisplay;
		EGLSurface eglSurface;
		EGLContext eglContext;
};

} // oak namespace
