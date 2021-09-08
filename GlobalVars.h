#ifndef SPANDEX_SDK_GLOBALVARS_H_
#define SPANDEX_SDK_GLOBALVARS_H_

namespace spandex
{
	struct GlobalVars
	{
		float m_flRealTime;
		int m_iFrameCount;
		float m_flAbsoluteFrameTime;
		float m_flAbsoluteFrameStartTimeStdDev;
		float m_flCurrentTime;
		float m_flFrameTime;
		int m_iMaxClients;
		int m_iTickCount;
		float m_flIntervalPerTick;
		float m_flInterpolationAmount;
		int m_iSimTicksThisFrame;
		int m_iNetworkProtocol;
		void* m_pSaveData;
		bool m_bClient;
		int m_nTimestampNetworkingBase;
		int m_nTimestampRandomizeWindow;
	};
}

#endif