#pragma once
#include <string>

#include <Lexer.h>

namespace Compiler
{
	enum class DataSetCombination:char
	{
        None,
		Condition,
		Union,
		Intersect,
		Except,
		Join
	};
	using Element = std::pair<Index, TokenType>;
	using Expression = std::stack<Element>;
	using DataSet = std::pair<std::string, DataSetCombination>;
	class Statement
	{
		std::stack<DataSet> m_dataSets;
		TokenType m_operation;
        Expression m_expression;

	};
	using ParsedToken = std::pair<TokenType, std::string>;
	using ParsingList = std::vector<ParsedToken>;
	class Parser
	{
		Lexer m_lexer;
		ParsingList m_list;

		void parse();
	public:
		Parser(const std::string& statement);
		Parser(std::string&& statement);
		Parser(Lexer&& lexer);
		Parser(Parser&& move) noexcept;
		static TokenType GetKeyword(const std::string& token);
		static TokenType GetBinOperator(const std::string& token);
		static TokenType GetUniOperator(const std::string& token);
		static TokenType GetLogicalOperator(const std::string& token);
		const ParsingList& getList()const;
        const Lexer& getLexer()const;
		const TokenError& getError()const;
	};
}
