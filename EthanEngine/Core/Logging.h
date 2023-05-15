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
// Author: Nghia Lam
// Github: https://github.com/zZnghialamZz/Ethan
// License: MIT License (See LICENSE for details)
//
// ---
// EthanEngine/Core/Logging.h

#ifndef ETHANENGINE_CORE_LOGGING_H
#define ETHANENGINE_CORE_LOGGING_H

#include "EthanEngine/BasicDefines.h"

// ---------------------------------------------------------------------------------
// SECTION: Settings
// ---------------------------------------------------------------------------------

#if defined(USE_ETHAN_DEBUG)
    #define LOG_TRACE_ENABLED 1
    #define LOG_DEBUG_ENABLED 1
#else
    #define LOG_TRACE_ENABLED 0
    #define LOG_DEBUG_ENABLED 0
#endif

#define LOG_INFO_ENABLED  1
#define LOG_WARN_ENABLED  1
#define LOG_ERROR_ENABLED 1
#define LOG_FATAL_ENABLED 1

// ---------------------------------------------------------------------------------
// SECTION: Types & structures
// ---------------------------------------------------------------------------------

typedef enum ELogLevel
{
    ELogTrace = 0,
    ELogDebug = 1,
    ELogInfo  = 2,
    ELogWarn  = 3,
    ELogError = 4,
    ELogFatal = 5,
} ELogLevel;

// ---------------------------------------------------------------------------------
// SECTION: Logging APIs
// ---------------------------------------------------------------------------------

ETHAN_API void ELoggerInitialize();
ETHAN_API void ELoggerShutdown();
ETHAN_API void ELoggerLogOutput(ELogLevel level, const char* message, ...);

#if LOG_TRACE_ENABLED == 1
    #define ELOG_TRACE(message, ...) ELoggerLogOutput(ELogTrace, message, ##__VA_ARGS__)
#else
    #define ELOG_TRACE(message, ...)
#endif
#if LOG_DEBUG_ENABLED == 1
    #define ELOG_DEBUG(message, ...) ELoggerLogOutput(ELogDebug, message, ##__VA_ARGS__)
#else
    #define ELOG_DEBUG(message, ...)
#endif
#if LOG_INFO_ENABLED == 1
    #define ELOG_INFO(message, ...) ELoggerLogOutput(ELogInfo, message, ##__VA_ARGS__)
#else
    #define ELOG_INFO(message, ...)
#endif
#if LOG_WARN_ENABLED == 1
    #define ELOG_WARN(message, ...) ELoggerLogOutput(ELogWarn, message, ##__VA_ARGS__)
#else
    #define ELOG_WARN(message, ...)
#endif
#if LOG_ERROR_ENABLED == 1
    #define ELOG_ERROR(message, ...) ELoggerLogOutput(ELogError, message, ##__VA_ARGS__)
#else
    #define ELOG_ERROR(message, ...)
#endif
#if LOG_FATAL_ENABLED == 1
    #define ELOG_FATAL(message, ...) ELoggerLogOutput(ELogFatal, message, ##__VA_ARGS__)
#else
    #define ELOG_FATAL(message, ...)
#endif

#endif // ETHANENGINE_CORE_LOGGING_H
