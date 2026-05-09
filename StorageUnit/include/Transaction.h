#pragma once
#include <stack>
#include <string>
#include <vector>

namespace StorageUnit::Operations
{
	enum class OperationType
	{
		None,
		FullTable,
		Scan,
		Condition,
		Bitset,
		Hash,
		Index,
		Range,
		Column,
		Join
	};
	class Operation
	{
	public:
		Operation(OperationType action);
        Operation(const Operation& operation)=default;
		virtual OperationType getType()const = 0;
	};
	class Transaction
	{ 
		std::string m_id;
        std::stack<Operation> m_finished;
		std::stack<Operation> m_unfinished;
	};
}
