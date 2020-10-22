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
 * @file ui_macros.h
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

#ifndef ETHAN_UI_MACROS_H_
#define ETHAN_UI_MACROS_H_

namespace Ethan {

//------------------------------------------------------------------------------
// UI Configurations
// NOTE(Nghia Lam): Some of these configs is used for fixed size data storage,
// which might need to comeback and revise many times. --> Can we consider using
// another built-in dynamic array?
//------------------------------------------------------------------------------
#define FONTATLAS_WIDTH  1024        // Current width of font atlas
#define UILAYOUT_SIZE    16          // Maximum support 16 nested layout
#define UICONTAINER_SIZE 48          // Maximum support 48 opened window
#define UICOMMAND_SIZE   256 * 1024

}  // namespace Ethan

#endif  // ETHAN_UI_MACROS_H_
