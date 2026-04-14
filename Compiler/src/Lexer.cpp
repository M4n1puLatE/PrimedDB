#include "Lexer.h"

#include "Automata.h"

namespace Compiler
{
	class LexerRules
	{
		Automata<CharacterTypes,char> lexerAutomata;
	public:
		static CharacterTypes GetInit(char character)
		{
			if (TokenFunctions::IsChar(character) || character == '_')
				return CharacterTypes::Char;
			else if (TokenFunctions::IsOperator(character))
				return CharacterTypes::Operator;
			else if (TokenFunctions::SkipCharacter(character))
				return CharacterTypes::Skip;
			else if (TokenFunctions::IsQuote(character))
				return CharacterTypes::String;
			else if (TokenFunctions::IsDigit(character))
				return CharacterTypes::Number;
			else if (TokenFunctions::IsTerminate(character))
				return CharacterTypes::Terminate;
			else if (TokenFunctions::IsBracket(character))
				return CharacterTypes::Bracket;

			return CharacterTypes::Fail;
		}
		LexerRules()
		{
			lexerAutomata.bind(CharacterTypes::Char,
							   [](char c)
			{
							   	if (TokenFunctions::IsChar(c) || c == '_')
									return CharacterTypes::Char;
								return CharacterTypes::Fail;
			});
			lexerAutomata.bind(CharacterTypes::Char,
							   CharacterTypes::Char,
							   [](char c)
			{
				
			});


            lexerAutomata.bind(CharacterTypes::Operator,
							   CharacterTypes::Operator,
							   [](char c)
			{
				return CharacterTypes::Operator;
			});


            lexerAutomata.bind(CharacterTypes::Number,
							   CharacterTypes::Number,
							   [](char c)
			{
				return CharacterTypes::Number;
			});


            lexerAutomata.bind(CharacterTypes::String,
							   CharacterTypes::Char,
							   [](char c)
			{
				return CharacterTypes::Char;
			});
		}
		
	};
	void Lexer::reconstruct(const std::string& statement)
	{
		m_error = std::make_pair(ErrorCode::None, -1);
		m_rawTokens.clear();
        m_tokens.clear();
		tokenize(statement);
	}
	CharacterTypes Lexer::GetState(CharacterTypes init, char c)
	{
		if (c == '\n'
			//对于一个随意的空格，在没有任何词法成分的情况下会被忽略
			|| (TokenFunctions::IsSpace(c) && init == CharacterTypes::None))
			return CharacterTypes::Skip;
		if (
			//当字符为';'/'\0'是表明语句达到结尾，为Terminate状态
			c == ';' || c == '\0'
			//当字符为' '时表明当前Token已经结束，返回Terminate。但对于字符字面量，其判断截止条件为'\"',所以可以接受' '
			|| (c == ' '&& init != CharacterTypes::String)
			//当字符为'\n'时表明语句并未结束。但对于字符字面量而言是非法的，所以表明为Terminate状态
			|| (c == '\n' && init == CharacterTypes::String)
			)
			return CharacterTypes::Terminate;


		if (TokenFunctions::IsBracket(c))
			return CharacterTypes::Bracket;
		//当传入字符为'"'时表明开始了一个字符串字面或结束了一个字符串字面量
		if (TokenFunctions::IsQuote(c))
		{
			//开始一个字面量
			return CharacterTypes::String;
		}

		//当传入字符为'a'-'z'/'A'-'Z'/'下划线'时表明当前是一个字符，返回Char
		if (TokenFunctions::IsChar(c)
			|| TokenFunctions::IsUnderLine(c)
			|| (init == CharacterTypes::String && c == ' '))
			return CharacterTypes::Char;
		//当传入字符为'0'-'9'时表明当前是一个数字，返回Number
		if (TokenFunctions::IsDigit(c))
			return CharacterTypes::Number;
		//当传入字符包含于Tokens::Operators中时表明当前是一个操作符，返回Operator
		if (TokenFunctions::IsOperator(c))
			return CharacterTypes::Operator;
		//对于非字面量，'\n'是可以被接受的，会被跳过。


		return CharacterTypes::Fail;
	}
	void Lexer::generateError(CharacterTypes init, size_t pos)
	{
		if (init == CharacterTypes::String)
		{
			setError(ErrorCode::NotClosedStringLiteral, pos);
		}
		if (init == CharacterTypes::Operator)
		{
			setError(ErrorCode::InvalidOperator, pos);
		}
	}
	bool Lexer::isContinue(CharacterTypes init, char c, CharacterTypes current)
	{
		if (init == current&& current != CharacterTypes::String)
			return true;
		else
		{
			if (c == '\n')
				return false;
			if (init == CharacterTypes::String)
			{
				if (c == '\"')
					return false;
				if (current == CharacterTypes::Char)
					return true;
			}
			if (init == CharacterTypes::Char)
			{
				if (current == CharacterTypes::Operator || current == CharacterTypes::Bracket)
				{
					return false;
				}
				return true;
			}

			return false;
		}
	}
	TokenType Lexer::getTokenType(CharacterTypes state, Index current, std::string& token)
	{
		if (state == CharacterTypes::Char)
		{
			if (TokenFunctions::IsKeyword(token))
				return TokenType::Keyword;
			else if (TokenFunctions::IsLogicalOperator(token))
				return TokenType::LogicalOperator;
			else
				return TokenType::Identifier;
		}
		else if (state == CharacterTypes::Number)
		{
			return TokenType::NumberLiteral;
		}
		else if (state == CharacterTypes::Operator)
		{
			if (TokenFunctions::IsBinOperator(token))
				return TokenType::BinOperator;
			else if (TokenFunctions::IsUniOperator(token))
				return TokenType::UniOperator;
			else if (TokenFunctions::IsLogicalOperator(token))
				return TokenType::LogicalOperator;
			else
				return TokenType::Operator;
		}
		else if (state == CharacterTypes::String)
		{
			return TokenType::StringLiteral;
		}
		else if (state == CharacterTypes::Bracket)
		{
			if (token == "(")
				return TokenType::LeftParenthesis;
			else if (token == "[")
                return TokenType::LeftBracket;
            else if (token == "{")
                return TokenType::LeftCurlyBracket;
            else if (token == "]")
                return TokenType::RightBracket;
            else if (token == "}")
                return TokenType::RightCurlyBracket;
			else
				return TokenType::RightParenthesis;
		}

		return TokenType::Error;
	}
	void Lexer::tokenize(const std::string& statement)
	{
		if (statement.empty())
		{
			setError(ErrorCode::NotAValidStatement, 0);
			return;
		}
		CharacterTypes init = CharacterTypes::None, current = CharacterTypes::None;
		std::string token;
		char character;
		bool isQuoteClosed, requireSpace = false;
		for (Index n = 0; n < statement.size();)
		{

			init = GetState(init, statement[n++]);
			if (init != CharacterTypes::String)
				token = statement[n-1];
			isQuoteClosed = false;
			if (init == CharacterTypes::Skip)
			{
				requireSpace = false;
				continue;
			}

			if (init == CharacterTypes::Terminate || init == CharacterTypes::Fail)
				break;
			if (requireSpace)
			{
				setError(ErrorCode::IdentifierFormatError, static_cast<long long>(n - 1));
				break;
			}

			while (init != CharacterTypes::Bracket
				   && init != CharacterTypes::Fail
				   && current != CharacterTypes::Fail
				   && current != CharacterTypes::Terminate)
			{
				character = statement[n];
				current = GetState(init, character);
				if (current == CharacterTypes::Skip)
				{
					if (n < statement.size())
						++n;
					continue;
				}
				else if (current == CharacterTypes::Terminate)
				{
					if (n < statement.size() && character != ';')
						++n;
					break;
				}
				else if (current == CharacterTypes::Fail)
				{
					//设置字符格式错误
					setError(ErrorCode::InvalidCharacter, static_cast<long long>(n));
					break;
				}
				else if (init == CharacterTypes::Number && current == CharacterTypes::Char)
				{
					setError(ErrorCode::InvalidNumberFormat, n);
					current = CharacterTypes::Fail;
					break;
				}
				if (current == CharacterTypes::String)
				{
					isQuoteClosed = true;
					requireSpace = true;
				}

				if (!isContinue(init, character, current))
				{
					if (init == CharacterTypes::String && !isQuoteClosed)
					{
						setError(ErrorCode::NotClosedStringLiteral, static_cast<long long>(n));
					}
					++n;
					break;
				}

				token += character;
				++n;
				if (token == "\"\"")
					break;
				//没有长度超过3的运算符
				if (current == CharacterTypes::Operator && token.size() > 2)
				{
					//设置操作符格式错误
					setError(ErrorCode::OperatorFormatError, static_cast<long long>(n));
					break;
				}
			}
			//
			if (init == CharacterTypes::Fail
				|| current == CharacterTypes::Fail)
			{
				return;
			}
			m_tokens.emplace_back(getTokenType(init, n, token), m_rawTokens.size());
			m_rawTokens.emplace_back(token);
			init = current = CharacterTypes::None;
			token = "";

		}
		if (!isError())
		{
			if (m_rawTokens.size() == 1)
				setError(ErrorCode::NotAValidStatement, statement.size());
			else if (m_rawTokens.empty())
				setError(ErrorCode::EmptyStatement, statement.size());
		}

	}
	Lexer::Lexer()
		:m_error(ErrorCode::None, -1)
	{
		
	}
	Lexer::Lexer(const std::string& statement)
	{
		reconstruct(statement);
	}
	Lexer::Lexer(std::string&& statement)
	{
		reconstruct(statement);
	}
	Lexer::Lexer(Lexer&& move)noexcept
		:m_error(move.m_error), m_tokens(std::move(move.m_tokens)), m_rawTokens(std::move(move.m_rawTokens))
	{
		move.m_error = std::make_pair(ErrorCode::None, -1);
		move.m_tokens.clear();
		move.m_rawTokens.clear();
	}
	const TokenList& Lexer::getTokens()const
	{
		return m_tokens;
	}
	const StringList& Lexer::getRawTokens()const
	{
		return m_rawTokens;
	}
	bool Lexer::isError()const
	{
		return m_error.first != ErrorCode::None
		|| m_rawTokens.empty();
	}
	std::string&& Lexer::moveAt(size_t index)
	{
		return std::move(m_rawTokens[index]);
	}
	size_t Lexer::tokenSize()const
	{
		return m_tokens.size();
	}
	size_t Lexer::rawTokenSize()const
	{
		return m_rawTokens.size();
	}
	long long Lexer::getErrorPosition()const
	{
		return m_error.second;
	}
	ErrorCode Lexer::getErrorCode()const
	{
		return m_error.first;
	}
	const TokenError& Lexer::getError() const
	{
		return m_error;
	}
	void Lexer::setError(ErrorCode errorCode, long long errorPosition)
	{
		m_error = std::make_pair(errorCode, errorPosition);
	}
}
