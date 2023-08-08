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
// EthanEditor/EthanEditor.cpp

#include "EthanEditor.hpp"

namespace EthanEditor
{
	MainEditor::MainEditor() = default;
	MainEditor::~MainEditor() = default;

	void MainEditor::Start()
	{
		Ethan::Application::Start();

		CLIENTLOG_INFO("Ethan Editor Initialized !!");
	}

	void MainEditor::RunLoop()
	{
		Ethan::Application::RunLoop();
	}

	void MainEditor::Exit()
	{
		Ethan::Application::Exit();
	}

} // namespace EthanEditor

ETHAN_RUNMAIN(EthanEditor::MainEditor);
