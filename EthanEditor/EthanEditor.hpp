// ==================================================
//      _____
//   __|___  |__    __    __   _  ____    ____   _
//  |   ___|    | _|  |_ |  |_| ||    \  |    \ | |
//  |   ___|    ||_    _||   _  ||     \ |     \| |
//  |______|  __|  |__|  |__| |_||__|\__\|__/\____|
//     |_____|
//                   Game Engine
// ==================================================
//
// Github : https://github.com/zZnghialamZz/Ethan
// License: MIT License (See LICENSE for details)
//
// ---
// EthanEditor/EthanEditor.hpp

#ifndef ETHANEDITOR_EDITOR_H
#define ETHANEDITOR_EDITOR_H

#include "Ethan.hpp"

namespace EthanEditor
{
	class MainEditor final : public Ethan::Application
	{
	public:
		MainEditor();
		~MainEditor() override;

		void Init() override;
		void RunLoop() override;
		void Exit() override;
	};
} // namespace EthanEditor

#endif // ETHANEDITOR_EDITOR_H
