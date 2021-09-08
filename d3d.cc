#include "d3d.h"

#include "window.h"

void spandex::D3D::Init()
{
	Direct3DCreate9Ex(D3D_SDK_VERSION, &interface_ptr);

	D3DPRESENT_PARAMETERS present_params;
	ZeroMemory(&present_params, sizeof(D3DPRESENT_PARAMETERS));
	present_params.Windowed = true;
	present_params.SwapEffect = D3DSWAPEFFECT_DISCARD;
	present_params.MultiSampleQuality = D3DMULTISAMPLE_NONE;
	present_params.hDeviceWindow = gWindow.hWnd;
	present_params.BackBufferFormat = D3DFMT_A8R8G8B8;
	present_params.BackBufferWidth = gWindow.width;
	present_params.BackBufferHeight = gWindow.height;
	present_params.EnableAutoDepthStencil = true;
	present_params.AutoDepthStencilFormat = D3DFMT_D16;

	interface_ptr->CreateDeviceEx(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, gWindow.hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &present_params, 0, &device_ptr);

	D3DXCreateLine(device_ptr, &line_ptr);
	D3DXCreateFont(device_ptr, 18, NULL, FW_NORMAL, NULL, false, DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH, "Segoe UI", &font_ptr);
}

void spandex::D3D::Render()
{
	device_ptr->Clear(NULL, NULL, D3DCLEAR_TARGET, NULL, 1, NULL);
	device_ptr->BeginScene();

	for (RenderModule* module : modules)
	{
		module->Render();
	}

	device_ptr->EndScene();
	device_ptr->PresentEx(NULL, NULL, NULL, NULL, NULL);
}

void spandex::D3D::CleanUp()
{
	interface_ptr->Release();
	device_ptr->Release();
	line_ptr->Release();
	font_ptr->Release();
}

void spandex::D3D::DrawBox(float x, float y, float width, float height, int r, int g, int b, int a, bool filled)
{
	if (filled)
	{
		D3DXVECTOR2 points[2];
		points[0] = D3DXVECTOR2(x, y + height / 2.f);
		points[1] = D3DXVECTOR2(x + width, y + height / 2.f);
		line_ptr->SetWidth(height);
		line_ptr->Draw(points, 2, D3DCOLOR_RGBA(r, g, b, a));
	}
	else
	{
		D3DXVECTOR2 points[5];
		points[0] = D3DXVECTOR2(x, y);
		points[1] = D3DXVECTOR2(x + width - 1, y);
		points[2] = D3DXVECTOR2(x + width - 1, y + height - 1);
		points[3] = D3DXVECTOR2(x, y + height - 1);
		points[4] = D3DXVECTOR2(x, y);
		line_ptr->SetWidth(1);
		line_ptr->Draw(points, 5, D3DCOLOR_RGBA(r, g, b, a));
	}
}

void spandex::D3D::DrawString(float x, float y, const char* string, int r, int g, int b, int a, bool outlined)
{
	if (outlined)
	{
		RECT outline_bottom_rect;
		outline_bottom_rect.top = y + 1;
		outline_bottom_rect.left = x;
		font_ptr->DrawTextA(0, string, strlen(string), &outline_bottom_rect, DT_NOCLIP, D3DCOLOR_RGBA(0, 0, 0, a));

		RECT outline_top_rect;
		outline_top_rect.top = y - 1;
		outline_top_rect.left = x;
		font_ptr->DrawTextA(0, string, strlen(string), &outline_top_rect, DT_NOCLIP, D3DCOLOR_RGBA(0, 0, 0, a));

		RECT outline_left_rect;
		outline_left_rect.top = y;
		outline_left_rect.left = x - 1;
		font_ptr->DrawTextA(0, string, strlen(string), &outline_left_rect, DT_NOCLIP, D3DCOLOR_RGBA(0, 0, 0, a));

		RECT outline_right_rect;
		outline_right_rect.top = y;
		outline_right_rect.left = x + 1;
		font_ptr->DrawTextA(0, string, strlen(string), &outline_right_rect, DT_NOCLIP, D3DCOLOR_RGBA(0, 0, 0, a));

		RECT font_rect;
		font_rect.top = y;
		font_rect.left = x;
		font_ptr->DrawTextA(0, string, strlen(string), &font_rect, DT_NOCLIP, D3DCOLOR_RGBA(r, g, b, a));
	}
	else
	{
		RECT font_rect;
		font_rect.left = x;
		font_rect.top = y;
		font_ptr->DrawTextA(0, string, strlen(string), &font_rect, DT_NOCLIP, D3DCOLOR_RGBA(r, g, b, a));
	}
}

void spandex::D3D::DrawLine(float x1, float y1, float x2, float y2, int r, int g, int b, int a)
{
	D3DXVECTOR2 points[2];
	points[0] = D3DXVECTOR2(x1, y1);
	points[1] = D3DXVECTOR2(x2, y2);
	line_ptr->SetWidth(1);
	line_ptr->Draw(points, 2, D3DCOLOR_RGBA(r, g, b, a));
}