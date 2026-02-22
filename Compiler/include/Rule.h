#pragma once
namespace Compiler
{
	enum class RuleType:char
	{
		None,
		Terminal,
		NonTerminal,
		Epsilon,
		Error
	};
	enum class OperatorType :char
	{
		Add,
		Subtract,
		Multiply,
		Divide,
		Equals,
		LessThan,
		GreaterThan,
		LessThanOrEqual,
		GreaterThanOrEqual,
		NotEquals,
		And,
		Or,
		Not,
		Xor,
	};
	enum class TokenType:char
	{
		Error,
		Keyword,
		Identifier,
		Operator,
        StringLiteral,
        NumberLiteral,
        Comma,
		Repeat,
		BeginPattern,
		EndPattern,
        Whitespace,
		SubExpression,
        Expression,
		LeftBracket,
        RightBracket,
		Terminal
	};
	class Rule
	{
		
	};
}
