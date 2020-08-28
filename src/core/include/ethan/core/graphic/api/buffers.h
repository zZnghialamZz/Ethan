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
 * @file buffers.h
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

#ifndef ETHAN_CORE_GRAPHIC_BUFFERS_H_
#define ETHAN_CORE_GRAPHIC_BUFFERS_H_

#include "shader.h"

namespace Ethan {
  
  //------------------------------------------------------------------------------
  // Type & Structure Definition
  //------------------------------------------------------------------------------
  enum class BufferDataUsage {
    STATIC,
    DYNAMIC
  };
  
  //------------------------------------------------------------------------------
  // Main Class Objects
  //------------------------------------------------------------------------------
  
  //~ NOTE(Nghia Lam): BufferElement
  class BufferElement {
   public:
    BufferElement(const std::string &name,
                  ShaderData::DataType type,
                  bool normalized = false);
    virtual ~BufferElement();
    
    void SetOffset(size_t offset) { offset_ = offset; }
    
    [[nodiscard]] INLINE const std::string &GetName() const { return name_; }
    [[nodiscard]] INLINE const size_t &GetOffset() const { return offset_; }
    [[nodiscard]] INLINE const uint32_t &GetSize() const { return size_; }
    [[nodiscard]] INLINE const ShaderData::DataType &GetType() const { return type_; }
    [[nodiscard]] INLINE const bool &IsNormalized() const { return normalized_; }
    [[nodiscard]] uint32_t GetComponentCount() const;
    
   private:
    std::string name_;
    uint32_t size_;
    size_t offset_;
    ShaderData::DataType type_;
    bool normalized_;
  };
  
  //~ NOTE(Nghia Lam): BufferLayout
  class BufferLayout {
   public:
    BufferLayout();
    explicit BufferLayout(const std::initializer_list<BufferElement> &elements);
    virtual ~BufferLayout();
    
    void AddElement(const BufferElement& element);
    
    [[nodiscard]] INLINE uint32_t GetStride() const { return stride_; }
    [[nodiscard]] INLINE const std::vector<BufferElement> &GetElements() const { return elements_; }
    
    INLINE std::vector<BufferElement>::iterator begin() { return elements_.begin(); }
    INLINE std::vector<BufferElement>::iterator end() { return elements_.end(); }
    [[nodiscard]] INLINE std::vector<BufferElement>::const_iterator begin() const { return elements_.begin(); }
    [[nodiscard]] INLINE std::vector<BufferElement>::const_iterator end() const { return elements_.end(); }
    
   private:
    std::vector<BufferElement> elements_;
    uint32_t stride_;
    
    void Init();
  };
  
  //~ NOTE(Nghia Lam): VertexBuffer
  class VertexBuffer {
   public:
    virtual ~VertexBuffer() = default;
    
    virtual void Bind() const = 0;
    virtual void UnBind() const = 0;
    
    [[nodiscard]] virtual const BufferLayout& GetLayout() const = 0;
    virtual void SetLayout(const BufferLayout& layout) = 0;
    virtual void SetData(const void* data, uint32_t size) = 0;
    virtual void SetSubData(const void* data, uint32_t size, uint32_t offset) = 0;
    
    static Shared<VertexBuffer> Create(BufferDataUsage usage = BufferDataUsage::STATIC);
    static Shared<VertexBuffer> Create(uint32_t size, BufferDataUsage usage = BufferDataUsage::STATIC);
    static Shared<VertexBuffer> Create(const void* data, uint32_t size, BufferDataUsage usage = BufferDataUsage::STATIC);
  };
  
  //~ NOTE(Nghia Lam): IndexBuffer
  class IndexBuffer {
   public:
    virtual ~IndexBuffer() = default;
    
    virtual void Bind() const = 0;
    virtual void UnBind() const = 0;
    
    [[nodiscard]] virtual uint32_t GetCount() const = 0;
    
    static Shared<IndexBuffer> Create(uint32_t* indices, uint32_t count);
  };
  
}

#endif // ETHAN_CORE_GRAPHIC_BUFFERS_H_
