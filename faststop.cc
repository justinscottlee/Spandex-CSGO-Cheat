#include "faststop.h"

#include "utils.h"

void spandex::Faststop::Tick()
{
	Config config = engine_->GetConfig();

	if (config.faststop.enabled)
	{
		Entity local_player = engine_->GetLocalPlayer();
		if (!local_player.GetBaseAddress())
			return;

		if (!GetAsyncKeyState(VK_SPACE) && local_player.IsGrounded())
		{
			Vector3 velocity = local_player.GetVelocity();

			ClientState client_state = engine_->GetClientState();
			if (!client_state.GetBaseAddress())
				return;

			Vector3 view_angles = utils::angle::FromQAngle(client_state.GetViewAngles());
			Vector3 forward_direction = Vector3(view_angles.x, view_angles.y, 0);
			Vector3 right_direction = Vector3(view_angles.y, -view_angles.x, 0);

			float forward_velocity = Vector3::DotProduct(velocity, forward_direction);
			float right_velocity = Vector3::DotProduct(velocity, right_direction);

			float max_allowed_velocity = 250.0f - 240.0f * config.faststop.strength;

			bool forward_keystate = GetAsyncKeyState(0x57);
			bool backward_keystate = GetAsyncKeyState(0x53);

			if (forward_velocity > max_allowed_velocity && !forward_keystate)
				engine_->SetForceBackward(true);
			else if (forward_velocity < -max_allowed_velocity && !backward_keystate)
				engine_->SetForceForward(true);
			if (engine_->GetForceBackward() && forward_velocity < max_allowed_velocity && !backward_keystate)
				engine_->SetForceBackward(false);
			else if (engine_->GetForceForward() && forward_velocity > -max_allowed_velocity && !forward_keystate)
				engine_->SetForceForward(false);

			bool right_keystate = GetAsyncKeyState(0x44);
			bool left_keystate = GetAsyncKeyState(0x41);
			if (right_velocity > max_allowed_velocity && !right_keystate)
				engine_->SetForceLeft(true);
			else if (right_velocity < -max_allowed_velocity && !left_keystate)
				engine_->SetForceRight(true);
			if (engine_->GetForceLeft() && right_velocity < max_allowed_velocity && !left_keystate)
				engine_->SetForceLeft(false);
			else if (engine_->GetForceRight() && right_velocity > -max_allowed_velocity && !right_keystate)
				engine_->SetForceRight(false);
		}
	}
}