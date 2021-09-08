#include "bunnyhop.h"

#include <ctime>
#include <thread>

void spandex::Bunnyhop::Tick()
{
	Config config = engine_->GetConfig();

	if (config.bunnyhop.enabled)
	{
		spandex::Entity local_player = engine_->GetLocalPlayer();
		if (!local_player.GetBaseAddress())
			return;

		if (GetAsyncKeyState(VK_SPACE))
		{
			if (local_player.IsGrounded())
			{
				int min_error = config.bunnyhop.minimum_error;
				int max_error = config.bunnyhop.maximum_error;

				Sleep(min_error);
				if (max_error > min_error)
					Sleep(rand() % (max_error - min_error));
				engine_->Jump();
			}
		}
	}
}