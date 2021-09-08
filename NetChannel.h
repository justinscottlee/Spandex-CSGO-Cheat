#ifndef SPANDEX_SDK_NETCHANNEL_H_
#define SPANDEX_SDK_NETCHANNEL_H_

namespace spandex
{
	class NetChannel
	{
	public:
		virtual const char* GetName(void) const;
		virtual const char* GetAddress(void) const;
		virtual float GetTime(void) const;
		virtual float GetTimeConnected(void) const;
		virtual int GetBufferSize(void) const;
		virtual int GetDataRate(void) const;
		virtual bool IsLoopback(void) const;
		virtual bool IsTimingOut(void) const;
		virtual bool IsPlayback(void) const;
		virtual float GetLatency(int flow) const;
		virtual float GetAvgLatency(int flow) const;
		virtual float GetAvgLoss(int flow) const;
		virtual float GetAvgChoke(int flow) const;
		virtual float GetAvgData(int flow) const;
		virtual float GetAvgPackets(int flow) const;
		virtual int GetTotalData(int flow) const;
		virtual int GetSequenceNr(int flow) const;
		virtual bool IsValidPacket(int flow, int frame_number) const;
		virtual float GetPacketTime(int flow, int frame_number) const;
		virtual int GetPacketBytes(int flow, int frame_number, int group) const;
		virtual bool GetStreamProgress(int flow, int* received, int* total) const;
		virtual float GetTimeSinceLastReceived(void) const;
		virtual float GetCommandInterpolationAmount(int flow, int frame_number) const;
		virtual void GetPacketResponseLatency(int flow, int frame_number, int* pnLatencyMsecs, int* pnChoke) const;
		virtual void GetRemoteFramerate(float* pflFrameTime, float* pflFrameTimeStdDev) const;
		virtual float GetTimeoutSeconds() const;
	};
}

#endif