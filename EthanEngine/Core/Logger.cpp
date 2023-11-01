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
// EthanEngine/Core/Logger.cpp

#include "Logger.hpp"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace Ethan
{
	Shared<spdlog::logger> Logger::EngineLogger;
	Shared<spdlog::logger> Logger::ClientLogger;

	void Logger::InitLoggers()
	{
		spdlog::sink_ptr sink = CreateSharedPtr<spdlog::sinks::stdout_color_sink_mt>();
		sink->set_pattern("%^(%H:%M:%S) [%n] %s:%# - %l : %v%$");

		EngineLogger = CreateSharedPtr<spdlog::logger>("ETHAN", sink);
		EngineLogger->set_level(spdlog::level::trace);
		EngineLogger->flush_on(spdlog::level::trace);
		spdlog::register_logger(EngineLogger);

		ClientLogger = CreateSharedPtr<spdlog::logger>("EDITOR", sink);
		ClientLogger->set_level(spdlog::level::trace);
		ClientLogger->flush_on(spdlog::level::trace);
		spdlog::register_logger(ClientLogger);

		PrintContextInfo();
	}

	void Logger::ShutDown()
	{
		spdlog::shutdown();
	}

	void Logger::PrintContextInfo()
	{
		ENGINELOG_INFO("\n\n"
					   "\tEngine Context Info:\n"
					   "\t|\n"
					   "\t-\tOS:\n"
					   "\t|\t\tWin32 = {0}\n"
					   "\t|\t\tLinux = {1}\n"
					   "\t|\t\tMacos = {2}\n"
					   "\t-\tCompiler:\n"
					   "\t|\t\tClang = {3}\n"
					   "\t|\t\tMSVC  = {4}\n"
					   "\t|\t\tGCC   = {5}\n"
					   "\t-\tArchitecture:\n"
					   "\t|\t\tx64   = {6}\n"
					   "\t|\t\tx86   = {7}\n"
					   "\t|\t\tarm   = {8}\n"
					   "\t|\t\tarm64 = {9}\n",
					   OS_WIN32, OS_LINUX, OS_MACOS, COMPILER_CLANG, COMPILER_MSVC, COMPILER_GCC, ARCH_X64, ARCH_X86, ARCH_ARM, ARCH_ARM64);
	}
} // namespace Ethan
