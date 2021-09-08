#include "esp.h"

#include "d3d.h"
#include "utils.h"

void spandex::ESP::Render()
{
	POINT cursor_pos;
	GetCursorPos(&cursor_pos);
	Config config = engine_->GetConfig();
	if (config.esp.enabled)
	{
		gD3D.DrawString(4, 0, "spandex beta", 255, 255, 255, 255, true);

		GlobalVars global_vars = engine_->GetGlobalVars();

		Entity local_player = engine_->GetLocalPlayer();
		if (!local_player.GetBaseAddress())
			return;

		if (config.esp.head_box)
		{
			for (int i = 0; i < global_vars.m_iMaxClients; i++)
			{
				Entity current_player = engine_->GetPlayerById(i);
				if (!current_player.GetBaseAddress() || current_player.GetBaseAddress() == local_player.GetBaseAddress() || !current_player.IsAlive() || current_player.GetDormant() || current_player.GetTeam() == local_player.GetTeam())
					continue;

				Vector3 head_position = current_player.GetBonePosition(8);

				Vector3 head_screenposition;

				float size = 3500.0f / (head_position - local_player.GetEyePosition()).Magnitude();

				if (utils::WorldToScreen(engine_, head_position, head_screenposition))
					gD3D.DrawBox(head_screenposition.x - size / 2.f, head_screenposition.y - size / 2.f, size, size, 255, 0, 0, 255, false);
			}
		}
	}
}