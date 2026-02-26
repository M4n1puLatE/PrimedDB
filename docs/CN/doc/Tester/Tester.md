# Tester(Class)
>Tester 是PrimedDB中用于**执行单元测试的基类**。子类（实际测试）通过向基类测试列表注册测试。所有注册的测试在外部调用`run()`接口时统一执行。

所属命名空间：`Tester`

- Tester被配置在另外的`Tester`项目中，由`Tester.exe`运行。所以与其他类没有耦合关系，也不影响PrimedDB本身的任何功能(由`PrimedDB.exe`运行)。
- **Tester 不是线程安全的！** 因为Tester设计的目的是在未发行正式版本前执行单元测试。


---
# 使用方法
- 子类**通过CRTP方式使用子类中`init()`函数构造父类**。且子类中必须使用`THIS_IS_A_TEST(子类名称)`或`A_TEST`宏声明子类为一个Test类。
- 在**子类中只需要实现`init()`函数**和实际的**测试函数**即可。
- 在`init()`中，**子类**需要**将所有的测试函数**通过`protected`接口`add`**添加到父类的测试函数列表**中。在添加时需要指定测试名称，以及使用宏`TEST_FUNCTION(函数名称)`包裹测试函数。
- 此外，init中还可以**自定义选择是否使用计时器**来计量测试操作的性能。有两种计时器可以选择
	- timer：**普通计时器**，按照*毫秒*输出执行时间，使用`enableTimer()`启用，默认关闭
	- precise：**高精度计时器**，按照*纳秒*输出执行时间，使用`enablePrecise()`启用，默认关闭


## 使用样例
```cpp
class NewTester:public Tester<NewTester>
{
A_TEST;
private:
	void UtilTester::init()
	{
		//测试名称，被TEST_FUNCTION包裹的测试函数本身
		add("testIndexSplitString",TEST_FUNCTION(testIndexSplitString));
	    add("testSplitString",TEST_FUNCTION(testSplitString));
	    add("testInterpretString",TEST_FUNCTION(testInterpretString));
	    enableTimer();
	}
}

```

---
# 类声明与接口
```cpp
namespace Tester
{
#define TEST_FUNCTION(function) [this](){return function();}
#define THIS_IS_A_TEST(Self) friend class Tester<Self>
#define A_TEST friend class Tester;
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
		bool m_useTimer, m_usePrecise;
	public:
		size_t size()const;
		
		bool isTimerEnable() const;
		bool isPreciseEnable() const;
		void run();
		
	};
}

```
## 宏
1. **TEST_FUNCTION(function)**: 用于标明一个测试函数，实际上是使用一个lambda表达式调用给定函数使得Tester函数可以正确执行自定义测试函数。
2. **THIS_IS_A_TEST(Self)**: 表明当前类是一个测试类，将基类`Tester`设置为友元类，这样`Tester`就可以访问私有`init()`进行构造。
3. **A_TEST**: 上一个宏根据编译器特性的简化版本。

---

## 类型别名
1. **test_function**: 表示一个可调用对象（测试运行函数）。
	- 实际类型为`std::function<bool()>`
2. **test_pair**: 表示一个测试，由测试名称和测试运行函数组成。
	- 实际类型为`std::pair<string, test_function>`
3. **string**: 简化`std::string`

---
## 成员变量
1. **m_tests**: `std::queue <test_pair>`
	- 测试列表，包含所有子类添加的测试

2. **m_timer**: `Timer<Util::milliseconds>`
	- 普通计时器，输出毫秒时间。
	- [Timer类型说明](Tim- [Timer类型说明](Util/Timer.md)er.md)
3. **m_preciseTimer**: `Timer<Util::nanoseconds>`
	- 高精度计时器，输出纳秒时间。
4. **m_useTimer**: `bool`
	- 启用普通计时器，默认为`false`
5. **m_usePrecise**: `bool`
	- 启用高精度计时器，默认为`false`

---
## 构造函数
1. 默认构造函数
	- 使用CRTP模式调用子类实现的`init()`函数
---
## 接口
### public
 1. **size() const**: `size_t`
	 - 返回**未执行**的测试的数量
2. **isTimerEnable() const**: `bool`
	- 返回普通计时器是否开启
3. **isPreciseEnable() const**: `bool`
	- 返回高精度计时器是否开启
4. **run()**
	- 执行所有的测试

---
### protected
1. `template<Printable T>` **printVector(const std::vector\<T>& vec)**: `static`, `void`
	- 用于打印vector中的数据，当容器中是可打印的类型（重载了`ostream::operator<<`）的类型。
![printVector的输出](../Util/pic/Pasted%20image%2020260201194936.png)
2. `template <std::ranges::range T>` **collectionEqual(const T& c1,const T& c2)**: `static`, `bool`
	- 用于比较两个容器中的内容是否相等。限制类型必须存在`begin(),end()`
	- 且两个容器必须可以使用`algorithm.h`中的`equal`进行比较
3. `template <std::derived_from<Tester> T>` **className(T instance)**: `static`, `const char*`
	- 用以获取子类的函数名称
	- 在运行测试时会通过这个函数获取并打印出当前测试所属的类名称
4. **enableTimer()**
	- 启用普通计时器
	- 如果此时高精度计时器已经被启动，将会被关闭。
5. **enablePrecise()**
	- 启动高精度计时器
	- 如果此时普通计时器已经被启动，将会被关闭。
6. **disableTimer()**
	- 关闭普通计时器
7. **disablePrecise()**
	- 关闭高精度计时器
8. **add(const string& name, test_function test)**
	- 添加新的测试到测试队列中。
	- 需要给定**名称**和**可调用对象**

# 运行输出
![测试结果](../Util/pic/Pasted%20image%2020260212125600.png)
- 白底部分为当前测试类名称。
- 黄色带序号部分为当前测试项目名称（在add时可自定义）。
- 白字部分为测试内部自行输出的内容。
- 绿色部分为测试是否通过，如果失败则会变为红色且后缀变为*is failed*。
- 蓝色部分为当前测试执行耗时，如果没有启用任何Timer则不显示。
- 最后会总结测试通过的数量和测试失败的数量。