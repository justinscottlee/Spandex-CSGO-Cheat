#ifndef SPANDEX_MODULE_CLANTAG_H_
#define SPANDEX_MODULE_CLANTAG_H_

#include "module.h"

namespace spandex
{
	class Clantag : public Module
	{
	public:
		Clantag(Engine* engine) : Module(engine) {}
		void Tick();

	private:
		int last_length_;
	};
}

#endif