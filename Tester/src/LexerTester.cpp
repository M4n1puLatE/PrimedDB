#include "LexerTester.h"

#include "Parser.h"
namespace Tester
{
	void LexerTester::init()
	{
		add("CompilerTest", TEST_FUNCTION(LexerTester::CompilerTest));
		enablePrecise();
	}

	bool LexerTester::CompilerTest()
	{
		string str,p;
		while (std::getline(std::cin,str))
		{
			p = str;
			if (str == "finish")
				break;
			Compiler::Parser lexer(std::move(str));
			str.clear();
			if (!lexer.isError())
			{

				auto& tokens = lexer.getTokens();
				cout << '[';
				for (auto& t : tokens)
				{
					cout << Compiler::TokenFunctions::GetTokenType(t->type()) << ",";
				}
				cout << ']' << endl;
			}
			else
			{
				cout << Compiler::TokenFunctions::GetError(lexer.getErrorCode()) << " at " << lexer.getErrorPosition() << endl;
				p.insert(lexer.getErrorPosition(), "%");
				cout<< p << endl;
			}

		}
		
		return true;
	}
}
