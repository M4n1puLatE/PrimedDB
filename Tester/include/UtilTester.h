#pragma once
#include <Tester.h>
#include <Util.h>
namespace Tester
{
	class UtilTester:public Tester
	{
		string test1 = "hello,a,1,2,3";
		string test2 = "hellobab1b2b3";
		string test3 = "....";
		string test4 = "hello.a.1.2.3";
		std::vector<string> token = {"hello","a","1","2","3"};
        std::vector<size_t> index = {5,7,9,11};
		void init() override;
		bool testIndexSplitString() const;
		bool testSplitString() const;
		bool testInterpretString()const;

	public:
		UtilTester();
	};
}