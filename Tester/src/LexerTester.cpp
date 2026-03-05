#include "LexerTester.h"

#include "Lexer.h"
namespace Tester
{
	void LexerTester::init()
	{
		add("CompilerTest", TEST_FUNCTION(LexerTester::CompilerTest));
		enableTimer();
	}
	bool LexerTester::CompilerTest()
	{
		Compiler::Lexer lexer("select * hello from here id=2+23+12");
		if (!lexer.isError())
		{
			printVector(lexer.getRawTokens());
			auto& tokens = lexer.getTokens();
			cout << '[';
			for (auto& t : tokens)
			{
				cout << Compiler::TokenFunctions::GetTokenType(t.first)<<",";
			}
			cout<<']'<<endl;
		}

		else
			return false;
		return true;
	}
}
