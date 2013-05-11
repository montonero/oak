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

#include <engine/script/ScriptEngine.hpp>

#include <engine/script/bind/GraphicsBind.hpp>

#include <engine/system/Log.hpp>

#include <lua.hpp>

namespace oak {

ScriptEngine::ScriptEngine()
{
	this->L = NULL;
	this->errorHandlerStackIndex = 0;
	
	this->callingFunction = false;
	this->callParameterCount = 0;
}

ScriptEngine::~ScriptEngine()
{
	OAK_ASSERT(this->L == NULL, "ScriptEngine is destroyed, but was not shut down");
}

void ScriptEngine::initialize()
{
	// create the state
	this->L = luaL_newstate();
	
	// initialize standard libs
	luaL_openlibs(this->L);
	
	// error callback function
	lua_pushcfunction(this->L, ScriptEngine::luaErrorHandler);
	this->errorHandlerStackIndex = lua_gettop(this->L);
	
	// temp function
	luaL_Reg api[] = {
		{"plop", ScriptEngine::plop},
		{NULL, NULL}
	};
	//lua_register(L, "plop", ScriptEngine::plop);
	//luaL_register(L, "oak", api);
	lua_register(L, "plop", ScriptEngine::plop);
}

void ScriptEngine::shutdown()
{
	lua_close(this->L);
	this->L = NULL;
}

void ScriptEngine::loadFile(const std::string &filename)
{
	luaL_dofile(this->L, filename.c_str());
}

bool ScriptEngine::startCall(const std::string &functionName)
{
	OAK_ASSERT(!this->callingFunction, "A function call is already in progress");
	
	// check that the symbol exists, and is actually a function
	lua_getglobal(this->L, functionName.c_str());
	if (lua_type(this->L, -1) != LUA_TFUNCTION)
	{
		// just pop the unknown value
		lua_pop(this->L, 1);
		return false;
	}
	
	this->callingFunction = true;
	return true;
}

void ScriptEngine::appendParameter(double value)
{
	if (!this->callingFunction)
		return;
	
	lua_pushnumber(this->L, value);
	this->callParameterCount++;
}

void ScriptEngine::endCall()
{
	if (!this->callingFunction)
		return;
	
	// actual call
	lua_pcall(this->L, this->callParameterCount, 0, this->errorHandlerStackIndex);
	
	this->callingFunction = false;
	this->callParameterCount = 0;
}

void ScriptEngine::registerGraphics(GraphicsEngine *graphics)
{
	GraphicsBind::registerFunctions(this->L, graphics);
}

int ScriptEngine::luaErrorHandler(lua_State *L)
{
	const char *errorMessage = lua_tostring(L, -1);
	Log::warning(std::string(errorMessage));
	
	return 0;
}

// temp
int ScriptEngine::plop(lua_State *L)
{
	const char *message = lua_tostring(L, -1);
	lua_pop(L, 1);
	
	Log::info(std::string(message));
	
	return 1;
}

} // oak namespace