#ifndef SPANDEX_LOCAL_PLAYER_H_
#define SPANDEX_LOCAL_PLAYER_H_

#include <limits>

#include "vector3.h"

namespace spandex
{
	struct Bone
	{
		const char pad0[0xC];
		const float x;
		const char pad1[0xC];
		const float y;
		const char pad2[0xC];
		const float z;
	};

	class Entity
	{
	public:
		Entity(DWORD base_address) : base_address_(base_address) {}

		DWORD GetBaseAddress() const { return base_address_; }

		bool GetDormant() const { return *(bool*)(base_address_ + 0xED); }
		int GetTeam() const { return *(int*)(base_address_ + 0xF4); }
		int GetHealth() const { return *(int*)(base_address_ + 0x100); }
		int GetFlags() const { return *(int*)(base_address_ + 0x104); }
		Vector3 GetViewOffset() const { return *(Vector3*)(base_address_ + 0x108); }
		Vector3 GetVelocity() const { return *(Vector3*)(base_address_ + 0x114); }
		Vector3 GetOrigin() const { return *(Vector3*)(base_address_ + 0x138); }
		Vector3 GetViewPunch() const { return *(Vector3*)(base_address_ + 0x3020); }
		Vector3 GetAimPunch() const { return *(Vector3*)(base_address_ + 0x302C); }
		Vector3 GetAimPunchVelocity() const { return *(Vector3*)(base_address_ + 0x3038); }
		Vector3 GetEyePosition() const { return GetOrigin() + GetViewOffset(); }

		void SetDormant(const bool& value) const { *(bool*)(base_address_ + 0xED) = value; }
		void SetTeam(const int& value) const { *(int*)(base_address_ + 0xF4) = value; }
		void SetHealth(const int& value) const { *(int*)(base_address_ + 0x100) = value; }
		void SetFlags(const int& value) const { *(int*)(base_address_ + 0x104) = value; }
		void SetViewOffset(const Vector3& value) const { *(Vector3*)(base_address_ + 0x108) = value; }
		void SetVelocity(const Vector3& value) const { *(Vector3*)(base_address_ + 0x114) = value; }
		void SetOrigin(const Vector3& value) const { *(Vector3*)(base_address_ + 0x138) = value; }
		void SetViewPunch(const Vector3& value) const { *(Vector3*)(base_address_ + 0x3020) = value; }
		void SetAimPunch(const Vector3& value) const { *(Vector3*)(base_address_ + 0x302C) = value; }
		void SetAimPunchVelocity(const Vector3& value) const { *(Vector3*)(base_address_ + 0x3038) = value; }

		Vector3 GetBonePosition(int bone)
		{
			Bone* bone_matrix = GetBoneMatrix();
			if (!bone_matrix)
				return Vector3(0, 0, std::numeric_limits<float>::infinity());

			return Vector3(bone_matrix[bone].x, bone_matrix[bone].y, bone_matrix[bone].z);
		}

		bool IsAlive() const { return GetHealth() > 0; }
		bool IsGrounded() const { return GetFlags() & (1 << 0); }

	private:
		DWORD base_address_;
		Bone* GetBoneMatrix() const { return *(Bone**)(base_address_ + 0x26A8); }
	};
}

#endif