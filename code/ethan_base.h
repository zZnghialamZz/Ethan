/* ==========================================================================
|  @File   : ethan_base.h
|  @Brief  : ...
|  @Author : Nghia Lam <nghialam12795@gmail.com>
|  ---
|  @License: MIT License.
|
|  Copyright (c) 2021 Nghia Lam
|
|  Permission is hereby granted, free of charge, to any person obtaining a copy
|  of this software and associated documentation files (the "Software"), to deal
|  in the Software without restriction, including without limitation the rights
|  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
|  copies of the Software, and to permit persons to whom the Software is
|  furnished to do so, subject to the following conditions:
|
|  The above copyright notice and this permission notice shall be included in
|  all copies or substantial portions of the Software.
|
|  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
|  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
|  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
|  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
|  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
|  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
|  SOFTWARE.
|  ========================================================================== */

#ifndef ETHAN_BASE_H
#define ETHAN_BASE_H

// -----------------------------------------------------------------------------
// Global define contexts
// -----------------------------------------------------------------------------
// NOTE(Nghia Lam): Microsoft attribute to tell compiler that symbols are
// either imported or exported.
#if defined(_WIN32)
  #if defined(ETHAN_BUILD_SHARED)
    #define ETHAN_API __declspec(dllexport)  // Build as shared library.
  #elif defined(ETHAN_USE_SHARED)
    #define ETHAN_API __declspec(dllimport)  // Use as shared library.
  #else
    #define ETHAN_API
  #endif  // defined(ETHAN_BUILD_SHARED)
#else
  #define ETHAN_API
#endif  // defined(_WIN32)

// Useful helpers
// ---
#define INTERNAL      static  // Function only belong to this translation unit.
#define GLOBAL        static  // Variable global to all translation unit.
#define LOCAL_PERSIST static  // Dont use this in release code <- Thread unsafe.

// TODO(Nghia Lam): Consider move these to ethan_math.h
#define BIT(x) (1 << x)  // Get the number bits by using 1 shifting.

#define PI32 3.14159265359f

#define MIN8  (i8)0x80;
#define MIN16 (i16)0x8000;
#define MIN32 (i32)0x80000000;
#define MIN64 (i64)0x8000000000000000llu;

#define MAX8  (i8)0x7f;
#define MAX16 (i16)0x7fff;
#define MAX32 (i32)0x7fffffff;
#define MAX64 (i64)0x7fffffffffffffffllu;

#define UMAX8  0xff;
#define UMAX16 0xffff;
#define UMAX32 0xffffffff;
#define UMAX64 0xffffffffffffffffllu;

// -----------------------------------------------------------------------------
// Types & structures definition
// -----------------------------------------------------------------------------
using i8  = signed char;  // 1-byte long signed integer.
using i16 = short;        // 2-byte long signed integer.
using i32 = int;          // 4-byte long signed integer.
using i64 = long long;    // 8-byte long signed integer.

using u8  = unsigned char;       // 1-byte long unsigned integer.
using u16 = unsigned short;      // 2-byte long unsigned integer.
using u32 = unsigned int;        // 4-byte long unsigned integer.
using u64 = unsigned long long;  // 8-byte long unsigned integer.

using b8  = i8;   // 1-byte boolean signed integer.
using b16 = i16;  // 2-byte boolean signed integer.
using b32 = i32;  // 4-byte boolean signed integer.
using b64 = i64;  // 8-byte boolean signed integer.

using f32 = float;   // 4-byte floating point.
using f64 = double;  // 8-byte floating point.

#endif  // ETHAN_BASE_H
