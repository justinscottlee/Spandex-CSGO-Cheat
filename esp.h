#ifndef SPANDEX_MODULE_ESP_H_
#define SPANDEX_MODULE_ESP_H_

#include "rendermodule.h"

namespace spandex
{
	class ESP : public RenderModule
	{
	public:
		ESP(Engine* engine) : RenderModule(engine) {}
		void Render();
	};
}

#endif