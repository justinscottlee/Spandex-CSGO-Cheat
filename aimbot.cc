#include "aimbot.h"

#include <algorithm>

#include "utils.h"

//TODO: FOLLOW CURVE INSTEAD OF STRAIGHT LINE?
//TODO: ADD RANDOM ERROR CONFIG OPTION?
void spandex::Aimbot::Tick()
{
	Config config = engine_->GetConfig();

	if (config.aimbot.enabled)
	{
		if (!config.aimbot.while_firing || config.aimbot.while_firing && GetAsyncKeyState(VK_LBUTTON))
		{
			Entity closest_player = utils::FindClosestEnemyToCrosshair(engine_);
			if (!closest_player.GetBaseAddress())
				return;

			int closest_bone = utils::FindClosestBoneToCrosshair(engine_, closest_player);

			float delta_angle = utils::GetAngleFromCrosshair(engine_, closest_player.GetBonePosition(closest_bone)).Magnitude();

			if (delta_angle <= config.aimbot.fov)
			{
				Entity local_player = engine_->GetLocalPlayer();
				if (!local_player.GetBaseAddress())
					return;

				ClientState client_state = engine_->GetClientState();
				if (!client_state.GetBaseAddress())
					return;

				Vector3 recoil_offset = local_player.GetAimPunch() * -2;
				float degrees_per_tick = 0.005f / (config.aimbot.smoothing + std::numeric_limits<float>::epsilon());
				float smoothing_factor = std::clamp(degrees_per_tick / delta_angle, 0.0f, 1.0f);
				Vector3 projected_aim_position = local_player.GetEyePosition() + utils::angle::FromQAngle(client_state.GetViewAngles() + local_player.GetAimPunch() * 2) * (closest_player.GetBonePosition(closest_bone) - local_player.GetEyePosition()).Magnitude();
				Vector3 target_aim_position = projected_aim_position + (closest_player.GetBonePosition(closest_bone) - projected_aim_position) * smoothing_factor;

				client_state.SetViewAngles(utils::angle::ToQAngle(target_aim_position - local_player.GetEyePosition()) + recoil_offset);
			}
		}
	}
}