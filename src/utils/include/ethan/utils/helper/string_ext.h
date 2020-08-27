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
 * @file string_ext.h
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

#ifndef ETHAN_UTILS_HELPER_STRING_EXT_H_
#define ETHAN_UTILS_HELPER_STRING_EXT_H_

#include <string.h> // For strlen, strcmp, memcpy, etc..

namespace Ethan::String {

/**
 * Split String based on the given separator
 * @param original - std::string
 * @param separator - std::string
 * @return a vector contains all split strings
 */
std::vector<std::string> Split(const std::string &original,
                               const std::string &separator);

/**
 * Convert a string with multiple lines into a vector of strings
 * @param input - std::string
 * @return a vector of strings
 */
std::vector<std::string> GetLines(const std::string& input);

/**
 * Checking if the given string contains a specific word.
 * @param input - std::string
 * @param contain - std::string
 * @return whether the string contains word
 */
bool IsContains(const std::string& input, const std::string& word);

/**
 * Checking if the given string start with a specific word.
 * @param input - std::string
 * @param word - std::string
 * @return  whether the string start with word
 */
bool IsStartWith(const std::string& input, const std::string& word);

}

namespace Ethan {
  
  // NOTE(Nghia Lam): Temporary class until fully replace std::string.
  class Str {
    
   public:
    Str();
    
    [[nodiscard]] INLINE char* c_str() { return data_; }
    [[nodiscard]] INLINE const char* c_str() const { return data_; }
    [[nodiscard]] INLINE bool empty() const { return data_[0] == 0; }
    [[nodiscard]] INLINE int length() const { return (int)strlen(data_); }
    [[nodiscard]] INLINE int capacity() const { return capacity_; }
    
    [[nodiscard]] INLINE char& operator[](size_t i) { return data_[i]; }
    [[nodiscard]] INLINE char operator[](size_t i) const { return data_[i]; }
    [[nodiscard]] INLINE Str& operator=(const char* input) const { /* Return Str here */ }
    [[nodiscard]] INLINE bool operator==(const char* input) const { return strcmp(c_str(), input) == 0; }
    
    void clear();
    void reserve(int cap);
    void reserve_discard(int cap);
    void shrink_to_fit();
     
   private:
    // Private Members ---
    
    char*        data_;                  // Point to local buffer or heap allocate
    int          capacity_ : 21;         // Max 2MB
    int          localbuffer_size_ : 10; // Max 1023 Bytes
    unsigned int owned_ : 1;             // Set when we have the ownership of the pointed data (most common, unless using set reference method or create a reference constructor.
    
  };
  
}

#endif // ETHAN_UTILS_HELPER_STRING_EXT_H_
