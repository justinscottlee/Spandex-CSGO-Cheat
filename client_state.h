#ifndef SPANDEX_CLIENT_STATE_H_
#define SPANDEX_CLIENT_STATE_H_

#include "NetChannel.h"

namespace spandex
{
	class ClientState
	{
	public:
		ClientState(DWORD base_address) : base_address_(base_address) {}

		DWORD GetBaseAddress() const { return base_address_; }

		NetChannel* GetNetChannel() const { return *(NetChannel**)(base_address_ + 0x9C); }
		Vector3 GetViewAngles() const { return *(Vector3*)(base_address_ + 0x4D88); }

		void SetViewAngles(const Vector3& value) const { *(Vector3*)(base_address_ + 0x4D88) = value; }

	private:
		DWORD base_address_;
	};
}

#endif