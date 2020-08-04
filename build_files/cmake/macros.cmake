# ==================================================
#      _____
#   __|___  |__    __    __   _  ____    ____   _
#  |   ___|    | _|  |_ |  |_| ||    \  |    \ | |
#  |   ___|    ||_    _||   _  ||     \ |     \| |
#  |______|  __|  |__|  |__| |_||__|\__\|__/\____|
#     |_____|
#                   Game Engine
# ==================================================
#
# @file macros.cmake
# @author Nghia Lam <nghialam12795@gmail.com>
#
# @brief
#
# @license Copyright 2020 Nghia Lam
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

function(ETHAN_VERSION)
  set(ETHAN_VERSION_MAJOR "0")
  set(ETHAN_VERSION_MINOR "0")
  set(ETHAN_VERSION_PATCH "1")
  set(ETHAN_VERSION "${ETHAN_VERSION_MAJOR}.${ETHAN_VERSION_MINOR}.${ETHAN_VERSION_PATCH}")
endfunction()
