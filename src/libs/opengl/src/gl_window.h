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
 * @file gl_window.h
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

#ifndef _ETHAN_LIB_GL_WINDOW_H_
#define _ETHAN_LIB_GL_WINDOW_H_

#include "ethan/core/graphic/window.h"
#include "gl_input.h"

namespace ethan {

class GLWindow : public Window {
 public:
  explicit GLWindow(const WindowProperty& props);
  virtual ~GLWindow();

  void OnUpdate() override;

  [[nodiscard]] unsigned int GetWidth() const override { return data_.width; }
  [[nodiscard]] unsigned int GetHeight() const override { return data_.height; }
  [[nodiscard]] bool IsVSync() const override { return data_.vsync; }
  [[nodiscard]] bool IsClose() const override { return is_close_; }
  [[nodiscard]] void* GetNativeWindow() const override { return window_; }

  void SetVSync(bool enabled) override;
  void SetWindowResizeCallback() override;
  void SetWindowCloseCallback() override;
  void SetEventCallback(std::function<void(Event &)> event_func) override;

  void HandleEvent(WindowEvent &event) override;
  void Close() override;
  void Resize(unsigned int width, unsigned int height) override;

  struct WindowData {
    const char* title;
    unsigned int width, height;
    bool vsync;

    std::function<void(Event&)> event_callback;
  };

 private:
  WindowData data_;
  std::unique_ptr<GLInput> input_;
  GLFWwindow* window_;

  static bool is_glfw_init_;
  bool is_close_;

  void Init(const WindowProperty& props);
  static void SetErrorCallBack(int error, const char* description);
};

}

#endif // _ETHAN_LIB_GL_WINDOW_H_
