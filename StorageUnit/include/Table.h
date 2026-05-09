#pragma once
#include <memory>
#include <optional>
#include <vector>
#include <string_view>
#include "Extents.h"
#include "StorageUnit.h"
#include "Column.h"
namespace StorageUnit::Schema
{
	class Restriction
	{
		IdType m_tableId = 0;
		IdType m_userId	= 0;
		BitSet64 m_restrictions = 0;
		Restriction(IdType tableId, IdType userId, BitSet64 restrictions);
		Restriction(IdType tableId, IdType userId, std::vector<char> which);
		Restriction(const Restriction& restriction)=default;
		static Restriction create(IdType tableId, IdType userId, std::vector<char> which);
		static Restriction create(IdType tableId, IdType userId, BitSet64 restrictions);
		void changeUser(IdType userId);

	};
	class Table:public std::enable_shared_from_this<Table>
	{ 
		char m_name[NAME_SIZE];
        IdType m_tableId = 0;
		IdType m_owner = 0;
        IdType m_recordCount = 0;
		BitSet64 m_primaryKeys = 0;
		BitSet64 m_foreignKeys = 0;
		BitSet64 m_uniqueKeys = 0;
		std::vector<Column> m_columns{};
		std::vector<Memory::Extent> m_extents{};
	public:
		Table(std::string_view name, IdType tableId);
		Table(std::string_view name, IdType tableId,std::vector<Column>&& move);
		Table(Table&& move) noexcept;
		//获取当前表ID
		IdType getTableId() const;
		//获取当前记录数量
		IdType getRecordCount() const;
        std::string_view getName() const;
		bool isPrimaryKey(unsigned short index) const;
		bool isPrimaryKey(std::string_view index) const;
		bool isUniqueKey(std::string_view name) const;
		bool isUniqueKey(unsigned short index) const;
		bool isForeignKey(std::string_view name) const;
		bool isForeignKey(unsigned short index) const;
		unsigned char getColumnCount() const;
		IdType getId() const;
		IdType getOwner() const;
		IdType size() const;
		IdType getByteSize()const;

		bool addColumn(std::string_view name, ColumnType type, bool isKey);
		std::optional<std::reference_wrapper<Column>> getColumn(std::string_view name);
	};
}
