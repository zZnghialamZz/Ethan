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
 * @file keycode.h
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

#ifndef ETHAN_CORE_INPUT_KEYCODE_H_
#define ETHAN_CORE_INPUT_KEYCODE_H_

#include "ethan/core/main/event.h"

namespace Ethan {

/// -------------------------------------------
/// --- Main Keys API
/// -------------------------------------------

typedef enum class KeyCode : uint16_t {
  Unknown             = 0,

  A                   = 'A',
  B                   = 'B',
  C                   = 'C',
  D                   = 'D',
  E                   = 'E',
  F                   = 'F',
  G                   = 'G',
  H                   = 'H',
  I                   = 'I',
  J                   = 'J',
  K                   = 'K',
  L                   = 'L',
  M                   = 'M',
  N                   = 'N',
  O                   = 'O',
  P                   = 'P',
  Q                   = 'Q',
  R                   = 'R',
  S                   = 'S',
  T                   = 'T',
  U                   = 'U',
  V                   = 'V',
  W                   = 'W',
  X                   = 'X',
  Y                   = 'Y',
  Z                   = 'Z',

  Num0                = '0',
  Num1                = '1',
  Num2                = '2',
  Num3                = '3',
  Num4                = '4',
  Num5                = '5',
  Num6                = '6',
  Num7                = '7',
  Num8                = '8',
  Num9                = '9',

  Minus               = '-',
  Equals              = '=',
  LeftBracket         = '[',
  RightBracket        = ']',
  Backslash           = '\\',
  Semicolon           = ';',
  Apostrophe          = '\'',
  Grave               = '`',
  Comma               = ',',
  Period              = '.',
  Slash               = '/',

  World1              = 161, /* non-US #1 */
  World2              = 162, /* non-US #2 */

  /* Function keys */
  Space               = 32,

  Enter               = 257,
  Tab                 = 258,
  Backspace           = 259,
  Insert              = 260,
  Delete              = 261,

  Right               = 262,
  Left                = 263,
  Down                = 264,
  Up                  = 265,

  PageUp              = 266,
  PageDown            = 267,
  Home                = 268,
  End                 = 269,

  CapsLock            = 280,
  ScrollLock          = 281,
  NumLock             = 282,

  PrintScreen         = 283,
  Pause               = 284,

  F1                  = 290,
  F2                  = 291,
  F3                  = 292,
  F4                  = 293,
  F5                  = 294,
  F6                  = 295,
  F7                  = 296,
  F8                  = 297,
  F9                  = 298,
  F10                 = 299,
  F11                 = 300,
  F12                 = 301,
  F13                 = 302,
  F14                 = 303,
  F15                 = 304,
  F16                 = 305,
  F17                 = 306,
  F18                 = 307,
  F19                 = 308,
  F20                 = 309,
  F21                 = 310,
  F22                 = 311,
  F23                 = 312,
  F24                 = 313,
  F25                 = 314,

  /* Keypad */
  Keypad0             = 320,
  Keypad1             = 321,
  Keypad2             = 322,
  Keypad3             = 323,
  Keypad4             = 324,
  Keypad5             = 325,
  Keypad6             = 326,
  Keypad7             = 327,
  Keypad8             = 328,
  Keypad9             = 329,
  KeypadDecimal       = 330,
  KeypadDivide        = 331,
  KeypadMultiply      = 332,
  KeypadSubtract      = 333,
  KeypadAdd           = 334,
  KeypadEnter         = 335,
  KeypadEqual         = 336,

  LeftShift           = 340,
  LeftControl         = 341,
  LeftAlt             = 342,
  LeftSuper           = 343,
  RightShift          = 344,
  RightControl        = 345,
  RightAlt            = 346,
  RightSuper          = 347,
  Menu                = 348
} Key;

inline std::ostream& operator<<(std::ostream& os, Key keycode) {
  os << static_cast<int32_t>(keycode);
  return os;
}

enum class KeyMods {
  None              = 0,
  Shift             = 1,
  Ctrl              = 2,
  CtrlShift         = Ctrl  | Shift,
  Alt               = 4,
  ShiftAlt          = Shift | Alt,
  CtrlAlt           = Ctrl  | Alt,
  CtrlShiftAlt      = Ctrl  | Shift | Alt,
  Mod               = 8,
  ShiftMod          = Shift | Mod,
  CtrlMod           = Ctrl  | Mod,
  CtrlShiftMod      = Ctrl  | Shift | Mod,
  AltMod            = Alt   | Mod,
  ShiftAltMod       = Shift | Alt   | Mod,
  CtrlAltMod        = Ctrl  | Alt   | Mod,
  CtrlShiftAltMod   = Ctrl  | Shift | Alt  | Mod,
};

/// -------------------------------------------
/// --- Events
/// -------------------------------------------
enum KeyEventType {
  kKeyPressedEvent,
  kKeyReleasedEvent
};

class KeyEvent : public Event {
 public:
  explicit KeyEvent(KeyCode keycode);
  [[nodiscard]] KeyCode GetKeyCode() const { return keycode_; }
  [[nodiscard]] virtual KeyEventType GetKeyEventType() const = 0;

 private:
  KeyCode keycode_;
};

class KeyPressedEvent : public KeyEvent {
 public:
  KeyPressedEvent(KeyCode keycode, int repeat);
  [[nodiscard]] int GetRepeatCount() const { return repeat_; }
  [[nodiscard]] std::string ToString() const override;
  [[nodiscard]] KeyEventType GetKeyEventType() const override {
    return kKeyPressedEvent;
  }

  EVENT_CLASS(KeyPressed);

 private:
  int repeat_;
};

class KeyReleasedEvent : public KeyEvent {
 public:
  explicit KeyReleasedEvent(KeyCode keycode);
  [[nodiscard]] std::string ToString() const override;
  [[nodiscard]] KeyEventType GetKeyEventType() const override {
    return kKeyReleasedEvent;
  }

  EVENT_CLASS(KeyReleased);
};

} // namespace Ethan

#endif // ETHAN_CORE_INPUT_KEYCODE_H_
