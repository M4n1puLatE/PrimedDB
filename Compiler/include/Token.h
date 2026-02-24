#pragma once
#include <deque>
#include <string>
#include <utility>
#include <vector>

namespace Compiler
{
	enum class TokenType:char
	{
		Error,
		Keyword,
		Identifier,
		UniOperator,
		BinOperator,
        StringLiteral,
        NumberLiteral,
        Comma,
		Repeat,
		SemiColon,
		BeginPattern,
		EndPattern,
        Whitespace,
		SubExpression,
        Expression,
		LeftBracket,
        RightBracket,
		Terminal
	};
	using ParsingList = std::vector<std::string>;
	//Token类型，Token位置
	using Token = std::pair<TokenType,int>;
	using Operator = char;
	using Rule = std::deque<TokenType>;
	using TokenList = std::deque<Token>;
}
