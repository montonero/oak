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

#include <engine/app/Application.hpp>

#include <glm/glm.hpp>

#include <engine/input/InputEngine.hpp>
#include <engine/graphics/GraphicsEngine.hpp>
#include <engine/script/ScriptEngine.hpp>
#include <engine/sg/WorldManager.hpp>
#include <engine/system/Log.hpp>
#include <engine/system/Time.hpp>

namespace oak {

void Application::initialize(const std::string &baseFolder)
{
	Log::info("Application::initialize");
	
	Time::reset();
	
	this->worldManager = new WorldManager;
	
	this->input = new InputEngine;
	this->input->addListener(this);
	
	this->graphics = new GraphicsEngine(this->worldManager);
	
	this->script = new ScriptEngine(baseFolder);
	this->script->initialize();
	
	// script bindings
	this->script->registerGraphics(this->graphics);
	this->script->registerSg(this->worldManager);
	
	this->script->loadFile("main.lua");
	
	this->script->startCall("initialize");
	this->script->endCall();
}

void Application::shutdown()
{
	Log::info("Application::shutdown");
	
	this->script->startCall("shutdown");
	this->script->endCall();
	
	this->script->shutdown();
	delete this->script;
	
	delete this->graphics;
	
	this->input->removeListener(this);
	delete this->input;
	
	delete this->worldManager;
}

void Application::update()
{
	Time::frameStart();
	
	this->input->update();
	
	this->script->startCall("update");
	this->script->appendParameter(Time::getElapsedTime());
	this->script->endCall();
	
	this->graphics->renderFrame();
}

void Application::pointerDown(unsigned int pointerId, unsigned int button, glm::vec2 position)
{
	this->script->startCall("pointerDown");
	this->script->appendParameter((int)pointerId);
	this->script->appendParameter((int)button);
	this->script->appendParameter(position.x);
	this->script->appendParameter(position.y);
	this->script->endCall();
}

void Application::pointerUp(unsigned int pointerId, unsigned int button, glm::vec2 position)
{
	this->script->startCall("pointerUp");
	this->script->appendParameter((int)pointerId);
	this->script->appendParameter((int)button);
	this->script->appendParameter(position.x);
	this->script->appendParameter(position.y);
	this->script->endCall();
}

void Application::pointerMove(unsigned int pointerId, glm::vec2 position, glm::vec2 movement)
{
	this->script->startCall("pointerMove");
	this->script->appendParameter((int)pointerId);
	this->script->appendParameter(position.x);
	this->script->appendParameter(position.y);
	this->script->appendParameter(movement.x);
	this->script->appendParameter(movement.y);
	this->script->endCall();
}

} // oak namespace
