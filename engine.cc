#include "engine.h"

spandex::Entity spandex::Engine::GetLocalPlayer()
{
	return Entity(*(DWORD*)(client_module_.base_address + offsets.dwLocalPlayer));
}

spandex::Entity spandex::Engine::GetPlayerById(int id)
{
	return Entity(*(DWORD*)(client_module_.base_address + offsets.dwEntityList + 0x10 * (id - 1)));
}

spandex::ClientState spandex::Engine::GetClientState()
{
	return ClientState(*(DWORD*)(engine_module_.base_address + offsets.dwClientState));
}

spandex::GlobalVars spandex::Engine::GetGlobalVars()
{
	return *(GlobalVars*)(engine_module_.base_address + offsets.dwGlobalVars);
}

spandex::Matrix4x4* spandex::Engine::GetViewMatrix()
{
	return (Matrix4x4*)(client_module_.base_address + offsets.dwViewMatrix);
}

void spandex::Engine::Shoot()
{
	int* force_attack = (int*)(client_module_.base_address + offsets.dwForceAttack);
	*force_attack = 5;
	Sleep(30);
	*force_attack = 4;
}

void spandex::Engine::Jump()
{
	int* force_jump = (int*)(client_module_.base_address + offsets.dwForceJump);
	*force_jump = 5;
	Sleep(30);
	*force_jump = 4;
}

void spandex::Engine::SetForceBackward(bool value)
{
	if (GetForceBackward() != value)
	{
		int* force_backward = (int*)(client_module_.base_address + offsets.dwForceBackward);
		if (value)
			*force_backward = 1;
		else
			*force_backward = 0;
	}
}

void spandex::Engine::SetForceForward(bool value)
{
	if (GetForceForward() != value)
	{
		int* force_forward = (int*)(client_module_.base_address + offsets.dwForceForward);
		if (value)
			*force_forward = 1;
		else
			*force_forward = 0;
	}
}

void spandex::Engine::SetForceLeft(bool value)
{
	if (GetForceLeft() != value)
	{
		int* force_left = (int*)(client_module_.base_address + offsets.dwForceLeft);
		if (value)
			*force_left = 1;
		else
			*force_left = 0;
	}
}

void spandex::Engine::SetForceRight(bool value)
{
	if (GetForceRight() != value)
	{
		int* force_right = (int*)(client_module_.base_address + offsets.dwForceRight);
		if (value)
			*force_right = 1;
		else
			*force_right = 0;
	}
}

void spandex::Engine::SetClanTag(const char* tag)
{
	static auto pSetClanTag = reinterpret_cast<void(__fastcall*)(const char*, const char*)>(engine_module_.base_address + offsets.dwSetClanTag);
	pSetClanTag(tag, tag);
}

bool spandex::Engine::GetForceBackward()
{
	int* force_backward = (int*)(client_module_.base_address + offsets.dwForceBackward);
	return *force_backward;
}

bool spandex::Engine::GetForceForward()
{
	int* force_forward = (int*)(client_module_.base_address + offsets.dwForceForward);
	return *force_forward;
}

bool spandex::Engine::GetForceLeft()
{
	int* force_left = (int*)(client_module_.base_address + offsets.dwForceLeft);
	return *force_left;
}

bool spandex::Engine::GetForceRight()
{
	int* force_right = (int*)(client_module_.base_address + offsets.dwForceRight);
	return *force_right;
}

void spandex::Engine::UpdateOffsets()
{
	// Memory pattern scanning was removed from here to prevent easy functionality.
}