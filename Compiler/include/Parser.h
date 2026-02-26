#pragma once
#include <set>
#include <string>
#include <Token.h>
#include <Util.h>
namespace Compiler
{
	enum class ParserErrors
	{
		None,
		NotAStatement,
		NotAKeyword,
        NotAnOperator,
		IncorrectOperator,
		IdentifierFormatError,
        LiteralFormatError,
		InvalidCharacter
	};
	
	class Parser
	{
		using ParserError = std::pair<ParserErrors, size_t>;
		std::string m_raw;
		TokenList m_tokenList;
		ParsingList m_parsingList;
		ParserError m_error = std::make_pair(ParserErrors::None, 0);
	private:
		void tokenize();
		void parse();
		void operatorConvert(Token& token);
		void add(std::string&& token);
		static void Lower(std::string& str);
	public:
		static const std::set<char> Operators;
		static const std::set<std::string_view> Keywords;
		static const std::set<std::string_view> LogicalOperators;
		Parser() = default;
		Parser(std::string& raw);
		Parser(std::string&& raw);
		//Throw ParseFailed Exception;
		const std::string& get(size_t index)const;
		long long errorPosition()const;
		const TokenList& getTokenList()const;
		const ParsingList& getParsingList()const;
		bool fail() const;
		size_t tokenSize()const;
		size_t parsingSize()const;
	};
}
