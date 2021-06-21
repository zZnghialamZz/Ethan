/* ==========================================================================
|  @File   : ethan_win.h
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

#ifndef ETHAN_WIN_H
#define ETHAN_WIN_H

#include <windows.h>
#include <dsound.h>
#include <xinput.h>

// ----------------------------------------------------------------------------
// Define global contexts
// ----------------------------------------------------------------------------

// NOTE(Nghia Lam): Similar to xinput.h, dsound.h is different on each machine
// depend on the Windows driver. So we will need to load the library by hand,
// not linking directy (The game wont load if it cannot find the driver). But it
// will be a bit overkill if we implement it exactly like the xinput since it
// will be only used once right after the application startup, so we only:
//   - Define the function macros
//   - Define type of the functions, so we can use the function as a pointer
// ---
// DirectSoundCreate
#define DIRECT_SOUND_CREATE(name)                                              \
  HRESULT WINAPI name(LPCGUID pcGuidDevice,                                    \
                      LPDIRECTSOUND* ppDS,                                     \
                      LPUNKNOWN pUnkOuter);
typedef DIRECT_SOUND_CREATE(DSoundCreate);

// ----------------------------------------------------------------------------
// Types & structure definition
// ----------------------------------------------------------------------------

// Main
// ---

struct Win32OffScreenBuffer {
  BITMAPINFO Info;  // The information of the device independent bitmap.
  void* Memory;     // The memory area for the bitmap.
  int Width;        // The width of our bitmap area.
  int Height;       // The height of our bitmap area.
  int Pitch;        // The range of the bitmap's width in bytes.
  int BytePerPixel;
};

// ---

// Audio
// ---

struct Win32SoundOutput {
  int SampleRate;          // How many samples can be played per second.
  int BytesPerSample;      // The size of our sample in byte.
  int SecondBufferSize;    // The buffer of our secondary buffer for sound.
  int ToneHz;              // Determine our tone, in Hertz.
  int ToneVolume;          // Our sound pitch.
  int WavePeriod;          // Determine the wave length of our wave.
  u32 RunningSampleIndex;  // Keep track of the samples we write.
  f32 TSine;               // TSine value for our sine wave.
  int LatencySampleCount;  // How much ahead of the cursor we want to be.
};

// ---

// ----------------------------------------------------------------------------
// Global variables
// ----------------------------------------------------------------------------

GLOBAL IDirectSoundBuffer* win32_audio_buffer;  // The second sound buffer.

// ----------------------------------------------------------------------------
// Win32 API declaration
// ----------------------------------------------------------------------------

// Main
// ---

// ---

// Audio
// ---

/**
 * Initialize the dsound library on Windows. Then also create the wave format,
 * which also defines the sound format and finally create the global sound
 * buffer.
 *
 * @param window - Our window handler on Windows.
 * @param sample_rate - The samples that can be played per second.
 * @param buffer_size - The size of our global sound buffer.
 * */
ETHAN_API void Win32InitDSound(HWND window, i32 sample_rate, i32 buffer_size);

/**
 * Fill the primary sound buffer with our global audio buffer (we use as a
 * second buffer for our cycle method).
 *
 * @param sound_output - The actual sound settings we want to output.
 * @param byte_to_lock - The region we want to lock for writing.
 * @param byte_to_write - The actual region we gonna write the sound.
 * */
ETHAN_API void Win32FillSoundBuffer(Win32SoundOutput* sound_output,
                                    DWORD byte_to_lock,
                                    DWORD bytes_to_write);

// ---

// -----------------------------------------------------------------------------
// Windows API Implementation
// -----------------------------------------------------------------------------
#include "ethan_win_main.cpp"
#include "ethan_win_audio.cpp"
#include "ethan_win_input.cpp"

#endif  // ETHAN_WIN_H
