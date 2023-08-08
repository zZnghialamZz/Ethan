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
// EthanEngine/Core/Application.hpp

#ifndef ETHANENGINE_CORE_APPLICATION_H
#define ETHANENGINE_CORE_APPLICATION_H

namespace Ethan
{

	// -------------------------------------------------------------------
	// SECTION: Application APIs
	// ---
	// Main Entry Point handle for the application built using this engine
	// framework. Here is an example usage of our entry point:
	//
	// ```c++
	// class GameName : public PLEngine::PApplication
	// {
	// public:
	//     GameName ()
	//     {
	//         // Implementation goes here...
	//     }
	//     ~GameNameo () override
	//     {
	//         // Implementation goes here...
	//     }
	//
	//     void RunLoop () override
	//     {
	//         // Implementation goes here....
	//     }
	// }
	//
	// PLENGINE_RUNMAIN (GameMain) // Run the Game Implementation here
	// ```
	// --------------------------------------------------------------------

	class ETHAN_API Application
	{
	public:
		Application();
		virtual ~Application();

		virtual void Start();
		virtual void RunLoop();
		virtual void Exit();
	};

	static int RunMain(Application* App)
	{
		App->Start();
		App->RunLoop();
		App->Exit();
		return 0;
	}
} // namespace Ethan

// ---------------------------------------------------------------------------
// Define the `PLENGINE_RUNMAIN` Macro for client to use it as the entry point
// for their application.
//
// Usage:
//     class Game : public Application { ... }
//     ETHAN_RUNMAIN(Game) // -- Entry point call here.
// ---
// TODO(Nghia Lam): Confirmation for static build DLL.
// ---------------------------------------------------------------------------
#ifndef ETHAN_RUNMAIN
	#if OS_WIN32
		#define ETHAN_RUNMAIN(EApp)                         \
			int __stdcall WinMain(void*, void*, char*, int) \
			{                                               \
				EApp App;                                   \
				return Ethan::RunMain(&App);                \
			}
	#else
		#define ETHAN_RUNMAIN(EApp)          \
			int main(void)                   \
			{                                \
				EApp App;                    \
				return Ethan::RunMain(&App); \
			}
	#endif
#endif

#endif // ETHANENGINE_CORE_APPLICATION_H
