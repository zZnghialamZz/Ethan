/* ==========================================================================
|  @File   : ethan_win_audio.cpp
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

#include "ethan_win_audio.h"

// TODO(Nghia Lam): Check if this is a global library can be used for cross
// platforms.
#include <math.h>

// ----------------------------------------------------------------------------
// Main audio API definitions
// ----------------------------------------------------------------------------

void OutputSound(Sound sound) {}

// ----------------------------------------------------------------------------
// Specific Win32 audio API definitions
// ----------------------------------------------------------------------------

void Win32InitDSound(HWND window, i32 sample_rate, i32 buffer_size) {
  // Load the library
  HMODULE dsound_lib = LoadLibraryA("dsound.dll");

  if (dsound_lib) {
    // Get the dsound object
    DSoundCreate* DirectSoundCreate =
        (DSoundCreate*)GetProcAddress(dsound_lib, "DirectSoundCreate");

    IDirectSound* DirectSound;
    if (DirectSoundCreate && SUCCEEDED(DirectSoundCreate(0, &DirectSound, 0))) {
      // Init the wave format for sound format
      // ---
      // NOTE(Nghia Lam):
      //   - wFormatTag: the format of the wave-form audio. We are working
      //   with the PCM method(i.e Pulse-Code Modulation).
      //   - nChannels: we want to support stereo format so it shoule be 2.
      //   - nSamplesPerSec: we set it to be passed as a parameters.
      //   - wBitsPerSample: we want 16 bits per channel (CD quality).
      //   - nBlockAlign: How many bytes are there per unit of samples.
      //     + Since we pass two channels in Left-Right sequences, we can
      //     simply compute nChannels times wBitsPerSample, divided by the
      //     number of bits in a byte (8).
      //   - nAvgBytesPerSec: How many bytes will the samples occupy in one
      //   second.
      //   - cbSize: Size of any extra information we want to pass. We dont
      //   have any so set it to 0.
      WAVEFORMATEX wave_format   = {};
      wave_format.wFormatTag     = WAVE_FORMAT_PCM;
      wave_format.nChannels      = 2;
      wave_format.nSamplesPerSec = sample_rate;
      wave_format.wBitsPerSample = 16;
      wave_format.nBlockAlign =
          (wave_format.nChannels * wave_format.wBitsPerSample) / 8;
      wave_format.nAvgBytesPerSec =
          wave_format.nSamplesPerSec * wave_format.nBlockAlign;
      wave_format.cbSize = 0;

      // NOTE(Nghia Lam): Since we have to setup our sound format, we need to
      // use DSSCL_PRIORITY.
      if (SUCCEEDED(DirectSound->SetCooperativeLevel(window, DSSCL_PRIORITY))) {
        // Create a primary buffer
        // ---
        // NOTE(Nghia Lam): First we clear all the settings of buffer
        // description to zero. Then, we only need to worry about two settings:
        //   - dwSize : size of the buffer desc.
        //   - dwFlags: a bit field. We use DSBCAPS_PRIMARYBUFFER as it
        //   identitfies the buffer as primary.
        DSBUFFERDESC buffer_description = {};  // Clear all settings to zero
        buffer_description.dwSize       = sizeof(buffer_description);
        buffer_description.dwFlags      = DSBCAPS_PRIMARYBUFFER;

        IDirectSoundBuffer* primary_buffer;
        if (SUCCEEDED(DirectSound->CreateSoundBuffer(&buffer_description,
                                                     &primary_buffer,
                                                     0))) {
          // Set the sound format
          if (SUCCEEDED(primary_buffer->SetFormat(&wave_format))) {
          }
        }
      }

      // Create a second buffer with different description
      // NOTE(Nghia Lam): Here is some change compare to the primary buffer.
      //   - dwFlags: Since we dont really need anything, leave it as 0.
      //   - dwBufferBytes: buffer size, we pass this as a parameter.
      //   - lpwfxFormat: we dont really need to set the format again, just pass
      //   the address of the wave format to here.
      DSBUFFERDESC buffer_description  = {};  // Clear all settings to zero
      buffer_description.dwSize        = sizeof(buffer_description);
      buffer_description.dwBufferBytes = buffer_size;
      buffer_description.lpwfxFormat   = &wave_format;

      if (SUCCEEDED(DirectSound->CreateSoundBuffer(&buffer_description,
                                                   &global_audio_buffer,
                                                   0))) {
        // Start it playing!
        OutputDebugStringA("Secondary Buffer init successfully !!");
      }
    }
  }
}

void Win32FillSoundBuffer(Win32SoundOutput* sound_output,
                          DWORD byte_to_lock,
                          DWORD bytes_to_write) {
  VOID* region1;
  DWORD region1_size;
  VOID* region2;
  DWORD region2_size;

  // NOTE(Nghia Lam): Here is some notes for the parameters of the Lock
  // method:
  //   - dwWriteCursor: The starting address of our write pointer. Let's
  //   say we will have a certain ByteToLock which we will lock
  //   - dwWriteBytes: How many bytes we intend to write to, i.e. our
  //   “desired size”. Let's say we're going to write some BytesToWrite
  //   value that we will come up with later.
  //   - lplpvAudioPtr1, lpdwAudioBytes1: Address of a pointer and a
  //   size variable for the first region you will receive back.
  //   - lplpvAudioPtr2, lpdwAudioBytes2: Address of a pointer and a
  //   size variable for the potential second region, if any.
  //   - dwFlags: There a couple flags that we could pass here. We don't
  //   really need them, so just pass 0.
  if (SUCCEEDED(global_audio_buffer->Lock(byte_to_lock,    // Input
                                          bytes_to_write,  // Input
                                          &region1,        // Output
                                          &region1_size,   // Output
                                          &region2,        // Output
                                          &region2_size,   // Output
                                          0                // Input
                                          ))) {
    // TODO(Nghia Lam): Assert region1_size/region2_size are valid.
    i16* sample_out     = (i16*)region1;
    DWORD region1_count = region1_size / sound_output->BytesPerSample;
    for (DWORD index = 0; index < region1_count; ++index) {
      f32 sine_value   = sinf(sound_output->TSine);
      i16 sample_value = sine_value * sound_output->ToneVolume;
      *sample_out++    = sample_value;
      *sample_out++    = sample_value;
      sound_output->TSine += (2.f * PI32 * 1.f) / (f32)sound_output->WavePeriod;
      ++sound_output->RunningSampleIndex;
    }

    sample_out          = (i16*)region2;
    DWORD region2_count = region2_size / sound_output->BytesPerSample;
    for (DWORD index = 0; index < region2_count; ++index) {
      f32 sine_value   = sinf(sound_output->TSine);
      i16 sample_value = sine_value * sound_output->ToneVolume;
      *sample_out++    = sample_value;
      *sample_out++    = sample_value;
      sound_output->TSine += (2.f * PI32 * 1.f) / (f32)sound_output->WavePeriod;
      ++sound_output->RunningSampleIndex;
    }

    global_audio_buffer->Unlock(region1, region1_size, region2, region2_size);
  }
}
