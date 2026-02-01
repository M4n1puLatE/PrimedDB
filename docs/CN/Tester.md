# Tester/class Tester
>Tester 是PrimedDB中用于**执行单元测试的基类**。

- Tester被配置在另外的`Tester`项目中，由`Tester.exe`运行。所以与其他类没有耦合关系，也不影响PrimedDB本身的任何功能(由`PrimedDB.exe`运行)。
- **Tester 不是线程安全的！**


---
# 使用方法
- 子类**通过CRTP方式使用子类中`init()`函数构造父类**。且子类中必须使用`THIS_IS_A_TEST(子类名称)`这个宏声明子类为一个Test类。
- 在**子类中只需要实现`init()`函数**和实际的**测试函数**即可。
- 在`init()`中，**子类**需要**将所有的测试函数**通过`protected`接口`add`**添加到父类的测试函数列表**中。在添加时需要指定测试名称，以及使用宏`TEST_FUNCTION(函数名称)`包裹测试函数。
- 此外，init中还可以**自定义选择是否使用计时器**来计量测试操作的性能。有两种计时器可以选择
	- timer：**普通计时器**，按照毫秒输出执行时间，使用`enableTimer()`启用，默认关闭
	- precise：**高精度计时器**，按照纳秒输出执行时间，使用`enablePrecise()`启用，默认关闭


## 使用样例
```cpp
void UtilTester::init()
{
	//测试名称，被TEST_FUNCTION包裹的测试函数本身
	add("testIndexSplitString",TEST_FUNCTION(testIndexSplitString));
    add("testSplitString",TEST_FUNCTION(testSplitString));
    add("testInterpretString",TEST_FUNCTION(testInterpretString));
    enableTimer();
}
```

---
# 类声明与接口
```cpp
namespace Tester
{
#define TEST_FUNCTION(function) [this](){return function();}
#define THIS_IS_A_TEST(Self) friend class Tester<Self>
	using std::cout;
	using std::endl;
	//用于进行单元测试
	//非线程安全类
	template <class DerivedTest>

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
		
		
		template <std::derived_from<Tester> T>
		static const char* className(T* instance);
		
		void enableTimer();
		
		void enablePrecise();
		
		void disableTimer();
		
		void disablePrecise();
		
		void add(const string& name, test_function test);
		
		Tester()
			:m_usePrecise(false), m_useTimer(false)
		{
			static_cast<DerivedTest*>(this)->init();
		}
	private:
		std::queue <test_pair> m_tests;
		Util::Timer<Util::milliseconds> m_timer;
		Util::Timer<Util::nanoseconds> m_preciseTimer;
		bool m_useTimer,m_usePrecise;
	public:
		size_t size()const;
		
		bool isTimerEnable() const;
		bool isPreciseEnable() const;
		void run();
		
	};
}

```

## 类型别名
- **test_function**: 表示一个可调用对象（测试运行函数）。
	- 实际类型为`std::function<bool()>`
- **test_pair**: 表示一个测试，由测试名称和测试运行函数组成。
	- 实际类型为`std::pair<string, test_function>`
- **string**: 简化`std::string`

---
## 成员变量
- **m_tests**: `std::queue <test_pair>`
	- 测试列表，包含所有子类添加的测试
- [Timer类型说明](Timer.md)
- **m_timer**: `Timer<Util::milliseconds>`
	- 普通计时器，输出毫秒时间。
- **m_preciseTimer**: `Timer<Util::nanoseconds>`
	- 高精度计时器，输出纳秒时间。
- **m_useTimer**: `bool`
	- 启用普通计时器，默认为`false`
- **m_usePrecise**: `bool`
	- 启用高精度计时器，默认为`false`

---
## 对外接口
 - **size() const**: `size_t`
	 - 返回**未执行**的测试的数量

- **isTimerEnable() const**: `bool`
	- 返回普通计时器是否开启
- **isPreciseEnable() const**: `bool`
	- 返回高精度计时器是否开启
- **run()**
	- 执行所有的测试

---
## 类内接口
- **printVector(const std::vector\<T>& vec)**: `static`, `void`, `template<Printable T>`
	- 用于打印vector中的数据，当容器中是可打印的类型（重载了`ostream::operator<<`）的类型。
![printVector的输出](pic/Pasted%20image%2020260201194936.png)
- **collectionEqual(const T& c1,const T& c2)**: `static`, `bool`, `template <std::ranges::range T>`
	- 用于比较两个容器中的内容是否相等。限制类型必须存在`begin(),end()`
	- 且两个容器必须可以使用`algorithm.h`中的`equal`进行比较
- **className(T\* instance)**: `static`, `const char*`, `template <std::derived_from<Tester> T>`
	- 用以获取子类的函数名称
	- 在运行测试时会通过这个函数获取并打印出当前测试所属的类名称
- **enableTimer()**
	- 启用普通计时器
	- 如果此时高精度计时器已经被启动，将会被关闭。
- **enablePrecise()**
	- 启动高精度计时器
	- 如果此时普通计时器已经被启动，将会被关闭。
- **disableTimer()**
	- 关闭普通计时器
- **disablePrecise()**
	- 关闭高精度计时器
- **add(const string& name, test_function test)**
	- 添加新的测试到测试队列中。
	- 需要给定**名称**和**可调用对象**