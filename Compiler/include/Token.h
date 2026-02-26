#pragma once
#include <deque>
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace Compiler
{
	enum class TokenType:char
	{
		None,
		Assign,
		Error,
		Keyword,
		Identifier,
		Operator,
		UniOperator,
		BinOperator,
		String,
        StringLiteral,
        NumberLiteral,
        Comma,
		Repeat,
		SemiColon,
		BeginPattern,
		EndPattern,
        Expression,
		LeftBracket,
        RightBracket,
		Terminal
	};
	using ParsingList = std::vector<std::string>;
	//Token类型，Token位置
	using Token = std::pair<TokenType,long long>;
	using Operator = char;
	using Rule = std::deque<TokenType>;
	using TokenList = std::deque<Token>;
	class Expression
	{
		Token m_left;
		Operator m_op;
	public:
		Expression(Token left, Operator op, std::unique_ptr<Expression> right);
		
	};
}
