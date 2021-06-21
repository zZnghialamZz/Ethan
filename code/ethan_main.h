/* ==========================================================================
|  @File   : ethan_main.h
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

#ifndef ETHAN_MAIN_H
#define ETHAN_MAIN_H

// ----------------------------------------------------------------------------
// Types & structure definition
// ----------------------------------------------------------------------------
struct WindowDimension {
  int Width;
  int Height;
};

// ----------------------------------------------------------------------------
// Main audio API
// ----------------------------------------------------------------------------

/**
 * Initialize the Window based on the current OS and settings.
 *
 * @param width  - The width of the main Window.
 * @param height - The height of the main Window.
 * @param title  - The title of the main Window.
 * */
ETHAN_API void InitWindow(int width, int height, const char* title);

/**
 * Find the `WindowDimension` of current main Window.
 *
 * @return WindowDimension
 * */
ETHAN_API WindowDimension GetWindowDimension();

#endif  // ETHAN_MAIN_H
