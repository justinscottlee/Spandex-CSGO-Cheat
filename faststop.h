#ifndef SPANDEX_MODULE_FASTSTOP_H_
#define SPANDEX_MODULE_FASTSTOP_H_

#include "module.h"

namespace spandex
{
	class Faststop : public Module
	{
	public:
		Faststop(Engine* engine) : Module(engine) {}
		void Tick();
	};
}

#endif