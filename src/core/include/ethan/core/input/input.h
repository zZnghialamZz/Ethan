/**
 * ==================================================
 *      _____
 *   __|___  |__    __    __   _  ____    ____   _
 *  |   ___|    | _|  |_ |  |_| ||    \  |    \ | |
 *  |   ___|    ||_    _||   _  ||     \ |     \| |
 *  |______|  __|  |__|  |__| |_||__|\__\|__/\____|
 *     |_____|
 *
 *                   Game Engine
 * ==================================================
 *
 * @file input.h
 * @author Nghia Lam <nghialam12795@gmail.com>
 *
 * @brief
 *
 * @license Copyright 2020 Nghia Lam
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ETHAN_CORE_INPUT_H_
#define ETHAN_CORE_INPUT_H_

#include "keys.h"
#include "mouse.h"

#include <variant>

namespace Ethan {

//------------------------------------------------------------------------------
// Type & Structure Definition
//------------------------------------------------------------------------------

/**
 * Used when there is an input that allow two different code.
 * Key first, Mouse second. This order is important.
 */
using InputCode = std::variant<Key, Mouse>;

//------------------------------------------------------------------------------
// Input Class Object
//------------------------------------------------------------------------------
class Input {
 public:
  virtual ~Input() = default;

  virtual bool IsKeyHeld(Key keycode) = 0;
  virtual bool IsKeyPressed(Key keycode) = 0;
  virtual bool IsKeyReleased(Key keycode) = 0;
  virtual bool IsMouseButtonPressed(Mouse mouse_code) = 0;
  virtual bool IsMouseButtonReleased(Mouse mouse_code) = 0;

  virtual std::pair<float, float> GetMousePosition() = 0;
  virtual float GetMouseX() = 0;
  virtual float GetMouseY() = 0;

  virtual void SetKeyCallback() = 0;
  virtual void SetMouseCallback() = 0;
};

} // namespace Ethan

#endif // ETHAN_CORE_INPUT_H_
