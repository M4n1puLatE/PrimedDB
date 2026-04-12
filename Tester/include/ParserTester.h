#pragma once
#include "Tester.h"

namespace Tester
{
	class ParserTester:public Tester<ParserTester>
	{
		void init();
        bool CompilerTest();
	};
}
