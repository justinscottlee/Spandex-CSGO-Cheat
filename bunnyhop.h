#ifndef SPANDEX_MODULE_BUNNYHOP_H_
#define SPANDEX_MODULE_BUNNYHOP_H_

#include "module.h"

namespace spandex
{
	class Bunnyhop : public Module
	{
	public:
		Bunnyhop(Engine* engine) : Module(engine) {}
		void Tick();
	};
}

#endif