#ifndef SPANDEX_MODULE_RENDERMODULE_H_
#define SPANDEX_MODULE_RENDERMODULE_H_

#include "engine.h"

namespace spandex
{
	class RenderModule
	{
	public:
		RenderModule(Engine* engine) : engine_(engine) {}
		virtual void Render() {}

	protected:
		Engine* engine_;
	};
}

#endif