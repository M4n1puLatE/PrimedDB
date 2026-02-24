#include <Parser.h>
#include <Exception.h>
namespace Compiler
{
	class ParseFailureException : public ErrorHandler::Exception<"ParseFailure">
	{
	public:
		ParseFailureException(std::string& message, std::string_view funcSig, std::string_view fileDirectory = "", long long lineNumber = 0)
			:Exception(message, funcSig, fileDirectory, lineNumber)
		{}
		ParseFailureException(std::string&& message, std::string_view funcSig, std::string_view fileDirectory = "", long long lineNumber = 0)
			:Exception(std::move(message), funcSig, fileDirectory, lineNumber)
		{}
	};
	const std::vector<std::string> Parser::ValidOperators={
		"=","%","<",">","<=",">=","==","&&"
		,"||","!","?","&","|","^"
		,"*","+","-","/"
	};
	Parser::Parser(const std::string& raw)
		:m_parsingList(Util::Util::SplitString(raw, ' '))
	{}
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
	bool Parser::parse()
	{
		
		return false;
	}
	const TokenList& Parser::getTokenList()const
	{
		return m_tokenList;
	}
	const ParsingList& Parser::getParsingList()const
	{
		return m_parsingList;
	}
	bool Parser::empty() const
	{
		return m_parsingList.empty();
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
