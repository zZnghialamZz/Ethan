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
 * @file camera.cpp
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

#include "ethan/core/graphic/camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace ethan {

Camera::Camera(CameraProjection projection)
    : projection_(projection)
    , near_plane_(0.1f)
    , far_plane_(100.0f)
    , fov_(45.0f)
    , position_(0.0f)
    , rotation_(0.0f)
    , view_matrix_(1.0f)
    , viewport_(1600.0f, 900.0f) {

  UpdateProjectionMatrix();

}

Camera::~Camera() = default;

void Camera::SetProjection(CameraProjection projection) {
  projection_ = projection;
  UpdateProjectionMatrix();
}

void Camera::SetPosition(const glm::vec3 &position) {
  position_ = position;
  UpdateViewMatrix();
}

void Camera::SetRotation(const glm::vec3 &rotation) {
  rotation_ = rotation;
  UpdateViewMatrix();
}

void Camera::SetClippingPlanes(float near_plane, float far_plane) {
  near_plane_ = near_plane;
  far_plane_ = far_plane;

  UpdateProjectionMatrix();
}

void Camera::SetFieldOfViewDegree(float degree) {
  fov_ = degree;

  UpdateProjectionMatrix();
}

void Camera::SetViewport(const glm::vec2 &viewport) {
  viewport_ = viewport;

  UpdateProjectionMatrix();
}

void Camera::UpdateProjectionMatrix() {
  switch (projection_) {
    case CameraProjection::kOrthographic: {
      projection_matrix_ = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
      break;
    }
    case CameraProjection::kPerspective: {
      projection_matrix_ = glm::perspective(glm::radians(fov_),
                                            viewport_.x/viewport_.y,
                                            near_plane_,
                                            far_plane_);
      break;
    }
  }

  vp_matrix_ = projection_matrix_ * view_matrix_;
}

void Camera::UpdateViewMatrix() {
  // TODO: Learn and replace a new formula for this rotation system.
  glm::mat4 transform = glm::translate(glm::mat4(1.0f), position_)
      * glm::rotate(glm::mat4(1.0f), glm::radians(rotation_.x), glm::vec3(1, 0, 0))
      * glm::rotate(glm::mat4(1.0f), glm::radians(rotation_.y), glm::vec3(0, 1, 0))
      * glm::rotate(glm::mat4(1.0f), glm::radians(rotation_.z), glm::vec3(0, 0, 1));

  view_matrix_ = glm::inverse(transform);

  vp_matrix_ = projection_matrix_ * view_matrix_;
}

}