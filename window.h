#ifndef SPANDEX_OVERLAY_WINDOW_H_
#define SPANDEX_OVERLAY_WINDOW_H_

#include <Windows.h>

namespace spandex
{
	class Window
	{
	public:
		HWND hWnd;
		WNDCLASSEX window_class;
		int width, height;

		void Init();
		static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		void CleanUp();
	};

	extern Window gWindow;
}

#endif