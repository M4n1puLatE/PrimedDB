#pragma once
#include <thread>

#include "Singleton.h"
#include "Timer.h"

namespace Util
{
	
	class Setting : public Singleton<Setting>
	{
		static constexpr uint16_t KB = 1024;
		//最大线程数量
		uint8_t sm_maxThread = std::thread::hardware_concurrency();
		//块大小，blockSize*KB
		uint32_t sm_blockSize = 4 * KB;
		uint16_t sm_blockNumber = -1;
		seconds sm_newThreadAllocationTime = seconds(10);
		uint32_t sm_taskPerSecond = 50;

	public:
		seconds getNewThreadAllocationTime();
		uint32_t getTaskPerSecond();
		uint8_t getMaxThread();
	};
}
