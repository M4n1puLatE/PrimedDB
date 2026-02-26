#include <Parser.h>
#include <Exception.h>
#include <ranges>
#include <string>
#include <cctype>

namespace Compiler
{
	class ParseFailureException : public ErrorHandler::Exception<"ParseFailure">
	{
	public:
		ParseFailureException(std::string& message, 
							  std::string_view funcSig, 
							  std::string_view fileDirectory = "", 
							  long long lineNumber = 0)
			:Exception(message, funcSig, fileDirectory, lineNumber)
		{}
		ParseFailureException(std::string&& message, 
							  std::string_view funcSig, 
							  std::string_view fileDirectory = "", 
							  long long lineNumber = 0)
			:Exception(std::move(message), funcSig, fileDirectory, lineNumber)
		{}
	};
	const std::set<char> Parser::Operators={
		'=','%','<','>','&','^',
		'*','+','-','/','.','$'
	};

	const std::set<std::string_view> Parser::Keywords = {
		"select","from","insert","where",
		"into","join","table","create","delete",
		"update","set","values","alter","drop",
		"truncate","group","order","by","asc",
		"desc","count","sum","avg","max","min",
		"distinct","having","as","on","use","primary",
		"foreign","key","unique","auto_increment",
		"null","default","between","like","in","exists"
		,"case","when","then","else","end",
		"is","any","all","some","between","in","like"
		,"true","false", "date","time","user"
	};
	const std::set<std::string_view> Parser::LogicalOperators = {
		"and","or","not","nor"
	};
	static TokenType GetState(char c)
	{
		if (isalnum(c))
		{
			return TokenType::String;
		}
		else if (isdigit(c))
		{
			return TokenType::NumberLiteral;
		}
		else if (c == '(')
		{
			return TokenType::LeftBracket;
		}
		else if (c == ')')
		{
			return TokenType::RightBracket;
		}
		else if (c == ';')
		{
			return TokenType::Terminal;
		}
		else if (c == ',')
		{
			return TokenType::Comma;
		}
		else if (Parser::Operators.contains(c))
		{
			return TokenType::Operator;
		}
		else if (c == '\"')
		{
			return TokenType::StringLiteral;
		}
		else
			return TokenType::Error;
	}
	static bool isNumberLiteralState(TokenType state)
	{
		return state == TokenType::NumberLiteral;
	}
	static bool isStringLiteralState(TokenType state)
	{
		return state == TokenType::StringLiteral 
		|| isNumberLiteralState(state);
	}
	static bool PureNumberString(const std::string& str)
	{
		return std::ranges::all_of(str, isdigit);
	}
	static bool PureIdentifierString(const std::string& str)
	{
		return std::ranges::all_of(str, [](char c) {
			return isalnum(c) || c == '_';
		});
	}
	static bool PureOperatorString(const std::string& str)
	{
		return std::ranges::all_of(str, [](char c)
		{
			return Parser::Operators.contains(c);
		});
	}
	static bool isIdentifierState(TokenType state)
	{
		return state == TokenType::Identifier
		||isStringLiteralState(state);
	}

	void Parser::Lower(std::string& str)
	{
		std::ranges::for_each(str, [](char& c)
		{
			c = std::tolower(c);
		});
	}
	void Parser::tokenize()
	{
		std::string token;
		TokenType initState,current;
		if (m_raw.empty())
		{
			m_error = std::make_pair(ParserErrors::NotAStatement, 0);
		}
        for (size_t i = 0,begin = 0; i < m_raw.size();)
		{ 
        	if (std::isalnum(m_raw[i]) 
				|| m_raw[i] == '_' 
				|| m_raw[i] == '\"'
				|| Operators.contains(m_raw[i])
				|| m_raw[i] == ';'
				|| m_raw[i] == ','
				|| m_raw[i] == '('
				|| m_raw[i] == ')')
			{
				begin = i;
				token = m_raw[i++];
				initState = GetState(m_raw[i]);
				if (initState == TokenType::Error)
				{
					m_error = std::make_pair(ParserErrors::InvalidCharacter, i);
					return;
				}

				while (i < m_raw.size())
				{
					current = GetState(m_raw[i]);
					if (current == TokenType::Error)
					{
						m_error = std::make_pair(ParserErrors::InvalidCharacter, i);
						return;
					}
					if (current == initState
						||(initState == TokenType::Identifier && isIdentifierState(current))
						||(initState == TokenType::StringLiteral && isStringLiteralState(current))
						||(initState == TokenType::NumberLiteral && isNumberLiteralState(current))
                        ||(initState == TokenType::Operator && Operators.contains(token[0])))
						token += m_raw[i++];
					else
						break;
				}
				if (initState == TokenType::String)
				{
					if (Keywords.contains(token))
					{
						initState = TokenType::Keyword;
					}
					else
						initState = TokenType::Identifier;
				}
				if ((initState == TokenType::StringLiteral&&token.back() != '\'')
					|| (initState == TokenType::NumberLiteral && !PureNumberString(token)))
				{
					m_error = std::make_pair(ParserErrors::LiteralFormatError, i);
					return;
				}
				else if (initState == TokenType::Identifier&& !PureIdentifierString(token))
				{
					m_error = std::make_pair(ParserErrors::IdentifierFormatError, i);
					return;
				}
				else if (initState == TokenType::Operator
						 &&!(PureOperatorString(token)))
				{
					m_error = std::make_pair(ParserErrors::IncorrectOperator, i);
					return;
				}
				add(std::move(token));
				token.clear();
				m_tokenList.emplace_back(initState, begin);
			}
			m_error = std::make_pair(ParserErrors::InvalidCharacter, i);
			return;
		}
	}
	void Parser::operatorConvert(Token& token)
	{
		if (token.first == TokenType::Operator)
		{
			if (m_parsingList[token.second] == "="
				|| m_parsingList[token.second] == "+"
				|| m_parsingList[token.second] == "-"
				|| m_parsingList[token.second] == "*"
				|| m_parsingList[token.second] == "/"
				|| m_parsingList[token.second] == "=="
				|| m_parsingList[token.second] == "<="
				|| m_parsingList[token.second] == ">="
				|| m_parsingList[token.second] == ">"
				|| m_parsingList[token.second] == "<"
				|| m_parsingList[token.second] == "and")
			{
				token.first = TokenType::BinOperator;
			}
		}
	}
	void Parser::parse()
	{
		if (m_tokenList.size()<=3)
			m_error = std::make_pair(ParserErrors::NotAStatement, 0);
		for (size_t i = 0 ;i<m_tokenList.size();++i)
		{
			operatorConvert(m_tokenList[i]);
		}
	}

	void Parser::add(std::string&& token)
	{
		m_parsingList.emplace_back(std::move(token));
	}
	Parser::Parser(std::string& raw)
		:m_raw(raw)
	{
		Lower(m_raw);
		tokenize();
	}
	Parser::Parser(std::string&& raw)
		:m_raw(std::move(raw))
	{
		Lower(m_raw);
		tokenize();
	}
	//Throw ParseFailure Exception;
	const std::string& Parser::get(size_t index)const
	{
		if (!m_parsingList.empty()&&index<m_parsingList.size())
			return m_parsingList[index];
		throw ParseFailureException("",
			THIS_FUNC,
			THIS_FILE,
			THIS_LINE);
	}
	long long Parser::errorPosition()const
	{
		
		if (m_error.first != ParserErrors::None)
		{
			return m_error.second;
		}
		else
			return -1;
	}
	
	const TokenList& Parser::getTokenList()const
	{
		return m_tokenList;
	}
	const ParsingList& Parser::getParsingList()const
	{
		return m_parsingList;
	}
	bool Parser::fail() const
	{
		return m_error.first == ParserErrors::None;
	}
	size_t Parser::tokenSize()const
	{
		return m_tokenList.size();
	}
	size_t Parser::parsingSize()const
	{
		return m_parsingList.size();
	}
}
