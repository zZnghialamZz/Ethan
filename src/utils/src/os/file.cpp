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
 * @file file.cpp
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

#include "ethan/utils/os/file.h"

namespace Ethan {

/**
 * Checking if the file has the same extension as the given one.
 * @param file_name - char array
 * @param extension - char array
 * @return whether the file extension is matched.
 */
bool FileHandler::IsFileExtension(const char *file_name,
                                  const char *extension) {
  const char* file_ext = GetFileExtension(file_name);
  if (file_ext)
    if (strcmp(file_ext, extension) != 0) return true;

  return false;
}

/**
 * Find the extension of the given file.
 * The function assume the file has an extension start with '.'
 * @param file_name - char array
 * @return a pointer at the position of the extension
 */
const char* FileHandler::GetFileExtension(const char *file_name) {
  const char* dot = strrchr(file_name, '.');
  if (!dot || dot == file_name) return nullptr;

  return (dot + 1);
}

}