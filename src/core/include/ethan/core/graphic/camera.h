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
 * @file camera.h
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

#ifndef ETHAN_CORE_MAIN_CAMERA_H_
#define ETHAN_CORE_MAIN_CAMERA_H_

namespace Ethan {

enum class CameraProjection : uint8_t {
  kOrthographic,
  kPerspective
};

class Camera {
 public:
  explicit Camera(CameraProjection projection = CameraProjection::kOrthographic);
  virtual ~Camera();

  [[nodiscard]] CameraProjection GetProjection() const { return projection_; }
  [[nodiscard]] float GetNearPlane() const { return near_plane_; }
  [[nodiscard]] float GetFarPlane() const { return far_plane_; }
  [[nodiscard]] float GetFieldOfViewDegree() const { return fov_; }
  [[nodiscard]] const glm::vec2 &GetViewport() const { return viewport_; }
  [[nodiscard]] const glm::vec3 &GetPosition() const { return position_; }
  [[nodiscard]] const glm::vec3 &GetRotation() const { return rotation_; }
  [[nodiscard]] const glm::mat4 &GetProjectionMatrix() const { return projection_matrix_; }
  [[nodiscard]] const glm::mat4 &GetViewMatrix() const { return view_matrix_; }
  [[nodiscard]] const glm::mat4 &GetViewProjectionMatrix() const { return vp_matrix_; }

  void SetFieldOfViewDegree(float degree);
  void SetViewport(const glm::vec2 &viewport);
  void SetProjection(CameraProjection projection);
  void SetClippingPlanes(float near_plane, float far_plane);
  void SetPosition(const glm::vec3 &position);
  void SetRotation(const glm::vec3 &rotation);

 private:
  // Private members

  CameraProjection projection_;

  glm::mat4 projection_matrix_;
  glm::mat4 view_matrix_;
  glm::mat4 vp_matrix_;

  glm::vec3 position_;
  glm::vec3 rotation_;

  glm::vec2 viewport_;

  float near_plane_;
  float far_plane_;

  float fov_;

  // Private methods

  void UpdateViewMatrix();
  void UpdateProjectionMatrix();
};

}

#endif // ETHAN_CORE_MAIN_CAMERA_H_
