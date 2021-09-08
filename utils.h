#ifndef SPANDEX_UTILS_H_
#define SPANDEX_UTILS_H_

#include <cmath>
#include <list>

#include "vector3.h"
#include "window.h"

#define RAD2DEG 180. / M_PI
#define DEG2RAD M_PI / 180.

namespace spandex
{
	namespace utils
	{
		namespace angle
		{
			static Vector3 ClampQAngle(const Vector3& vector)
			{
				Vector3 clamped = vector;

				if (vector.x > 89.f)
					clamped.x = 89.f;
				else if (vector.x < -89.f)
					clamped.x = -89.f;

				if (vector.y > 180.f)
					clamped.y = vector.y - 360.f;
				else if (vector.y < -180.f)
					clamped.y = vector.y + 360.f;

				return clamped;
			}

			static Vector3 FromQAngle(const Vector3& vector)
			{
				return Vector3(cosf(DEG2RAD * vector.y) * cosf(DEG2RAD * vector.x), sinf(DEG2RAD * vector.y) * cosf(DEG2RAD * vector.x), -sinf(DEG2RAD * vector.x));
			}

			static Vector3 ToQAngle(const Vector3& vector)
			{
				return Vector3(RAD2DEG * atan2f(-vector.z, std::hypotf(vector.x, vector.y)), RAD2DEG * atan2f(vector.y, vector.x), 0);
			}
		}

		static Vector3 GetAngleFromCrosshair(Engine* engine, const Vector3& position)
		{
			Entity local_player = engine->GetLocalPlayer();
			if (!local_player.GetBaseAddress())
				return Vector3(89, 0, 0);

			Vector3 eye_position = local_player.GetEyePosition();

			ClientState client_state = engine->GetClientState();
			if (!client_state.GetBaseAddress())
				return Vector3(89, 0, 0);

			Vector3 view_angles = client_state.GetViewAngles();

			return angle::ClampQAngle(angle::ToQAngle(position - eye_position) - (view_angles + local_player.GetAimPunch() * 2));
		}

		static int FindClosestBoneToCrosshair(Engine* engine, Entity entity)
		{
			std::list<int> bones = { 5, 6, 7, 8, 11, 12, 41, 42 };
			int closest_bone = 8;

			for (int bone : bones)
			{
				if (!entity.IsAlive() || entity.GetDormant())
					return 8;

				if (GetAngleFromCrosshair(engine, entity.GetBonePosition(bone)).MagnitudeSqr() < GetAngleFromCrosshair(engine, entity.GetBonePosition(closest_bone)).MagnitudeSqr())
					closest_bone = bone;
			}

			return closest_bone;
		}

		static Entity FindClosestEnemyToCrosshair(Engine* engine)
		{
			Entity local_player = engine->GetLocalPlayer();
			if (!local_player.GetBaseAddress())
				return Entity(0);

			GlobalVars global_vars = engine->GetGlobalVars();

			Entity best_player = Entity(0);
			for (int i = 0; i < global_vars.m_iMaxClients; i++)
			{
				Entity current_player = engine->GetPlayerById(i);
				if (!current_player.GetBaseAddress() || current_player.GetTeam() == local_player.GetTeam() || current_player.GetDormant() || !current_player.IsAlive())
					continue;

				if (!best_player.GetBaseAddress())
				{
					best_player = current_player;
					continue;
				}

				if (GetAngleFromCrosshair(engine, current_player.GetBonePosition(6)).MagnitudeSqr() < GetAngleFromCrosshair(engine, best_player.GetBonePosition(6)).MagnitudeSqr())
					best_player = current_player;
			}

			return best_player;
		}

		static bool WorldToScreen(Engine* engine, Vector3 position, Vector3& screen_position)
		{
			Matrix4x4* view_matrix_ptr = engine->GetViewMatrix();
			if (!view_matrix_ptr)
				return false;
			Matrix4x4 view_matrix = *view_matrix_ptr;

			float x = position.x * view_matrix.m[0][0] + position.y * view_matrix.m[0][1] + position.z * view_matrix.m[0][2] + view_matrix.m[0][3];
			float y = position.x * view_matrix.m[1][0] + position.y * view_matrix.m[1][1] + position.z * view_matrix.m[1][2] + view_matrix.m[1][3];
			float z = position.x * view_matrix.m[2][0] + position.y * view_matrix.m[2][1] + position.z * view_matrix.m[2][2] + view_matrix.m[2][3];
			float w = position.x * view_matrix.m[3][0] + position.y * view_matrix.m[3][1] + position.z * view_matrix.m[3][2] + view_matrix.m[3][3];

			if (w < 0.1f)
				return false;

			Vector3 ndc = Vector3(x / w, y / w, 0);

			screen_position.x = ndc.x + gWindow.width / 2.f + ndc.x * gWindow.width / 2.f;
			screen_position.y = ndc.y + gWindow.height / 2.f - ndc.y * gWindow.height / 2.f;

			return true;
		}
	}
}

#endif