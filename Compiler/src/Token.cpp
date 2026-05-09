#include <Token.h>
namespace Compiler
{
	///////////////////////////////////////////////////////////////
///
///							Token
///
///////////////////////////////////////////////////////////////

	bool Token::valid(std::string_view)const
	{
		return true;
	}
	bool Token::equals(const Token& token) const
	{
		return type() == token.type();
	}
	bool Token::operator==(const Token& token) const
	{
		return equals(token);
	}
	const std::set<char> Tokens::Operators = {
		'=','%','<','>','&','^',
		'*','+','-','/','.','$',
		'|','!','?',':',',','(',
		')','[',']','{','}'
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
		"false", "date","time","user","bxy","lrk",
		"commit","undo","redo","rollback","transaction","grant",
		"level","administrator","manager","visitor","super","restrict"
	};
	const std::set<std::string_view> Tokens::LogicalOperators={
		"=",">","<",">=","<=","!=","and","or","not","xor"
	};
	const std::set<std::string_view> Tokens::UniOperators={
		"++","--","!","?"
	};
	const std::set<std::string_view> Tokens::BinOperators={
		":=","%","&","^",":",",",
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
		return c== ' ' || Tokens::SkipWords.contains(c);
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
		case ErrorCode::None:
			return "None";
		case ErrorCode::IdentifierFormatError:
			return "IdentifierFormatError";
		case ErrorCode::InvalidCharacter:
			return "InvalidCharacter";
		case ErrorCode::InvalidNumberFormat:
			return "InvalidNumberFormat";
		case ErrorCode::InvalidOperator:
			return "InvalidOperator";
		case ErrorCode::OperatorFormatError:
			return "OperatorFormatError";
		case ErrorCode::NotClosedStringLiteral:
			return "NotClosedStringLiteral";
		case ErrorCode::NotAValidStatement:
			return "NotAValidStatement";
		case ErrorCode::NotClosedBracket:
			return "NotClosedBracket";
		case ErrorCode::NotRecognizableToken:
			return "NotRecognizableToken";
		case ErrorCode::MissingLeftParenthesis:
			return "MissingLeftParenthesis";
		case ErrorCode::EmptyStatement:
			return "EmptyStatement";
		}
		return "";
	}
	std::string_view TokenFunctions::GetTokenType(TokenType type)
	{
		switch (type)
		{
		case TokenType::Error:
			return "Error";
		case TokenType::None:
			return "None";
		case TokenType::Terminate:
			return "Terminate";
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
		case TokenType::DoubleLiteral:
			return "DoubleLiteral";
		case TokenType::IntegerLiteral:
			return "IntegerLiteral";
		case TokenType::Expression:
			return "Expression";
		case TokenType::Repeat:
			return "Repeat";
		case TokenType::BeginPattern:
			return "BeginPattern";
		case TokenType::EndPattern:
			return "EndPattern";
		case TokenType::Assign:
			return "Assign";
		case TokenType::Comma:
			return "Comma";
		case TokenType::SemiColon:
			return "SemiColon";
		case TokenType::LeftSquare:
			return "LeftSquare";
		case TokenType::RightSquare:
			return "RightSquare";
		case TokenType::LeftBracket:
			return "LeftBracket";
		case TokenType::RightBracket:
			return "RightBracket";
		case TokenType::LeftCurly:
			return "LeftCurly";
		case TokenType::RightCurly:
			return "RightCurly";
		case TokenType::SubExpression:
			return "SubExpression";
		case TokenType::SubQuery:
			return "SubQuery";
		case TokenType::Select:
			return "Select";
		case TokenType::From:
			return "From";
		case TokenType::Insert:
			return "Insert";
		case TokenType::Where:
			return "Where";
		case TokenType::Into:
			return "Into";
		case TokenType::Join:
			return "Join";
		case TokenType::Table:
			return "Table";
		case TokenType::Create:
			return "Create";
		case TokenType::Delete:
			return "Delete";
		case TokenType::Update:
			return "Update";
		case TokenType::Set:
			return "Set";
		case TokenType::Values:
			return "Values";
		case TokenType::Alter:
			return "Alter";
		case TokenType::Drop:
			return "Drop";
		case TokenType::Truncate:
			return "Truncate";
		case TokenType::Group:
			return "Group";
		case TokenType::Order:
			return "Order";
		case TokenType::By:
			return "By";
		case TokenType::Asc:
			return "Asc";
		case TokenType::Desc:
			return "Desc";
		case TokenType::Count:
			return "Count";
		case TokenType::Sum:
			return "Sum";
		case TokenType::Avg:
			return "Avg";
		case TokenType::Max:
			return "Max";
		case TokenType::Min:
			return "Min";
		case TokenType::Distinct:
			return "Distinct";
		case TokenType::Having:
			return "Having";
		case TokenType::As:
			return "As";
		case TokenType::On:
			return "On";
		case TokenType::Use:
			return "Use";
		case TokenType::Primary:
			return "Primary";
		case TokenType::Foreign:
			return "Foreign";
		case TokenType::Key:
			return "Key";
		case TokenType::Unique:
			return "Unique";
		case TokenType::Series:
			return "Series";
		case TokenType::Null:
			return "Null";
		case TokenType::Default:
			return "Default";
		case TokenType::Between:
			return "Between";
		case TokenType::Like:
			return "Like";
		case TokenType::In:
			return "In";
		case TokenType::Exists:
			return "Exists";
		case TokenType::Case:
			return "Case";
		case TokenType::When:
			return "When";
		case TokenType::Then:
			return "Then";
		case TokenType::Else:
			return "Else";
		case TokenType::End:
			return "End";
		case TokenType::Is:
			return "Is";
		case TokenType::Any:
			return "Any";
		case TokenType::All:
			return "All";
		case TokenType::Some:
			return "Some";
		case TokenType::True:
			return "True";
		case TokenType::False:
			return "False";
		case TokenType::Date:
			return "Date";
		case TokenType::Time:
			return "Time";
		case TokenType::User:
			return "User";
		case TokenType::Lrk:
			return "Lrk";
		case TokenType::Bxy:
			return "Bxy";
		case TokenType::RValue:
			return "RValue";
		case TokenType::Add:
			return "Add";
		case TokenType::Sub:
			return "Sub";
		case TokenType::Mul:
			return "Mul";
		case TokenType::Div:
			return "Div";
		case TokenType::Mod:
			return "Mod";
		case TokenType::Pow:
			return "Pow";
		case TokenType::And:
			return "And";
		case TokenType::Or:
			return "Or";
		case TokenType::Not:
			return "Not";
		case TokenType::Equal:
			return "Equal";
		case TokenType::BitAnd:
			return "BitAnd";
		case TokenType::BitOr:
			return "BitOr";
		case TokenType::NotEqual:
			return "NotEqual";
		case TokenType::Greater:
			return "Greater";
		case TokenType::Less:
			return "Less";
		case TokenType::GreaterEqual:
			return "GreaterEqual";
		case TokenType::LessEqual:
			return "LessEqual";
		case TokenType::Dot:
			return "Dot";
		case TokenType::Condition:
			return "Condition";
		case TokenType::Union:
			return "Union";
		case TokenType::Intersect:
			return "Intersect";
		case TokenType::Minus:
			return "Minus";
		case TokenType::IndexOf:
			return "IndexOf";
		case TokenType::Statements:
			return "Statements";
		case TokenType::AddAssign:
			return "AddAssign";
		case TokenType::SubAssign:
			return "SubAssign";
		case TokenType::MulAssign:
			return "MulAssign";
		case TokenType::DivAssign:
			return "DivAssign";
		case TokenType::ModAssign:
			return "ModAssign";
		case TokenType::Pp:
			return "Pp";
		case TokenType::Mm:
			return "Mm";
		case TokenType::What:
			return "What";
		case TokenType::Emphasize:
			return "Emphasize";
		case TokenType::Xor:
			return "Xor";
		default:
			return "Unknown"; // 处理未定义的枚举值
		}
	}
}