// PrimedDB.cpp: 定义应用程序的入口点。
//

#include "PrimedDB.h"
#include <Log.h>
#include <Util.h>
#include <Timer.h>
#include <iostream>

using namespace std;
int main()
{
	
	string test = "hello,1,2,3,4,5,6,7,1,2,3,4,5,6,7,8,8,8,9,90,0,0,-";
	Util::Timer<Util::nanoseconds> timer;
	auto result = Util::Util::IndexSplitString(test, ',');
	std::cout << "time: " << timer.end()<<"\n";

	for (int n = 0;n<result.size()+1;++n)
	{
		std::cout << Util::Util::InterpretString(test, result,n);
	}


	timer.start();
	auto result2 = Util::Util::SplitString(test, ',');
	std::cout << "time: " << timer.end() << "\n";
	for (auto& str : result2)
	{
		std::cout << str;
	}
	
}
