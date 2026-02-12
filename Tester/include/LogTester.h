#pragma once
#include "Tester.h"

namespace Tester
{
	class LogTester : public Tester<LogTester>
	{ 
		A_TEST;
		void init();
		bool testAdd();
		bool testAddNumber();
		bool testAddDouble();
		bool testAddObject();
		bool testGetLogTypeName();
		bool testEnd();
		
		bool testPrint();
		bool testWrite();
		bool testEmpty();
		bool justPrint();

	public:
		LogTester() = default;
	};
}
