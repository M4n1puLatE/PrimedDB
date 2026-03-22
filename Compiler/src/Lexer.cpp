#include "Lexer.h"
namespace Compiler
{
	void Lexer::reconstruct(const std::string& statement)
	{
		m_error = std::make_pair(ErrorCode::None, -1);
		tokenize(statement);
	}
	CharStates Lexer::GetState(CharStates init, char c)
	{
		//当字符为';'/'\0'是表明语句达到结尾，为Terminate状态
		//当字符为'\n'时表明语句并未结束。但对于字符字面量而言是非法的，所以表明为Terminate状态
		//当字符为' '时表明当前Token已经结束，返回Terminate。但对于字符字面量，其判断截止条件为'\"',所以可以接受' '
		if (c == ';' || c == '\0'
			|| (TokenFunctions::IsSpace(c) && init != CharStates::String)
			|| (c == '\n' && init == CharStates::String))
			return CharStates::Terminate;
		if (TokenFunctions::IsBracket(c))
			return CharStates::Bracket;
		//当传入字符为'"'时表明开始了一个字符串字面或结束了一个字符串字面量，因此返回String
		if (TokenFunctions::IsQuote(c))
			return CharStates::String;
		//当传入字符为'a'-'z'/'A'-'Z'/'下划线'时表明当前是一个字符，返回Char
		if (TokenFunctions::IsChar(c)
			|| TokenFunctions::IsUnderLine(c)
			|| (init == CharStates::String && c == ' '))
			return CharStates::Char;
		//当传入字符为'0'-'9'时表明当前是一个数字，返回Number
		if (TokenFunctions::IsDigit(c))
			return CharStates::Number;
		//当传入字符包含于Tokens::Operators中时表明当前是一个操作符，返回Operator
		if (TokenFunctions::IsOperator(c))
			return CharStates::Operator;
		//对于非字面量，'\n'是可以被接受的，不过会被跳过。
		if (c == '\n')
			return CharStates::Skip;

		return CharStates::Error;
	}
	void Lexer::generateError(CharStates init, size_t pos)
	{
		if (init == CharStates::String)
		{
			setError(ErrorCode::NotClosedStringLiteral, pos);
		}
		if (init == CharStates::Operator)
		{
			setError(ErrorCode::InvalidOperator, pos);
		}
	}
	bool Lexer::isContinue(CharStates init, char c, CharStates current)
	{
		if (init == current)
			return true;
		else
		{
			if (c == '\n')
				return false;
			if (init == CharStates::String)
			{
				if (c == '\"')
					return false;
				if (current == CharStates::Char)
					return true;
			}
			if (init == CharStates::Char)
			{
				if (current == CharStates::Operator || current == CharStates::Bracket)
				{
					return false;
				}
				return true;
			}

			return false;
		}
	}
	TokenType Lexer::getTokenType(CharStates state, Index current, std::string& token)
	{
		if (state == CharStates::Char)
		{
			if (TokenFunctions::IsKeyword(token))
				return TokenType::Keyword;
			else if (TokenFunctions::IsLogicalOperator(token))
				return TokenType::LogicalOperator;
			else
				return TokenType::Identifier;
		}
		else if (state == CharStates::Number)
		{
			return TokenType::NumberLiteral;
		}
		else if (state == CharStates::Operator)
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
		else if (state == CharStates::String)
		{
			if (token.back() == '\"' && token.size() > 1)
			{
				return TokenType::StringLiteral;
			}
			else
			{
				setError(ErrorCode::NotClosedStringLiteral, static_cast<long long>(current));
				return TokenType::Error;
			}
		}
		else if (state == CharStates::Bracket)
		{
			if (token == "(" || token == "[" || token == "{")
				return TokenType::LeftBracket;
			else
				return TokenType::RightBracket;
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
		CharStates init = CharStates::None, current = CharStates::None;
		std::string token;
		char character;
		for (Index n = 0; n < statement.size();)
		{
			token = statement[n];
			init = GetState(init, statement[n++]);
			if (init == CharStates::Terminate)
				break;
			while (init != CharStates::Bracket
				   && init != CharStates::Error
				   && current != CharStates::Error
				   && current != CharStates::Terminate)
			{
				character = statement[n];
				current = GetState(init, character);

				if (current == CharStates::Skip)
				{
					if (n < statement.size())
						++n;
					continue;
				}
				else if (current == CharStates::Terminate)
				{
					if (n < statement.size() && character != ';')
						++n;
					break;
				}
				else if (current == CharStates::Error)
				{
					//设置字符格式错误
					setError(ErrorCode::InvalidCharacter, static_cast<long long>(n));
					break;
				}
				else if (init == CharStates::Number && current == CharStates::Char)
				{
					setError(ErrorCode::InvalidNumberFormat, n);
					current = CharStates::Error;
					break;
				}
				if (!isContinue(init, character, current))
					break;
				token += character;
				++n;
				if (token == "\"\"")
					break;
				//没有长度超过3的运算符
				if (current == CharStates::Operator && token.size() > 2)
				{
					//设置操作符格式错误
					setError(ErrorCode::OperatorFormatError, static_cast<long long>(n));
					break;
				}
			}
			//
			if (init == CharStates::Error
				|| current == CharStates::Error)
			{
				return;
			}
			m_tokens.emplace_back(getTokenType(init, n, token), m_rawTokens.size());
			m_rawTokens.emplace_back(token);
			init = current = CharStates::None;
			token = "";

		}
		if (m_rawTokens.size() == 1)
			setError(ErrorCode::NotAValidStatement, statement.size());
		else if (m_rawTokens.empty())
			setError(ErrorCode::EmptyStatement, statement.size());
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
	void Lexer::setError(ErrorCode errorCode, long long errorPosition)
	{
		m_error = std::make_pair(errorCode, errorPosition);
	}
}