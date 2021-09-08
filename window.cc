#include "window.h"

#include <dwmapi.h>

#include "d3d.h"

void spandex::Window::Init()
{
	window_class.cbSize = sizeof(WNDCLASSEX);
	window_class.style = CS_HREDRAW | CS_VREDRAW;
	window_class.lpfnWndProc = WndProc;
	window_class.lpszClassName = "spandex";
	RegisterClassEx(&window_class);

	hWnd = CreateWindowExA(WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TRANSPARENT, window_class.lpszClassName, window_class.lpszClassName, WS_POPUP, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, window_class.hInstance, NULL);

	SetLayeredWindowAttributes(hWnd, RGB(0, 0, 0), 255, LWA_ALPHA);
	ShowWindow(hWnd, SW_SHOWNORMAL);

	MARGINS margins = { -1, -1, -1, -1 };
	DwmExtendFrameIntoClientArea(hWnd, &margins);

	HWND tWnd = FindWindow(NULL, "Counter-Strike: Global Offensive");
	RECT client_rect;
	GetClientRect(tWnd, &client_rect);
	width = client_rect.right - client_rect.left;
	height = client_rect.bottom - client_rect.top;
	SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, width, height, NULL);
	gD3D.Init();
}

LRESULT CALLBACK spandex::Window::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_PAINT:
		gD3D.Render();
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

void spandex::Window::CleanUp()
{
	DestroyWindow(hWnd);
	UnregisterClass(window_class.lpszClassName, window_class.hInstance);
	gD3D.CleanUp();
}