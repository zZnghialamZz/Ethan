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
 * @file camera_controller.cpp
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

#include "ethan/core/graphic/camera/camera_controller.h"
#include "ethan/core/main/application.h"

namespace Ethan {

CameraController::CameraController(Window *parent,
                                   const Shared<Camera> &camera,
                                   const CameraData &data)
    : parent_(parent)
    , camera_(camera)
    , data_(data)
    , target_pos_(camera->GetPosition()) {}

CameraController::CameraController(const CameraData &data)
    : data_(data)
    , parent_(&Application::ME().GetMainWindow())
    , target_pos_(0.0f) {}

CameraController::CameraController(const Shared<Camera> &camera,
                                   const CameraData &data)
    : camera_(camera)
    , data_(data)
    , parent_(&Application::ME().GetMainWindow())
    , target_pos_(camera->GetPosition()) {}

void CameraController::UpdateCamera(float dt) {

  switch (camera_->GetCameraMode()) {
    case CameraMode::CAMERA_CUSTOM: {
      UpdateCustomCamera(dt);
      break;
    }
    case CameraMode::CAMERA_2D: {
      UpdateCamera2D(dt);
      break;
    }
    case CameraMode::CAMERA_FREE: {
      UpdateCameraFree(dt);
      break;
    }
    case CameraMode::CAMERA_FPS: {
      UpdateCameraFPS(dt);
      break;
    }
    case CameraMode::CAMERA_THIRD: {
      UpdateCameraThirdView(dt);
      break;
    }
  }

}

void CameraController::UpdateCamera(const Shared<Camera> &camera, float dt) {
  camera_ = camera;
  UpdateCamera(dt);
}

void CameraController::EventCall(Event &event) {
  if (event.GetCategory() == EventCategory::MOUSE) {
    HandleEvent((MouseEvent&)event);
    event.SetHandled(true);
  } else if (event.GetCategory() == EventCategory::APPLICATION) {
    HandleEvent((WindowEvent&)event);
    event.SetHandled(true);
  }
}

void CameraController::HandleEvent(MouseEvent &event) {
  if (event.GetMouseEventType() == MouseEventType::MOUSE_SCROLLED_EVENT) {
    float zoom = camera_->GetZoomLevel();
    if (parent_->GetInputSystem()->IsKeyPressed(data_.SmoothZoomKey))
      zoom -= ((MouseScrolledEvent &) event).GetYOffset()
          * CAMERA_MOUSE_SCROLL_SENSITIVITY
          * CAMERA_SMOOTH_ZOOM_SENSITIVITY;
    else
      zoom -= ((MouseScrolledEvent&)event).GetYOffset()
          * CAMERA_MOUSE_SCROLL_SENSITIVITY;

    // Clamp
    zoom = std::max(zoom, CAMERA_DISTANCE_MIN_CLAMP);
    zoom = std::min(zoom, CAMERA_DISTANCE_MAX_CLAMP);

    camera_->SetZoomLevel(zoom);
  }
}

void CameraController::HandleEvent(WindowEvent &event) {
  if (event.GetEventType() == WindowEventType::kWindowResizeEvent) {
    float width = (float) ((WindowResizeEvent &) event).GetWidth();
    float height = (float) ((WindowResizeEvent &) event).GetHeight();

    switch (camera_->GetCameraMode()) {
      case CameraMode::CAMERA_CUSTOM:
        break;
      case CameraMode::CAMERA_2D: {
        float aspect_ratio = width / height;
        camera_->SetAspectRatio(aspect_ratio);
        break;
      }
      case CameraMode::CAMERA_FREE:
        break;
      case CameraMode::CAMERA_FPS:
        break;
      case CameraMode::CAMERA_THIRD:
        break;
    }
  }
}

void CameraController::SetCurrentCamera(const Shared<Camera> &camera) {
  camera_ = camera;
  target_pos_ = {
      camera->GetPosition().x,
      camera->GetPosition().y,
      camera->GetPosition().z
  };
}

void CameraController::SetMoveKeys(Key front,
                                   Key back,
                                   Key left,
                                   Key right,
                                   Key up,
                                   Key down) {
  data_.MoveKey[CameraMove::FRONT]  = front;
  data_.MoveKey[CameraMove::BACK]   = back;
  data_.MoveKey[CameraMove::LEFT]   = left;
  data_.MoveKey[CameraMove::RIGHT]  = right;
  data_.MoveKey[CameraMove::UP]     = up;
  data_.MoveKey[CameraMove::DOWN]   = down;
}

void CameraController::SetSmoothZoomKey(Key key) {
  data_.SmoothZoomKey = key;
}

void CameraController::SetAlterKey(Key key) {
  data_.AlterKey = key;
}

void CameraController::SetPanKey(InputCode key) {
  data_.PanKey = key;
}

void CameraController::UpdateCamera2D(float dt) {
  // Calculate mouse delta
  glm::vec2 mouse_pos {
      parent_->GetInputSystem()->GetMouseX(),
      parent_->GetInputSystem()->GetMouseY()
  };
  glm::vec2 mouse_delta = mouse_pos - previous_mouse_pos_;
  previous_mouse_pos_ = mouse_pos;

  bool pan = (data_.PanKey.index() == 0)
             ? parent_->GetInputSystem()->IsKeyPressed(std::get<Key>(data_.PanKey))
             : parent_->GetInputSystem()->IsMouseButtonPressed(std::get<Mouse>(data_.PanKey));
  bool alt = parent_->GetInputSystem()->IsKeyPressed(data_.AlterKey);

  if (pan && alt) {
    target_pos_.x -= mouse_delta.x * CAMERA_MOUSE_SENSITIVITY * dt;
    target_pos_.y += mouse_delta.y * CAMERA_MOUSE_SENSITIVITY * dt;

    camera_->SetPosition(target_pos_);
  }
}

void CameraController::UpdateCameraFree(float dt) {

}

// TODO: Support these camera modes
void CameraController::UpdateCameraFPS(float dt) {}
void CameraController::UpdateCameraThirdView(float dt) {}
void CameraController::UpdateCustomCamera(float dt) {}

}