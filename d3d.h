#ifndef SPANDEX_OVERLAY_D3D_H_
#define SPANDEX_OVERLAY_D3D_H_

#include <functional>

#include <d3d9.h>
#include <d3dx9.h>

#include "esp.h"

namespace spandex
{
	class D3D
	{
	public:
		void Init();
		void Render();
		void CleanUp();
		void AddModule(RenderModule* module) { modules.push_back(module); }

		void DrawBox(float x, float y, float width, float height, int r, int g, int b, int a, bool filled);
		void DrawString(float x, float y, const char* string, int r, int g, int b, int a, bool outlined);
		void DrawLine(float x1, float y1, float x2, float y2, int r, int g, int b, int a);

	private:
		IDirect3D9Ex* interface_ptr;
		IDirect3DDevice9Ex* device_ptr;
		ID3DXLine* line_ptr;
		ID3DXFont* font_ptr;

		std::list<RenderModule*> modules;
	};

	extern D3D gD3D;
}

#endif