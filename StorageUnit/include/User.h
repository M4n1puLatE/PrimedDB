#pragma once

#include <vector>

#include "StorageUnit.h"

namespace Storage::Schema
{

	enum class UserLevel:char
	{
		Visitor,
		//data:			read(yes) - write(no) - update(no)
		//table	schema: read(no) - write(no) - update(no)
		//table:		create(no) - delete(no)
		//database:		create(no) - delete(no)
		//user:			grant(no) - delete(no) - promote(no)
		//scope:		table assigned to it
		SuperVisitor,
		//data:			read(yes) - write(no) - update(no)
		//table	schema: read(no) - write(no) - update(no)
		//table:		create(no) - delete(no)
		//database:		create(no) - delete(no)
		//user:			grant(no) - delete(no) - promote(no)
		//scope:		current group or database
		Operator,
		//data:			read(yes) - write(yes) - update(yes)
		//table	schema: read(no) - write(no) - update(no)
		//table:		create(no) - delete(no)
		//database:		create(no) - delete(no)
		//user:			grant(no) - delete(no) - promote(no)
		//scope:		current group
		SuperOperator,//allow read and write every data in the same database
		Manager,//allow to create/alter table in the same database and assign table to someone
		SuperManager,//allow to create database
		Administrator,
		System
	};

	class User
	{
		char m_name[NAME_SIZE]{};
		IdType m_groupId=0;
		IdType m_userId=0;
		std::vector<IdType> m_tables;
	};
}
