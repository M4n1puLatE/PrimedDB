#pragma once
#include <Token.h>

namespace Compiler
{
	enum class CharStates:unsigned char
	{
		None,
		Error,
		Skip,
		Terminate,
		Char,//Keyword/Identifier/Literal
		Number,//NumberLiteral
		String,//StringLiteral
		Bracket,
		Operator,
	};

	class Lexer
	{
		TokenList m_tokens;
		StringList m_rawTokens;
		TokenError m_error;
		void tokenize(const std::string& statement);
		static CharStates GetState(CharStates init,char c);
		bool isContinue(CharStates init, char c,CharStates current);
		TokenType getTokenType(CharStates state, Index current ,std::string& token);
		void generateError(CharStates init, size_t pos);
	public:
		Lexer();
		Lexer(const std::string& statement);
		Lexer(std::string&& statement);
		Lexer(Lexer&& move)noexcept;
		const TokenList& getTokens()const;
		const StringList& getRawTokens()const;
		bool isError()const;
		std::string&& moveAt(size_t index);
		size_t tokenSize()const;
        size_t rawTokenSize()const;
        long long getErrorPosition()const;
		ErrorCode getErrorCode()const;
		void reconstruct(const std::string& statement);
		void setError(ErrorCode errorCode, long long errorPosition);
	};
}
