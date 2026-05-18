#include "Setting.h"

namespace Util
{

	seconds Setting::getNewThreadAllocationTime()
	{
		return sm_newThreadAllocationTime;
	}
	uint32_t Setting::getTaskPerSecond()
	{
		return sm_taskPerSecond;
	}
	uint8_t Setting::getMaxThread()
	{
		return sm_maxThread;
	}
}
