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
// EthanEngine/Core/Logger.hpp

#ifndef ETHANENGINE_CORE_LOGGER_H
#define ETHANENGINE_CORE_LOGGER_H

// ---------------------------------------------------------------------------------
// SECTION: Settings
// ---------------------------------------------------------------------------------

#if defined(USE_ETHAN_DEBUG)
	#define LOG_TRACE_ENABLED 1
	#define LOG_INFO_ENABLED  1

	#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#else
	#define LOG_TRACE_ENABLED 0
	#define LOG_INFO_ENABLED  0
#endif

#define LOG_WARN_ENABLED  1
#define LOG_ERROR_ENABLED 1
#define LOG_FATAL_ENABLED 1

// This ignores all warnings raised inside External headers
#pragma warning(push, 0)
#include <spdlog/spdlog.h> // For spdlog::logger
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)

// ---------------------------------------------------------------------------------
// SECTION: Logging APIs
// ---------------------------------------------------------------------------------

namespace Ethan
{
	class ETHAN_API Logger
	{
	public:
		static void InitLoggers();
		static void ShutDown();
		static void PrintContextInfo();

		static Shared<spdlog::logger>& GetEngineLogger() { return EngineLogger; }
		static Shared<spdlog::logger>& GetClientLogger() { return ClientLogger; }

	private:
		static Shared<spdlog::logger> EngineLogger;
		static Shared<spdlog::logger> ClientLogger;
	};
} // namespace Ethan

#if LOG_TRACE_ENABLED == 1
	#define ENGINELOG_TRACE(...) SPDLOG_LOGGER_TRACE(::Ethan::Logger::GetEngineLogger(), __VA_ARGS__)
	#define CLIENTLOG_TRACE(...) SPDLOG_LOGGER_TRACE(::Ethan::Logger::GetClientLogger(), __VA_ARGS__)
#else
	#define ENGINELOG_TRACE(...)
	#define CLIENTLOG_TRACE(...)
#endif
#if LOG_INFO_ENABLED == 1
	#define ENGINELOG_INFO(...) SPDLOG_LOGGER_INFO(::Ethan::Logger::GetEngineLogger(), __VA_ARGS__)
	#define CLIENTLOG_INFO(...) SPDLOG_LOGGER_INFO(::Ethan::Logger::GetClientLogger(), __VA_ARGS__)
#else
	#define ENGINELOG_INFO(...)
	#define CLIENTLOG_INFO(...)
#endif
#if LOG_WARN_ENABLED == 1
	#define ENGINELOG_WARN(...) SPDLOG_LOGGER_WARN(::Ethan::Logger::GetEngineLogger(), __VA_ARGS__)
	#define CLIENTLOG_WARN(...) SPDLOG_LOGGER_WARN(::Ethan::Logger::GetClientLogger(), __VA_ARGS__)
#else
	#define ENGINELOG_WARN(...)
	#define CLIENTLOG_WARN(...)
#endif
#if LOG_ERROR_ENABLED == 1
	#define ENGINELOG_ERROR(...) SPDLOG_LOGGER_ERROR(::Ethan::Logger::GetEngineLogger(), __VA_ARGS__)
	#define CLIENTLOG_ERROR(...) SPDLOG_LOGGER_ERROR(::Ethan::Logger::GetClientLogger(), __VA_ARGS__)
#else
	#define ENGINELOG_ERROR(...)
	#define CLIENTLOG_ERROR(...)
#endif
#if LOG_FATAL_ENABLED == 1
	#define ENGINELOG_FATAL(...) SPDLOG_LOGGER_CRITICAL(::Ethan::Logger::GetEngineLogger(), __VA_ARGS__)
	#define CLIENTLOG_FATAL(...) SPDLOG_LOGGER_CRITICAL(::Ethan::Logger::GetClientLogger(), __VA_ARGS__)
#else
	#define ENGINELOG_FATAL(...)
	#define CLIENTLOG_FATAL(...)
#endif

#if USE_ETHAN_ASSERT
	#define ENGINEASSERT(x, ...)                                                    \
		{                                                                           \
			if (!(x))                                                               \
			{                                                                       \
				ENGINELOG_FATAL("Assertion Failed !! More Info: {0}", __VA_ARGS__); \
				ASSERT_BREAK();                                                     \
			}                                                                       \
		}
	#define CLIENTASSERT(x, ...)                                                    \
		{                                                                           \
			if (!(x))                                                               \
			{                                                                       \
				CLIENTLOG_FATAL("Assertion Failed !! More Info: {0}", __VA_ARGS__); \
				ASSERT_BREAK();                                                     \
			}                                                                       \
		}
#else
	#define ENGINEASSERT(x, ...)
	#define CLIENTASSERT(x, ...)
#endif

#endif // ETHANENGINE_CORE_LOGGER_H
