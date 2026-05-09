#pragma once
#include <string>
#include <vector>
#include "Block.h"
#include "StorageUnit.h"
namespace StorageUnit::Memory
{
    class Extent
    { 
        const std::string m_directory;
        IdType m_id;
        std::vector<Block*> blocks;
        long long m_active=0;
        IdType m_ownerTable=0;
        IdType m_blockIdGenerator = 1;
    };
}