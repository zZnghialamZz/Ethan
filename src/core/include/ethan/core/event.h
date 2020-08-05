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
 * @file event.h
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

#ifndef _ETHAN_CORE_EVENT_H_
#define _ETHAN_CORE_EVENT_H_

#include <string>

#define BIT(x) (1 << x)
#define EVENT_CLASS(type)                                                      \
  virtual const char *GetName() const override { return #type; }

namespace ethan {

enum EventCategory {
  None = 0,
  ApplicationEvent = BIT(0),
  KeyboardEvent = BIT(1),
  MouseEvent = BIT(2)
};

class Event {
 public:
  virtual ~Event() = default;

  [[nodiscard]] virtual const char *GetName() const = 0;
  [[nodiscard]] virtual bool IsHandled() const { return handled_; }
  [[nodiscard]] virtual int GetCategory() const { return category_; }
  [[nodiscard]] virtual std::string ToString() const { return GetName(); }

  void SetHandled(bool handled) { handled_ = handled; }
  void SetCategory(EventCategory category) { category_ = category; }

  /**
   * Determine if an event is belong to an Event Category
   * @param category - EventCategory
   * @return bool
   */
  bool IsInCategory(EventCategory category) { return category_ & category; }

 private:
  bool handled_;
  EventCategory category_;
};

class EventManager {
 public:
  EventManager();
  virtual ~EventManager();

  template<typename T, typename F>
  bool Dispatch(const F &func);
};

/**
 * Output the value of the event to the console, use mainly for debug & logging
 * purpose
 * @param os - std::ostream
 * @param event - Event
 * @return overload for operator <<
 */
inline std::ostream &operator<<(std::ostream &os, const Event &event) {
  return os << event.ToString();
}

}

#endif // _ETHAN_CORE_EVENT_H_
