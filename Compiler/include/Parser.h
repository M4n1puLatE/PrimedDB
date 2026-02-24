#pragma once
#include <string>
#include <Token.h>
#include <Util.h>
namespace Compiler
{
	
	class Parser
	{
		ParsingList m_parsingList;
		TokenList m_tokenList;
	public:
		static const std::vector<std::string> ValidOperators;
		Parser(const std::string& raw);
		//Throw ParseFailed Exception;
		const std::string& get(size_t index)const;
		bool parse();
		const TokenList& getTokenList()const;
		const ParsingList& getParsingList()const;
		bool empty() const;
		size_t tokenSize()const;
		size_t parsingSize()const;
	};
}
