#pragma once
#include <deque>
#include <memory>
#include <set>
#include <stack>
#include <string>
#include <utility>
#include <vector>

namespace Compiler
{
	enum class TokenType:unsigned char
	{
		None,
		Error,
		Terminate,
		Assign,
		Keyword,
		Identifier,
		Operator,
		UniOperator,
		BinOperator,
		LogicalOperator,
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
		SubExpression
	};

	enum class OperatorType:unsigned char
	{
		RValue,
		Add,
		Sub,
        Mul,
        Div,
        Mod,
        Pow,
		And,
		Or,
        Not,
        Equal,
        NotEqual,
		Assign,
        Greater,
        Less,
        GreaterEqual,
        LessEqual,
		All,
		Comma,
		Dot,
		Exists,
		In
	};
	template<class T>
	concept EnumType = std::is_enum_v<T>;
	using StringList = std::vector<std::string>;
	//Token类型，Token位置
	using Index = size_t;
	using Token = std::pair<TokenType, Index>;
	using TokenList = std::vector<Token>;
	enum class ErrorCode:unsigned char
	{
		None,
		IdentifierFormatError,
		InvalidCharacter,
		InvalidNumberFormat,
		InvalidOperator,
		OperatorFormatError,
		NotClosedStringLiteral,
	};
	using Element = std::pair<Index, OperatorType>;
	using Expression = std::stack<Element>;
	using TokenError = std::pair<ErrorCode, long long>;
	class Tokens
	{
	public:
		static const std::set<char> Operators;
		static const std::set<std::string_view> Keywords;
		static const std::set<std::string_view> LogicalOperators;
		static const std::set<std::string_view> UniOperators;
        static const std::set<std::string_view> BinOperators;
	};
	class TokenFunctions
	{
	public:
		template <EnumType T>
		static char ConvertToToken(T t)
		{
			return static_cast<char>(t);
		}
		template <EnumType T>
        static T ConvertToEnum(char t)
		{
			return static_cast<T>(t);
		}
		static std::string_view GetTokenType(TokenType type);
		static bool IsChar(char t);
		static bool IsUnderLine(char t);
		static bool IsQuote(char t);
		static bool IsOperator(char t);
		static bool IsDigit(char t);
		static bool IsTerminate(char t);
		static bool IsSpace(char c);

        static bool IsKeyword(const std::string& t);
		static bool IsUniOperator(const std::string& t);
        static bool IsBinOperator(const std::string& t);
		static bool IsLogicalOperator(const std::string& t);
		static void ToLower(std::string& str);
		static void ToUpper(std::string& str);
		constexpr static std::string_view GetError(ErrorCode errorCode);
	};

}
