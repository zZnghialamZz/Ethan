// ==================================================
//      _____
//   __|___  |__    __    __   _  ____    ____   _
//  |   ___|    | _|  |_ |  |_| ||    \  |    \ | |
//  |   ___|    ||_    _||   _  ||     \ |     \| |
//  |______|  __|  |__|  |__| |_||__|\__\|__/\____|
//     |_____|
//                   Game Engine
// ==================================================
//
// Github : https://github.com/zZnghialamZz/Ethan
// License: MIT License (See LICENSE for details)
//
// ---
// EthanEngine/Core/Application.cpp

#include "Application.hpp"
#include "Logger.hpp"

namespace Ethan
{
	Application::Application() = default;
	Application::~Application() = default;

	void Application::Start()
	{
        Logger::InitLoggers();
	}

	void Application::RunLoop()
	{
	}

	void Application::Exit()
	{
        Logger::ShutDown();
	}
} // namespace Ethan
