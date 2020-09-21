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

//------------------------------------------------------------------------------
// Type & Structure Definition
//------------------------------------------------------------------------------

enum class CameraMode : u8 {
  CAMERA_CUSTOM = 0,
  CAMERA_2D,    // Camera specific for 2D View, can be used as default 2D game camera.
  CAMERA_FREE,  // Free style camera for editing Scene.
  CAMERA_FPS,   // Camera specific for FPS Game.
  CAMERA_THIRD  // Camera specific for third person view.
};

enum class CameraType : u8 {
  ORTHOGRAPHIC,
  PERSPECTIVE
};

//------------------------------------------------------------------------------
// Camera Class Object
//------------------------------------------------------------------------------
class Camera {
 public:
  explicit Camera(CameraMode mode = CameraMode::CAMERA_FREE,
                  CameraType type = CameraType::ORTHOGRAPHIC);
  virtual ~Camera();

  [[nodiscard]] INLINE CameraType GetCameraType() const { return type_; }
  [[nodiscard]] INLINE CameraMode GetCameraMode() const { return mode_; }
  [[nodiscard]] INLINE float GetNearPlane() const { return near_plane_; }
  [[nodiscard]] INLINE float GetFarPlane() const { return far_plane_; }
  [[nodiscard]] INLINE float GetFieldOfViewDegree() const { return fov_; }
  [[nodiscard]] INLINE float GetAspectRatio() const { return aspect_ratio_; }
  [[nodiscard]] INLINE float GetZoomLevel() const { return zoom_; }
  [[nodiscard]] INLINE const glm::vec2 &GetViewport() const { return viewport_; }
  [[nodiscard]] INLINE const glm::vec3 &GetPosition() const { return position_; }
  [[nodiscard]] INLINE const glm::vec3 &GetRotation() const { return rotation_; }
  [[nodiscard]] INLINE const glm::mat4 &GetProjectionMatrix() const { return projection_matrix_; }
  [[nodiscard]] INLINE const glm::mat4 &GetViewMatrix() const { return view_matrix_; }
  [[nodiscard]] INLINE const glm::mat4 &GetViewProjectionMatrix() const { return vp_matrix_; }

  void SetAspectRatio(float aspect_ratio);
  void SetZoomLevel(float zoom);
  void SetCameraType(CameraType type);
  void SetCameraMode(CameraMode mode);
  void SetFieldOfViewDegree(float degree);
  void SetViewport(const glm::vec2 &viewport);
  void SetClippingPlanes(float near_plane, float far_plane);
  void SetPosition(const glm::vec3 &position);
  void SetRotation(const glm::vec3 &rotation);

 private:
  // Private members

  CameraMode mode_;
  CameraType type_;

  glm::mat4 projection_matrix_;
  glm::mat4 view_matrix_;
  glm::mat4 vp_matrix_;

  glm::vec3 position_;
  glm::vec3 rotation_;

  glm::vec2 viewport_;

  float near_plane_;
  float far_plane_;

  float fov_;

  float aspect_ratio_;
  float zoom_;

  // Private methods

  void UpdateViewMatrix();
  void UpdateProjectionMatrix();
};

}

#endif // ETHAN_CORE_MAIN_CAMERA_H_
