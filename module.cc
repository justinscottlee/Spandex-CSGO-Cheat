#include "module.h"

void spandex::ModuleThread(Module* module, Engine* engine)
{
	std::clock_t last_tick_time = 0;

	while (!engine->ShouldClose())
	{
		while (std::clock() - last_tick_time == 0)
		{
			std::this_thread::yield();
		}

		module->Tick();

		last_tick_time = std::clock();
	}
}