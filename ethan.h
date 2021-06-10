/* ==========================================================================
|  @File   : ethan.h
|  @Brief  : Main header of Ethan.
|  @Author : Nghia Lam <nghialam12795@gmail.com>
|  ---
|
|  TODO(Nghia Lam):
|    - [ ] Setup new base structure for ethan.
|    - [ ] Find a good structure for our cross-platform entry point.
|    - [ ] Initialize the window.
|
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

#ifndef ETHAN_H
#define ETHAN_H

// -----------------------------------------------------------------------------
// Global define contexts
// -----------------------------------------------------------------------------
#define ETHAN_VERSION "0.0.1"

// Using single define for Windows
#if !defined(_WIN32) && (defined(__WIN32__) || defined(WIN32) ||               \
                         defined(__MINGW32__) || defined(__CYGWIN__))
  #define _WIN32
#endif

// -----------------------------------------------------------------------------
// Ethan sources
// -----------------------------------------------------------------------------
#include "code/ethan_base.h"
#include "code/ethan_audio.h"

// NOTE(Nghia Lam): This file will always be at the bottom of the file as it
// contains many implementations of different platforms.
#include "code/ethan_config.h"

#endif  // ETHAN_H
