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

namespace Ethan::String {

/**
 * Split String based on the given separator
 * @param original - std::string
 * @param separator - std::string
 * @return a vector contains all split strings
 */
static std::vector<std::string> Split(const std::string &original,
                                      const std::string &separator);

/**
 * Convert a string with '\n' into a vector of strings
 * @param input - std::string
 * @return a vector of strings
 */
static std::vector<std::string> GetLines(const std::string& input);

/**
 * Checking if the given string contains a specific word.
 * @param input - std::string
 * @param contain - std::string
 * @return whether the string contains word
 */
static bool IsContains(const std::string& input, const std::string& word);

}

#endif // ETHAN_UTILS_HELPER_STRING_EXT_H_
