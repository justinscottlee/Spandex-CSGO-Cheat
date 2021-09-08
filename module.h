#ifndef SPANDEX_MODULE_MODULE_H_
#define SPANDEX_MODULE_MODULE_H_

#include <thread>
#include <ctime>

#include "engine.h"

namespace spandex
{
	class Module
	{
	public:
		Module(Engine* engine) : engine_(engine) {}
		virtual void Tick() {}

	protected:
		Engine* engine_;
	};

	void ModuleThread(Module* module, Engine* engine);
}

#endif