#ifndef _ETHAN_CORE_APP_H_
#define _ETHAN_CORE_APP_H_

namespace ethan {

class Application {
public:
  Application();
  virtual ~Application();

  /**
   * Run before starting the app, can be use for pre-hack settings
   */
  virtual void Init();

  /**
   * Run once the app is started, can be used for default settings
   */
  virtual void Start();

  /**
   * Run when the app is terminated, can be used for final GC. Helping our OS
   * cleaner is always a good practice.
   */
  virtual void End();
};

} // namespace ethan

#endif // _ETHAN_CORE_APP_H_
