# Timer(Generic class)
>PrimedDB中的计时器类型，用于计时。模版参数传入`std::chrono`中的时间类型。
>
>Timer是一次性的，在结束后需要立即取回计时器结果，在结束时会清理计时器并丢失原先的结果。这种设计是为了保持计时器类最简，因为它可能会被用在性能测试等重要场景下。

所属命名空间：`Util`

其中部分`chrono`时间类型在命名空间中可以直接使用，如：
```cpp
using seconds = std::chrono::seconds;
using minutes = std::chrono::minutes;
using hours = std::chrono::hours;
using milliseconds = std::chrono::milliseconds;
using nanoseconds = std::chrono::nanoseconds;
```
# 使用方法
- 通过接口`start()`或非默认构造函数启动计时器。
- 使用`end()`结束当前计时器，并返回从`start()`调用到`end()`之间的时间间隔（单位取决于模板参数）。
- 使用`get`获取当前时间，在`end()`调用后再次调用会返回世界系统起始时间（也就是chrono时间类型的0）。
# 类声明与接口
```cpp
template<class TimeType>
class Timer
{
	TimeType m_begin;
public:
	Timer();
	Timer(TimeType begin);
	Timer(const Timer& copy);
	Timer(Timer&& move);
	
	bool isStarted() const;
	void start();
	void reset();
	TimeType end();
	bool isEmpty()const;
	TimeType get();
	static TimeType Now();
	Timer& operator=(const Timer& copy);
	Timer& operator=(Timer&& move);
};
```
## 模板参数说明
`TimeType`为用户传入的时间类型，被限制为仅限`std::chrono`中的时间类型。

---
## 成员变量
1. **m_begin**: `TimeType`
	- 计时器开始时间

---
## 构造函数
1. 默认构造函数
	- 默认关闭计时器，需要使用`start()`启动计时器。
	- 使用`isEmpty()`时返回*true*。
2. **Timer(TimeType begin)**
	- 自动使用传入的时间启动计时器。
	- 可以使用`static`函数`Now()`获取当前时间。
3. 拷贝构造函数
	- 将从给定对象拷贝计时器开始时间。
4. 移动构造函数
	 - 将从给定对象移动计时器开始时间。

---
## 接口
1. **isStarted() const**: `bool`
	- 返回当前`Timer`对象是否被启动。
2. **start()**
	- 启动当前`Timer`。
3. **reset()**
	- 重置当前`Timer`到未启动计时状态。
4. **end()**: `TimeType`
	- 终止当前计时器并返回时间间隔。
5. **isEmpty()const**: `bool`
	- 检测当前计时器是否为空(=isStarted())
6. **get()**: `TimeType
	- 获取开始时间。
7. **Now()**: `static`, `TimeType`
	- 静态函数，用于获取当前系统时间。
	- 可以在使用有参数的构造函数构造对象时使用。

