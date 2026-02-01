# Tester
Tester 是PrimedDB中用于**执行单元测试的基类**。子测试只需要继承Tester类就可以自动化执行测试。Tester由`Tester.exe`运行，所以与其他类没有耦合关系，也不影响PrimedDB本身的任何功能(由`PrimedDB.exe`运行)。
- **Tester 不是线程安全的！**

# [类声明与接口](../../Tester/include/Tester.h)
```cpp
	class Tester
	{
	protected:
		using string = std::string;
		using test_function = std::function<bool()>;
		using test_pair = std::pair<string, test_function>;
		template<class T>
		static void printVector(const std::vector<T>& vec);
		template <std::ranges::range T>
		static bool collectionEqual(const T& c1,const T& c2);
		void enableTimer();
		void disableTimer();
		void add(const string& name, test_function test);
		Tester(const string& name);
		Tester(const string& name, bool useTimer);
	private:
		const string& m_name;
		std::queue <test_pair> m_tests;
		Util::Timer<Util::milliseconds> m_timer;
		bool m_useTimer;
	public:
		size_t size()const;
		bool isTimerEnable() const;
		void run();
	};
```
