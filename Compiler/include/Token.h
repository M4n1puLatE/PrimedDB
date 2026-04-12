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
		Keyword,
		Identifier,
		Operator,
		UniOperator,
		BinOperator,
		LogicalOperator,
		StringLiteral,
		NumberLiteral,
		Expression,
		Repeat,
		BeginPattern,
		EndPattern,
		Assign,
		Comma,
		SemiColon,
		LeftBracket,
		RightBracket,
		LeftParenthesis,
        RightParenthesis,
		LeftCurlyBracket,
		RightCurlyBracket,
		SubExpression,
		SubQuery,

		//keywords
		Select, 
		From, 
		Insert, 
		Where, 
		Into,
		Join, 
		Table, 
		Create, 
		Delete, 
		Update,
		Set, 
		Values, 
		Alter, 
		Drop, 
		Truncate,
		Group, 
		Order, 
		By, 
		Asc, 
		Desc, 
		Count,
		Sum, 
		Avg, 
		Max, 
		Min, 
		Distinct, 
		Having,
		As, 
		On, 
		Use, 
		Primary, 
		Foreign, 
		Key,
		Unique,
		Series, 
		Null, 
		Default,
		Between, 
		Like, 
		In, 
		Exists, 
		Case,
		When, 
		Then, 
		Else, 
		End, 
		Is, 
		Any,
		All, 
		Some, 
		True, 
		False, 
		Date,
		Time, 
		User,
		//Operators
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
		BitAnd,
        BitOr,
		NotEqual,
		Greater,
		Less,
		GreaterEqual,
		LessEqual,
		Dot,
		Condition,
		Union,
		Intersect,
		Minus,
		IndexOf,
		Statements,
		AddAssign,
        SubAssign,
        MulAssign,
        DivAssign,
        ModAssign,
		Pp,
		Mm,
		What,
		Emphasize,
		Xor,
		Lrk,
		Bxy,
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
		NotAValidStatement,
		NotClosedBracket,
		MissingLeftParenthesis,
		EmptyStatement,
	};
	

	using TokenError = std::pair<ErrorCode, long long>;
	class Tokens
	{
	public:
		static const std::set<char> Operators;
		static const std::set<std::string_view> Keywords;
		static const std::set<std::string_view> LogicalOperators;
		static const std::set<std::string_view> UniOperators;
        static const std::set<std::string_view> BinOperators;
		static const std::set<char> Brackets;
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
		static bool IsChar(char c);
		static bool IsUnderLine(char c);
		static bool IsQuote(char c);
		static bool IsOperator(char c);
		static bool IsDigit(char c);
		static bool IsTerminate(char c);
		static bool IsSpace(char c);
		static bool IsBracket(char c);

        static bool IsKeyword(const std::string& str);
		static bool IsUniOperator(const std::string& str);
        static bool IsBinOperator(const std::string& str);
		static bool IsLogicalOperator(const std::string& str);
		static void ToLower(std::string& str);
		static void ToUpper(std::string& str);
		static std::string_view GetError(ErrorCode errorCode);
	};
	enum class CharacterTypes
	{
		
	};

}
