#include "Lexer.h"
namespace Compiler
{
	CharStates Lexer::GetState(CharStates init,char c)
	{
		if (c == ';'||c == '\0'
			|| (TokenFunctions::IsSpace(c)&& init != CharStates::String)
			|| (c == '\n' && init == CharStates::String))
			return CharStates::Terminate;
		if (TokenFunctions::IsQuote(c))
			return CharStates::String;
		if (TokenFunctions::IsChar(c) || TokenFunctions::IsUnderLine(c))
			return CharStates::Char;
		if (TokenFunctions::IsDigit(c))
			return CharStates::Number;
		if (TokenFunctions::IsOperator(c))
			return CharStates::Operator;
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
			}
			if (init == CharStates::Char)
			{
				if (current == CharStates::Operator)
				{
					return false;
				}
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
			else
				return TokenType::Operator;
		}
		else if (state == CharStates::String)
		{
			if (token.back() == '\"')
			{
				return TokenType::StringLiteral;
			}
			else
			{
				setError(ErrorCode::NotClosedStringLiteral, static_cast<long long>(current));
				return TokenType::Error;
			}
		}
		return TokenType::Error;
	}
	void Lexer::tokenize(const std::string& statement)
	{
		CharStates init = CharStates::None,current = CharStates::None;
		std::string token;
		char character;
		for (Index n = 0;n<statement.size();)
		{
			token = statement[n];
			init = GetState(init,statement[n++]);
			while (current != CharStates::Error
				   && current != CharStates::Terminate)
			{
				character = statement[n];
				current = GetState(init,character);
				
				if (current == CharStates::Skip)
				{
					if (n < statement.size())
						++n;
					continue;
				}
				else if (current == CharStates::Terminate)
				{
					if (n<statement.size())
						++n;
					break;
				}
				else if (current == CharStates::Error)
				{
					setError(ErrorCode::InvalidCharacter, static_cast<long long>(n));
					break;
				}

				if (!isContinue(init, character, current))
					break;
				token += character;
				++n;
				if (current == CharStates::Operator && token.size() > 2)
				{
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
			m_rawTokens.emplace_back(std::move(token));
			init = current = CharStates::None;
			token.clear();
		}
	}

	Lexer::Lexer(const std::string& statement)
		:m_error(ErrorCode::None,-1)
	{
        tokenize(statement);
	}
	Lexer::Lexer(std::string&& statement)
		:m_error(ErrorCode::None, -1)
	{
		tokenize(statement);
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
		return m_error.first != ErrorCode::None;
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