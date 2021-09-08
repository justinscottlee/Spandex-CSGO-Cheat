#ifndef SPANDEX_MODULE_AIMBOT_H_
#define SPANDEX_MODULE_AIMBOT_H_

#include "module.h"

namespace spandex
{
	class Aimbot : public Module
	{
	public:
		Aimbot(Engine* engine) : Module(engine) {}
		void Tick();
	};
}

#endif