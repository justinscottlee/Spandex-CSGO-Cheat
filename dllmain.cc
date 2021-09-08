#include <thread>

#include "config.h"
#include "engine.h"

#include "bunnyhop.h"
#include "aimbot.h"
#include "faststop.h"
#include "clantag.h"
#include "esp.h"

#include "D3D.h"
#include "Window.h"

spandex::Window spandex::gWindow;
spandex::D3D spandex::gD3D;

DWORD WINAPI MainThread(HMODULE hModule)
{
	spandex::Config config;
	spandex::Engine engine = spandex::Engine(config);

	spandex::gWindow.Init();

	spandex::ESP esp = spandex::ESP(&engine);
	spandex::gD3D.AddModule(&esp);

	std::list<spandex::Module*> modules = { &spandex::Bunnyhop(&engine), &spandex::Aimbot(&engine), &spandex::Faststop(&engine), &spandex::Clantag(&engine) };
	for (spandex::Module* module : modules)
	{
		auto thread = std::thread(spandex::ModuleThread, module, &engine);
		thread.detach();
	}

	while (!GetAsyncKeyState(VK_RCONTROL))
	{
		if (spandex::gWindow.hWnd)
		{
			InvalidateRect(spandex::gWindow.hWnd, NULL, false);
			MSG msg;
			if (PeekMessage(&msg, spandex::gWindow.hWnd, NULL, NULL, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
	}

	spandex::gWindow.CleanUp();

	engine.Close();

	Sleep(1000);

	FreeLibraryAndExitThread(hModule, 0);
}

DWORD WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
#ifdef SPANDEX_DEBUG
		AllocConsole();
		freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
#endif
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)MainThread, hModule, 0, nullptr);
		break;
	case DLL_PROCESS_DETACH:
#ifdef SPANDEX_DEBUG
		fclose((FILE*)stdout);
		FreeConsole();
#endif
		break;
	}

	return TRUE;
}