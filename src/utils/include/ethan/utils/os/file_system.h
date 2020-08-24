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
 * @file file.h
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

#ifndef ETHAN_UTILS_HELPER_FILE_H_
#define ETHAN_UTILS_HELPER_FILE_H_

#if defined(__GNUC__)
#include <cstdio>
#include <cstring>
#endif

#include <fstream>
#include <sys/stat.h>

namespace Ethan::FileSystem {

/**
 * Read a file from source.
 * @param file_path - char array
 * @return a string which has all of the given file's contents
 */
INLINE static std::string ReadFile(const std::string& file_path) {
  std::string result;
  std::ifstream in(file_path, std::ios::in | std::ios::binary);
  if (in) {
    in.seekg(0, std::ios::end);
    result.resize(in.tellg());
    in.seekg(0, std::ios::beg);
    in.read(&result[0], result.size());
    in.close();
  }

  return result;
}

/**
 * Get the file name based on the given path. Please be note that this function
 * will not return the file extension (if any)
 * @param file_path -  std::string
 * @return The File Name only.
 */
INLINE static std::string GetFileName(const std::string& file_path) {
  size_t found = file_path.find_last_of("/\\");
  std::string file_name = (found != std::string::npos)
      ? file_path.substr(found + 1)
      : file_path;

  found = file_name.find_last_of(".");
  file_name = (found != std::string::npos)
      ? file_name.substr(0, found)
      : file_name;

  return file_name;
}

/**
 * Find the extension of the given file.
 * The function assume the file has an extension start with '.'
 * @param file_name - char array
 * @return a pointer at the position of the extension
 */
INLINE static const char* GetFileExtension(const char* file_name) {
  const char* dot = strrchr(file_name, '.');
  if (!dot || dot == file_name) return nullptr;

  return (dot + 1);
}

/**
 * Checking if the file has the same extension as the given one.
 * @param file_name - char array
 * @param extension  - char array
 * @return whether the file extension is matched.
 */
INLINE static bool IsFileExtension(const char* file_name, const char* extension) {
  const char* file_ext = GetFileExtension(file_name);
  if (file_ext)
    if (strcmp(file_ext, extension) != 0) return true;

  return false;
}

/**
 * Access the file using stat POSIX function to check if it exists.
 * @param file_path - char array
 * @return whether the given file is existed.
 */
INLINE static bool IsFileExist(const char* file_path) {
  struct stat buffer{};
  return (stat(file_path, &buffer) == 0);
}

} // namespace Ethan::FileSystem

#endif // ETHAN_UTILS_HELPER_FILE_H_
