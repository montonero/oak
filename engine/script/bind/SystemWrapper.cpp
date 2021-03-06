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

#include <engine/script/bind/SystemWrapper.hpp>

#include <engine/system/Log.hpp>
#include <engine/system/Time.hpp>

namespace oak {

void SystemWrapper::logInfo(const std::string &message)
{
	Log::info("%s", message.c_str());
}

void SystemWrapper::logWarning(const std::string &message)
{
	Log::warning("%s", message.c_str());
}

void SystemWrapper::logError(const std::string &message)
{
	Log::error("%s", message.c_str());
}

double SystemWrapper::getTime()
{
	return Time::getTime();
}

double SystemWrapper::getElapsedTime()
{
	return Time::getElapsedTime();
}

} // oak namespace
