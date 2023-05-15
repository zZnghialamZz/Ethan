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
// EthanEngine/BasicDefines.c

#ifndef ETHANENGINE_BASICDEFINES_H
#define ETHANENGINE_BASICDEFINES_H

// ---------------------------------------------------------------------------------
// SECTION: OS
// ---------------------------------------------------------------------------------

#if defined(_WIN32)
    #define OS_WIN32 1
#elif defined(__gnu_linux__)
    #define OS_LINUX 1
#elif defined(__APPLE__) && defined(__MACH__)
    #define OS_MACOS 1
#else
    #error Unsupport OS detection!!
#endif

// ---------------------------------------------------------------------------------
// SECTION: API Defines
// ---
// NOTE: Define attributes of all API symbols declarations (e.g. for DLL under
// Windows). This mostly used for EthanEngine framework when building it as a
// shared library.
// ---------------------------------------------------------------------------------


#ifndef ETHAN_API
    #if defined(OS_WIN32) && defined(ETHAN_BUILD_DLL)
        #define ETHAN_API __declspec(dllexport)
    #elif defined(OS_WIN32)
        #define ETHAN_API __declspec(dllimport)
    #else
        #define ETHAN_API
    #endif
#endif
#ifndef ETHAN_API_IMPL
    #define ETHAN_API_IMPL
#endif

// ---------------------------------------------------------------------------------
// SECTION: Compiler & Architecture
// ---------------------------------------------------------------------------------

#if defined(__clang__)
    #define COMPILER_CLANG 1

    #if defined(__amd64__)
        #define ARCH_X64 1
    #elif defined(__i386__)
        #define ARCH_X86 1
    #elif defined(__arm__)
        #define ARCH_ARM 1
    #elif defined(__aarch64__)
        #define ARCH_ARM64 1
    #else
        #error Unsupport Architecture detection!!
    #endif

#elif defined(_MSC_VER)
    #define COMPILER_MSVC 1

    #if defined(_M_AMD64)
        #define ARCH_X64 1
    #elif defined(_M_IX86)
        #define ARCH_X86 1
    #elif defined(_M_ARM)
        #define ARCH_ARM 1
    #elif defined(_M_ARM64)
        #define ARCH_ARM64 1
    #else
        #error Unsupport Architecture detection!!
    #endif

#elif defined(__GNUC__)
    #define COMPILER_GCC 1

    #if defined(__amd64__)
        #define ARCH_X64 1
    #elif defined(__i386__)
        #define ARCH_X86 1
    #elif defined(__arm__)
        #define ARCH_ARM 1
    #elif defined(__aarch64__)
        #define ARCH_ARM64 1
    #else
        #error Unsupport Architecture detection!!
    #endif

#else
    #error Unsupport Compiler detection!!
#endif

// Zero-fill the above context marcros

#ifndef OS_WIN32
    #define OS_WIN32 0
#endif
#ifndef OS_LINUX
    #define OS_LINUX 0
#endif
#ifndef OS_MACOS
    #define OS_MACOS 0
#endif

#ifndef COMPILER_CLANG
    #define COMPILER_CLANG 0
#endif
#ifndef COMPILER_MSVC
    #define COMPILER_MSVC 0
#endif
#ifndef COMPILER_GCC
    #define COMPILER_GCC 0
#endif

#ifndef ARCH_X64
    #define ARCH_X64 0
#endif
#ifndef ARCH_X86
    #define ARCH_X86 0
#endif
#ifndef ARCH_ARM
    #define ARCH_ARM 0
#endif
#ifndef ARCH_ARM64
    #define ARCH_ARM64 0
#endif

// --------------------------------------------------------------------------------
// SECTION: Assertion Helpers
// --------------------------------------------------------------------------------

#if USE_ETHAN_ASSERT
    #if !defined(ASSERT_ABORT)
        #if OS_WIN32
            #define ASSERT_ABORT()  \
                do                  \
                {                   \
                    __debugbreak(); \
                    exit(1);        \
                }                   \
                while (0)
        #else
            #define ASSERT_ABORT() (*(int*)0 = 0)
        #endif
    #endif

    #if !defined(ASSERT_BREAK)
        #if defined(USE_ETHAN_DEBUG)
            #define ASSERT_BREAK() ASSERT_ABORT()
        #else
            #define ASSERT_BREAK()
        #endif
    #endif
#endif

// ---------------------------------------------------------------------------------
// SECTION: Type Definitions
// ---------------------------------------------------------------------------------

// NOTE(Nghia Lam): Turn off clang-format for this piece of code here since we
// do a lot of manual alignment here for visibility. Need to take a deep look
// into clang-format if they support typedef alignment yet.
// ---
// clang-format off

typedef unsigned char      UInt8;
typedef unsigned short     UInt16;
typedef unsigned int       UInt32;
typedef unsigned long long UInt64;

typedef signed char      Int8;
typedef signed short     Int16;
typedef signed int       Int32;
typedef signed long long Int64;

typedef float  Float32;
typedef double Float64;

// clang-format on

#endif // ETHANENGINE_BASICDEFINES_H
