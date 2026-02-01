#include <UtilTester.h>

namespace Tester
{
	void UtilTester::init()
	{
		add("testIndexSplitString",TEST_FUNCTION(testIndexSplitString));
        add("testSplitString",TEST_FUNCTION(testSplitString));
        add("testInterpretString",TEST_FUNCTION(testInterpretString));
		enableTimer();
	}
	bool UtilTester::testIndexSplitString()const
	{
		auto result1 = Util::Util::IndexSplitString(test1, ',');
		auto result2 = Util::Util::IndexSplitString(test2, 'b');
		auto result3 = Util::Util::IndexSplitString(test3, '.');
		auto result4 = Util::Util::IndexSplitString(test4, '.');
		//printVector(result1);
		if (!collectionEqual(result1, index))
			return false;
		//printVector(result2);
		if (!collectionEqual(result2, index))
			return false;
		//printVector(result3);
		//printVector(result4);
		if (!collectionEqual(result4, index))
			return false;
		return true;
	}
	bool UtilTester::testSplitString()const
	{
		auto result1 = Util::Util::SplitString(test1, ',');
		auto result2 = Util::Util::SplitString(test2, 'b');
		auto result3 = Util::Util::SplitString(test3, '.');
		auto result4 = Util::Util::SplitString(test4, '.');
		printVector(result1);
		if (!collectionEqual(token,result1))
			return false;
		/*printVector(result2);*/
		if (!collectionEqual(token, result2))
			return false;
		//printVector(result3);
		//printVector(result4);
		if (!collectionEqual(token, result4))
			return false;
		return true;
	}
	void recursiveInterpret(const std::string& str, const std::vector<size_t>& indexes)
	{
		for (int n = 0;n<indexes.size();++n)
		{
			std::cout << Util::Util::InterpretString(str, indexes, n);
			if (n+1 < indexes.size())
                std::cout << "|";
		}
		std::cout << std::endl;
	}
	bool UtilTester::testInterpretString()const
	{
		auto result1 = Util::Util::IndexSplitString(test1, ',');
		auto result2 = Util::Util::IndexSplitString(test2, 'b');
		auto result3 = Util::Util::IndexSplitString(test3, '.');
		auto result4 = Util::Util::IndexSplitString(test4, '.');
		
		recursiveInterpret(test1, result1);
		recursiveInterpret(test2, result2);
		recursiveInterpret(test3, result3);
		recursiveInterpret(test4, result4);
		return true;
	}
}