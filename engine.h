#ifndef SPANDEX_ENGINE_ENGINE_H_
#define SPANDEX_ENGINE_ENGINE_H_

#include "config.h"
#include "memory.h"
#include "entity.h"
#include "client_state.h"
#include "GlobalVars.h"
#include "matrix.h"

namespace spandex
{
	class Engine
	{
	public:
		Engine(Config& config) : config_(config), client_module_(memory::GetModule("client_panorama.dll")), engine_module_(memory::GetModule("engine.dll")) { UpdateOffsets(); }

		void Close() { should_close_ = true; }
		bool ShouldClose() { return should_close_; }

		const Config GetConfig() { return config_; }

		Entity GetLocalPlayer();
		Entity GetPlayerById(int id);
		ClientState GetClientState();
		Matrix4x4* GetViewMatrix();
		GlobalVars GetGlobalVars();

		void Shoot();
		void Jump();
		void SetForceBackward(bool value);
		void SetForceForward(bool value);
		void SetForceLeft(bool value);
		void SetForceRight(bool value);
		void SetClanTag(const char* tag);

		bool GetForceBackward();
		bool GetForceForward();
		bool GetForceLeft();
		bool GetForceRight();

		struct
		{
			DWORD dwLocalPlayer;
			DWORD dwEntityList;
			DWORD dwClientState;
			DWORD dwForceAttack;
			DWORD dwForceJump;
			DWORD dwForceBackward;
			DWORD dwForceForward;
			DWORD dwForceLeft;
			DWORD dwForceRight;
			DWORD dwSetClanTag;
			DWORD dwGlobalVars;
			DWORD dwViewMatrix;
		} offsets;

	private:
		memory::Module client_module_;
		memory::Module engine_module_;
		Config config_;
		bool should_close_;

		void UpdateOffsets();
	};
}

#endif