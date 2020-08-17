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

#ifndef ETHAN_CORE_EVENT_H_
#define ETHAN_CORE_EVENT_H_

#include <string>

#define BIT(x) (1 << x)
#define EVENT_CLASS(type)                                                      \
  virtual const char *GetName() const override { return #type; }

namespace Ethan {

enum class EventCategory {
  NONE = 0,
  APPLICATION = BIT(0),
  INPUT = BIT(1),
  KEYS = BIT(2),
  MOUSE = BIT(3)
};

class Event {
 public:
  virtual ~Event() = default;

  [[nodiscard]] virtual const char *GetName() const = 0;
  [[nodiscard]] virtual bool IsHandled() const { return handled_; }
  [[nodiscard]] virtual EventCategory GetCategory() const { return category_; }
  [[nodiscard]] virtual std::string ToString() const { return GetName(); }

  void SetHandled(bool handled) { handled_ = handled; }
  void SetCategory(EventCategory category) { category_ = category; }

  /**
   * Determine if an event is belong to an Event Category
   * @param category - EventCategory
   * @return bool
   */
  bool IsInCategory(EventCategory category) { return category_ == category; }

 private:
  bool handled_;
  EventCategory category_;
};

} // namespace Ethan

#endif // ETHAN_CORE_EVENT_H_
