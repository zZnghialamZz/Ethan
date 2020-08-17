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
 * @file camera_controller.h
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

#ifndef ETHAN_CORE_GRAPHIC_CAMERA_CONTROLLER_H_
#define ETHAN_CORE_GRAPHIC_CAMERA_CONTROLLER_H_

#include "camera.h"
#include "ethan/core/input/input.h"

namespace Ethan {

//------------------------------------------------------------------------------
// Macros
//------------------------------------------------------------------------------

#define CAMERA_MOUSE_MOVE_SENSITIVITY              0.003f
#define CAMERA_MOUSE_SCROLL_SENSITIVITY            0.5f
#define CAMERA_MOUSE_SENSITIVITY                   0.09f

#define CAMERA_DISTANCE_MIN_CLAMP                  0.1f
#define CAMERA_DISTANCE_MAX_CLAMP                  120.0f
#define CAMERA_MIN_CLAMP                           85.0f
#define CAMERA_MAX_CLAMP                         (-85.0f)
#define CAMERA_SMOOTH_ZOOM_SENSITIVITY             0.05f
#define CAMERA_PANNING_DIVIDER                     5.1f

//------------------------------------------------------------------------------
// Type & Structure Definition
//------------------------------------------------------------------------------
typedef enum : uint8_t {
  FRONT = 0,
  BACK,
  LEFT,
  RIGHT,
  UP,
  DOWN
} CameraMove;

struct CameraData {
  // Camera Movement control keys.
  Key MoveKey[6];       // Same order of CameraMove
  Key SmoothZoomKey;    // Smooth Zoom Key
  Key AlterKey;         // Alternative Key
  InputCode PanKey;     // Pan view Key
};

//------------------------------------------------------------------------------
// Default Variables Definition
//------------------------------------------------------------------------------
static CameraData CAMERA = {
    .MoveKey = { Key::E, Key::Q, Key::A, Key::D, Key::W, Key::S },
    .SmoothZoomKey = Key::LeftControl,
    .AlterKey = Key::LeftAlt,
    .PanKey = Mouse::ButtonLeft
};

//------------------------------------------------------------------------------
// Main Class Object
//------------------------------------------------------------------------------
class Application;
class Window;

class CameraController {
 public:
  CameraController(Window *parent,
                   const Shared<Camera> &camera,
                   const CameraData &data = CAMERA);
  explicit CameraController(const CameraData& data = CAMERA);
  explicit CameraController(const Shared<Camera>& camera, const CameraData& data = CAMERA);
  virtual ~CameraController() = default;

  void UpdateCamera(float dt);
  void UpdateCamera(const Shared<Camera>& camera, float dt);

  void HandleEvent(MouseEvent& event);
  void EventCall(Event& event);

  [[nodiscard]] Shared<Camera> GetCurrentCamera() const { return camera_; }

  void SetCurrentCamera(const Shared<Camera>& camera);
  void SetMoveKeys(Key front, Key back, Key left, Key right, Key up, Key down);
  void SetSmoothZoomKey(Key key);
  void SetAlterKey(Key key);
  void SetPanKey(InputCode key);

 private:
  // --- Private members
  CameraData data_;
  Shared<Camera> camera_;

  Window* parent_;

  glm::vec3 target_pos_;
  glm::vec2 previous_mouse_pos_ = { 0.0f, 0.0f };

  // --- Private Method
  void UpdateCamera2D(float dt);
  void UpdateCameraFree(float dt);
  void UpdateCameraFPS(float dt);
  void UpdateCameraThirdView(float dt);
  void UpdateCustomCamera(float dt);
};

}

#endif // ETHAN_CORE_GRAPHIC_CAMERA_CONTROLLER_H_
