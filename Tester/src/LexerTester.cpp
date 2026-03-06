#include "LexerTester.h"

#include "Lexer.h"
namespace Tester
{
	void LexerTester::init()
	{
		add("CompilerTest", TEST_FUNCTION(LexerTester::CompilerTest));
		enablePrecise();
	}

	bool LexerTester::CompilerTest()
	{
		string str;
		while (std::getline(std::cin,str))
		{
			if (str == "finish")
				break;
			Compiler::Lexer lexer(str);
			if (!lexer.isError())
			{
				printVector(lexer.getRawTokens());
				auto& tokens = lexer.getTokens();
				cout << '[';
				for (auto& t : tokens)
				{
					cout << Compiler::TokenFunctions::GetTokenType(t.first) << ",";
				}
				cout << ']' << endl;
			}
			else
			{
				cout << Compiler::TokenFunctions::GetError(lexer.getErrorCode()) << " at " << lexer.getErrorPosition() << endl;
				str.insert(lexer.getErrorPosition(), "<");
				cout<< str << endl;
			}

		}
		
		return true;
	}
}
