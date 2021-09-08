#include "memory.h"

#include <Psapi.h>

spandex::memory::Module spandex::memory::GetModule(const char* module_name)
{
	HMODULE hModule = GetModuleHandle(module_name);
	MODULEINFO module_info = {};
	if (hModule)
		GetModuleInformation(GetCurrentProcess(), hModule, &module_info, sizeof(MODULEINFO));

	return { (unsigned long)module_info.lpBaseOfDll, (unsigned long)module_info.SizeOfImage };
}

bool spandex::memory::CompareMemory(const BYTE* bData, const BYTE* bMask, const char* szMask)
{
	for (; *szMask; ++szMask, ++bData, ++bMask)
	{
		if (*szMask == 'x' && *bData != *bMask)
		{
			return false;
		}
	}

	return true;
}

DWORD spandex::memory::FindSignature(Module module, Signature signature)
{
	BYTE* dump = new BYTE[module.size];
	memcpy(dump, (BYTE*)module.base_address, module.size);

	for (int i = 0; i < module.size - strlen(signature.szMask); i++)
	{
		if (CompareMemory(dump + i, (const BYTE*)signature.bMask, signature.szMask))
		{
			delete[] dump;
			return *(DWORD*)(module.base_address + i + signature.offsets) + signature.extra - module.base_address;
		}
	}

	delete[] dump;
	return 0;
}