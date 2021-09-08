#ifndef SPANDEX_ENGINE_MEMORY_H_
#define SPANDEX_ENGINE_MEMORY_H_

#include <Windows.h>

namespace spandex
{
	namespace memory
	{
		struct Module
		{
			DWORD base_address;
			DWORD size;
		};

		struct Signature
		{
			const char* bMask;
			const char* szMask;
			int offsets;
			int extra;
		};

		Module GetModule(const char* module_name);
		bool CompareMemory(const BYTE* bData, const BYTE* bMask, const char* szMask);
		DWORD FindSignature(Module module, Signature signature);
	}
}

#endif