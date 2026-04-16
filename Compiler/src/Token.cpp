#include <Token.h>
namespace Compiler
{
	const std::set<char> Tokens::Operators = {
		'=','%','<','>','&','^',
		'*','+','-','/','.','$',
		'|','!','?',':'
	};
	const std::set<char> Tokens::SkipWords=
	{
		'\0','\n','\t', '\r'
	};
	const std::set<std::string_view> Tokens::Keywords={
		"select","from","insert","where","into",
		"join","table","create","delete","update",
		"set","values","alter","drop","truncate",
		"group","order","by","asc","desc","count",
		"sum","avg","max","min","distinct","having",
		"as","on","use","primary","foreign","key",
		"unique","series","null","default",
		"between","like","in","exists","case",
		"when","then","else","end","is","any",
		"all","some","like","true","between",
		"false", "date","time","user","bxy","lrk"
	};
	const std::set<std::string_view> Tokens::LogicalOperators={
		"=",">","<",">=","<=","!=","and","or","not","xor"
	};
	const std::set<std::string_view> Tokens::UniOperators={
		"++","--","!","?"
	};
	const std::set<std::string_view> Tokens::BinOperators={
		":=","%","&","^",
		"*","+","-","/",".","$",
		"|","+=","-=","*=","/=",
		"%=","&=","|=","union","intersect",
		"minus"
	};
	const std::set<char>Tokens::Brackets = {
		'(',')','[',']','{','}'
	};
	bool TokenFunctions::IsChar(char c)
	{
		return isalpha(c);
	}
	bool TokenFunctions::IsUnderLine(char c)
	{
		return c == '_';
	}
	bool TokenFunctions::IsQuote(char c)
	{
		return c == '\"';
	}
	bool TokenFunctions::IsOperator(char c)
	{
		return Tokens::Operators.contains(c);
	}
	bool TokenFunctions::IsDigit(char c)
	{
		return isdigit(c);
	}
	bool TokenFunctions::IsSkipCharacter(char c)
	{
		return c == ' ' || c == '\n' || c == '\t' || c == '\r' || c == '\0';
	}
	bool TokenFunctions::IsSpace(char c)
	{
		return c == ' ';
	}
	bool TokenFunctions::IsTerminate(char c)
	{
		return c == ';';
	}
	bool TokenFunctions::IsBracket(char c)
	{
		return Tokens::Brackets.contains(c);
	}
	bool TokenFunctions::IsKeyword(std::string_view c)
	{
		return Tokens::Keywords.contains(c);
	}
	bool TokenFunctions::IsUniOperator(std::string_view s)
	{
		return Tokens::UniOperators.contains(s);
	}
	bool TokenFunctions::IsBinOperator(std::string_view s)
	{
		return Tokens::BinOperators.contains(s);
	}
	bool TokenFunctions::IsLogicalOperator(std::string_view s)
	{
		return Tokens::LogicalOperators.contains(s);
	}
	void TokenFunctions::ToLower(std::string& str)
	{
		for (auto& c:str)
		{
			c = tolower(c);
		}
	}
	void TokenFunctions::ToUpper(std::string& str)
	{
		for (auto& c : str)
		{
			c = toupper(c);
		}
	}
	std::string_view TokenFunctions::GetError(ErrorCode errorCode)
	{
		switch (errorCode)
		{
		case ErrorCode::IdentifierFormatError:
			return "IdentifierFormatError";
		case ErrorCode::InvalidCharacter:
			return "InvalidCharacter";
		case ErrorCode::InvalidNumberFormat:
			return "InvalidNumberFormat";
		case ErrorCode::InvalidOperator:
			return "InvalidOperator";
		case ErrorCode::NotClosedStringLiteral:
			return "NotClosedStringLiteral";
		case ErrorCode::NotAValidStatement:
			return "NotAValidStatement";
		case ErrorCode::NotClosedBracket:
			return "NotClosedBracket";
		case ErrorCode::EmptyStatement:
			return "EmptyStatement";
		}
		return "";
	}
	std::string_view TokenFunctions::GetTokenType(TokenType type)
	{
		switch (type)
		{
		case TokenType::None:
			return "None";
		case TokenType::Error:
			return "Error";
		case TokenType::Terminate:
			return "Terminate";
		case TokenType::Assign:
			return "Assign";
		case TokenType::Keyword:
			return "Keyword";
		case TokenType::Identifier:
			return "Identifier";
		case TokenType::Operator:
			return "Operator";
		case TokenType::UniOperator:
			return "UniOperator";
		case TokenType::BinOperator:
			return "BinOperator";
		case TokenType::LogicalOperator:
			return "LogicalOperator";
		case TokenType::StringLiteral:
			return "StringLiteral";
		case TokenType::NumberLiteral:
			return "NumberLiteral";
		case TokenType::Comma:
			return "Comma";
		case TokenType::Repeat:
			return "Repeat";
		case TokenType::SemiColon:
			return "SemiColon";
		case TokenType::BeginPattern:
			return "BeginPattern";
		case TokenType::EndPattern:
			return "EndPattern";
		case TokenType::Expression:
			return "Expression";
		case TokenType::LeftSquare:
			return "LeftSquare";
		case TokenType::RightSquare:
			return "RightSquare";
		case TokenType::SubExpression:
			return "SubExpression";
		default:
			return "Unknown"; // 处理未定义的枚举值
		}
	}
}