#include <functional>
#include <queue>
#include <string>
#include <vector>
#include <Timer.h>
namespace Tester
{
	//用于进行单元测试
	//非线程安全类
	class Tester
	{
		using string = std::string;
		using test_function = std::function<bool()>;
		using test_pair = std::pair<string, test_function>;
		const string& m_name;
		std::queue <test_pair> m_tests;
		Util::Timer<Util::milliseconds> m_timer;
		bool m_useTimer;
	public:
        Tester(const string& name);
		Tester(const string& name,bool useTimer);
		void add(const string& name,test_function test);
		size_t size()const;
		void run();
	};
}
