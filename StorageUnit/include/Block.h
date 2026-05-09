#pragma once
#include "StorageUnit.h"

namespace StorageUnit::Memory
{
	constexpr unsigned short KILOBYTE = 1024;
    constexpr unsigned short BLOCK_SIZE = 8 * KILOBYTE;
	class Block
	{
		IdType m_blockId=0;
        char m_data[BLOCK_SIZE]{};
		IdType m_extentId=0;
	};
}
