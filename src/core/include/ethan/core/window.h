#ifndef _ETHAN_CORE_WINDOW_H_
#define _ETHAN_CORE_WINDOW_H_

namespace ethan {

struct WindowProperty {
  const char *title;
  unsigned int width;
  unsigned int height;

  WindowProperty(const char *_title = "Ethan Engine",
                 unsigned int _width = 1600, unsigned int _height = 900)
      : title(_title), width(_width), height(_height) {}
};

class Window {
 public:
  virtual ~Window() = default;

  /// Windows API
  /**
   * Update once per frame, used for pulling events from our application.
   */
  virtual void OnUpdate() = 0;

  virtual unsigned int GetWidth() const = 0;
  virtual unsigned int GetHeight() const = 0;

  virtual void SetVSync(bool enabled) = 0;
  virtual bool IsVSync() const = 0;

  static Window *CreateWindow(const WindowProperty &props = WindowProperty());
};

} // namespace ethan

#endif // _ETHAN_CORE_WINDOW_H_
