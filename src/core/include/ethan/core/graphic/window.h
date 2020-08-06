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
 * @file window.h
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

#ifndef _ETHAN_CORE_WINDOW_H_
#define _ETHAN_CORE_WINDOW_H_

#include "ethan/core/main/event.h"

namespace ethan {

/// -------------------------------------------
/// --- Events
/// -------------------------------------------
enum WindowEventType {
  kWindowResizeEvent,
  kWindowCloseEvent
};

class WindowEvent : public Event {
 public:
  virtual ~WindowEvent() = default;
  [[nodiscard]] virtual WindowEventType GetEventType() const = 0;
};

class WindowResizeEvent : public WindowEvent {
 public:
  WindowResizeEvent(unsigned int width, unsigned int height);

  [[nodiscard]] WindowEventType GetEventType() const override {
    return kWindowResizeEvent;
  }
  [[nodiscard]] unsigned int GetWidth() const { return width_; }
  [[nodiscard]] unsigned int GetHeight() const { return height_; }
  [[nodiscard]] std::string ToString() const override;

  EVENT_CLASS(WindowResize);

 private:
  unsigned int width_;
  unsigned int height_;
};

class WindowCloseEvent : public WindowEvent {
 public:
  WindowCloseEvent();

  [[nodiscard]] WindowEventType GetEventType() const override {
    return kWindowCloseEvent;
  }

  EVENT_CLASS(WindowClose);
};

/// -------------------------------------------
/// --- Main Window API
/// -------------------------------------------

struct WindowProperty {
  const char *title;
  unsigned int width;
  unsigned int height;

  explicit WindowProperty(const char *_title = "Ethan Engine",
                          unsigned int _width = 1600,
                          unsigned int _height = 900)
      : title(_title), width(_width), height(_height) {}
};

class Window {
 public:
  virtual ~Window() = default;

  /**
   * Update once per frame, used for pulling events from our application.
   */
  virtual void OnUpdate() = 0;

  [[nodiscard]] virtual unsigned int GetWidth() const = 0;
  [[nodiscard]] virtual unsigned int GetHeight() const = 0;
  [[nodiscard]] virtual bool IsVSync() const = 0;
  [[nodiscard]] virtual bool IsClose() const = 0;

  virtual void SetVSync(bool enabled) = 0;
  virtual void SetWindowResizeCallback() = 0;
  virtual void SetWindowCloseCallback() = 0;
  virtual void SetEventCallback(std::function<void(Event&)> event_func) = 0;

  virtual void ProcessEvent(WindowEvent& event) = 0;
  virtual void Close() = 0;
  virtual void Resize(unsigned int width, unsigned int height) = 0;

  static Window *CreateWindow(const WindowProperty &props = WindowProperty());
};

} // namespace ethan

#endif // _ETHAN_CORE_WINDOW_H_
