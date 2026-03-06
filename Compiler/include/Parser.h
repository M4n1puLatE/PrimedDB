#pragma once
#include <string>

#include <Lexer.h>

namespace Compiler
{
	enum class Keywords:char
	{
	};
	enum class Operators:char
	{
	};
	
	class Parser
	{
		using IdentifierList = std::vector<std::string>;
		Lexer m_lexer;
	public:
		Parser(const std::string& statement);
		Parser(std::string&& statement);
		Parser(Lexer&& lexer);
		Parser(Parser&& move) noexcept;
	};
}
