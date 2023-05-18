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
// EthanEngine/Core/Logging.c

#include "Logging.h"

#include <memory.h> // Required for: memset

ETHAN_API_IMPL void ELoggerLogOutput(ELogLevel level, const char* message, const char* file, int line, ...)
{
    char buffer[MAX_LOG_LENGTH];
    memset(buffer, 0, sizeof(buffer));
}
