#ifndef _ETHAN_LIB_GL_WINDOW_H_
#define _ETHAN_LIB_GL_WINDOW_H_

#include "ethan/core/window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace ethan {

class GLWindow : public Window {
 public:
  GLWindow(const WindowProperty& props);
  virtual ~GLWindow();

  void OnUpdate() override;

  unsigned int GetWidth() const override { return data_.width; }
  unsigned int GetHeight() const override { return data_.height; }

  void SetVSync(bool enabled) override;
  bool IsVSync() const override { return data_.vsync; }

 private:
  struct WindowData {
    const char* title;
    unsigned int width, height;
    bool vsync;
  };

  WindowData data_;
  GLFWwindow* window_;

  static bool is_glfw_init_;

  virtual void Init(const WindowProperty& props);
  virtual void ShutDown();
};

}

#endif // _ETHAN_LIB_GL_WINDOW_H_
