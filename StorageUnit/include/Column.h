#pragma once
#include <memory>
#include <string_view>
#include "StorageUnit.h"
#include "Table.h"

namespace StorageUnit::Schema
{
	enum class DataType:char
	{
		NONE,
		INT,
		CHAR,
		VARCHAR,
		TEXT,
		BOOLEAN,
		DATE,
		TIME,
		TIMESTAMP,
		BLOB,
		DECIMAL,
		FLOAT,
		DOUBLE,
		SERIAL,
		UNKNOWN
	};
	class Table;
	class Column:public std::enable_shared_from_this<Column>
	{
		using byte_size = unsigned short;
		static byte_size DefaultBytes(DataType type);
		char m_columnName[NAME_SIZE];
		DataType m_type=DataType::NONE;
		byte_size m_bytes;
		IdType m_owner=0;
	public:
		Column(Table* owner,std::string_view name, DataType type, unsigned short bytes);
		Column(Table* owner,std::string_view name, DataType type);
		Column(const Column& copy);
		Column(Column&& move)noexcept;
		std::string_view getName() const;
		bool rename(std::string_view newName);
		DataType getType() const;
		byte_size getBytes() const;
		void resize(byte_size bytes);
		void changeType(DataType type);


		bool operator==(const Column& other);
        Column& operator=(const Column& other);
        Column& operator=(Column&& other) noexcept;
	};
}
