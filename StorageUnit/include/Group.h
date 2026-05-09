#pragma once

#include <bitset>

#include "StorageUnit.h"
namespace StorageUnit::Schema
{
	enum class Permission
	{
		//Data
		Read,
		Update,
		AddDelete,//cover lower levels
		//Table
		CreateTable,
        DropTable,
		ReadTable,
		AlterTable,
		//Database
        CreateDatabase,
        DropDatabase,
        AlterDatabase,
		//User
		ReadUser,
        AlterUser,
		ManageUsers,
	};
	class Group
	{
		char m_groupName[NAME_SIZE]{};
		IdType m_groupId;
		IdType m_creatorId;
		std::bitset<12> m_allowedActions;
	};
}

