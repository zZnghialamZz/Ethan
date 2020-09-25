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
 * @file mesh.h
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

#ifndef ETHAN_CORE_GRAPHIC_MESH_H_
#define ETHAN_CORE_GRAPHIC_MESH_H_

#include "ethan/core/graphic/api/vertex_array.h"

namespace Ethan {

class Mesh {
 public:

  //------------------------------------------------------------------------------
  // Definitions & Types
  //------------------------------------------------------------------------------

  enum class PrimitiveType : uint8_t {
    NONE,
    QUAD,
    PLANE,
    CUBE,
    SPHERE,
    PYRAMID,
    CAPSULE,
    CYLINDER
  };

  struct Vertex {
    glm::vec3 Position;
    glm::vec2 Texcoord;
    glm::vec4 VerColor;

    Vertex()
        : Position(glm::vec3(1.0f))
        , Texcoord(glm::vec2(0.0f))
        , VerColor(glm::vec4(1.0f)) {}

    bool operator==(const Vertex& other) const {
      return Position == other.Position && Texcoord == other.Texcoord &&
             VerColor == other.VerColor;
    }
  };

  //------------------------------------------------------------------------------
  // Main Class Object
  //------------------------------------------------------------------------------

  Mesh();
  Mesh(const Mesh& mesh);
  explicit Mesh(const Shared<VertexArray>& vao);

  virtual ~Mesh();

  void Render(uint32_t index_count = 0);  // 0: Render All

  [[nodiscard]] INLINE bool IsHide() const { return is_hide_; };
  [[nodiscard]] INLINE const Shared<VertexArray>& GetVertexArray() const {
    return mesh_vao_;
  }

  // Static method
  static Shared<Mesh> CreatePrimitive(PrimitiveType type);
  static Shared<Mesh> CreateQuad();
  static Shared<Mesh> CreateQuad(float x, float y, float width, float height);
  static Shared<Mesh> CreateQuad(const glm::vec2& position,
                                 const glm::vec2& size);
  static Shared<Mesh> CreatePlane();
  static Shared<Mesh> CreateCube();
  static Shared<Mesh> CreateSphere();
  static Shared<Mesh> CreatePyramid();
  static Shared<Mesh> CreateCapsule();
  static Shared<Mesh> CreateCylinder();
  static Shared<Mesh> CreateBatchMesh();

 private:
  Shared<VertexArray> mesh_vao_;
  bool is_hide_;
};

}  // namespace Ethan

#endif  // ETHAN_CORE_GRAPHIC_MESH_H_
