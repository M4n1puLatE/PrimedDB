# Log
>是PrimedDB基于流的日志输出类型，会将待打印和待文件写入操作提交给[LogManager](CN/doc/LogLib/LogManager.md)执行。


# 类型原理
- 使用队列管理传入的消息。
- 在流截止时将队列字符串统一写入`stringstream`。
- 不使用`stringstream`保存数据的原因是节省字符串拷贝开销。

# 使用方法
- `Log`类使用流方法管理多个提交的日志消息，使用`add()/<<`相关方法添加新消息到流中。
- 使用`toFile()`将日志输出文件中
- 流将不会输出`Log`信息直到调用`end()`（`.`调用）或者`endl`（`<<`调用）
- 使用`type()/[]`设置`Log`类型，后续会添加日志过滤或指定类型触发指定功能。


# 类声明与接口
```cpp
class Log
{
	using string = std::string;


	std::deque<string> m_messageArray;
	LogType m_logType = LogType::None;
	string m_fileName;


	std::string getMessage()const;

	void writeTask(string&& message) const;
	static void printMessage(const string& message);
public:
	static string GetLogTypeName(LogType logType);
	bool isTerminated() const;
	bool isWriteToFile() const;
	Log& type(LogType logType);
	const std::string& getFileName() const;
	std::string getLabel() const;
	Log& toFile(string&& fileName);
	friend void endl(Log&);
	void end();
	void clear();
	bool isEmpty()const;
	Log& trigger(const string& error);
	Log& add(std::string& text);
	Log& add(std::string&& text);
	Log& addNumber(size_t number);
	Log& addDouble(double number);
	
	template<FormatType T>
	Log& addObject(const T& instance);
	
	Log& operator[](LogType logType);
	Log& operator()(string&& fileName);
	Log& operator<<(string& text);
	Log& operator<<(string&& text);
    Log& operator<<(size_t number);
    Log& operator<<(double number);
    
	template<FormatType T>
	Log& operator<<(const T& instance);

	void operator<<(void (*func)(Log&)); 
	static void endl(Log& obj);
};

static Log log;
```

## 成员变量与类型别名
### 类型别名
- **string**: `std::string`
	- 简化`std::string`

### 成员变量
 - **m_messageArray**: `std::deque<string>`
	 - 消息队列，保存所有提交的日志信息
 - **m_logType**: `LogType`
	 - 日志消息类型
 - **m_fileName**: `string`
	 - 导出日志消息的文件名称


## 接口
### 私有接口
#### 静态
1. **printMessage(const string& message)**
	- 使用`LogManager`打印日志消息以防止多线程同时打印导致日志乱序

#### 普通
1. **getMessage()const**: `std::string `
	- 从队列中拼接并返回完整的消息

2. **writeTask(string&& message) const**
	- 将日志消息提交给`LogManager`写入指定的日志文件。


### 公用接口
#### 静态接口
1. **GetLogTypeName(`LogType` logType)**: `string`
	- 返回日志类型枚举类型名称的字符串形式。
2. `friend` **endl(`Log&`)**;
	- 用于结束`<<`的流式输出
	- =`end()`
#### 普通
1. **getLabel() const**: `std::string `
	- = **GetLogTypeName(`LogType` logType)**
2. **getFileName() const**: `const std::string&`
	- 获取用户设置的输出日志信息的文件名称。
3. **isTerminated() const**: `bool` 
	- 检查当前日志是否已经被打印。
4. **isWriteToFile() const**: `bool`
	- 检测当前日志是否被定向输出到文件中。
5. **type(`LogType` logType)**: `Log&`
	- 用户用来设定`LogType`类型
6. **toFile(`string&&` fileName)**: `Log&`
	- 将当前定向输出到给定文件。
	- 文件名称会默认携带`.log` 后缀
7. **end()**
	 - 结束当前流，输出现有信息并清理已分配资源
	 - 如果定向到文件就输出到文件
8. **clear()**
	- 清理`Log`分配的资源
9. **isEmpty()const**`bool`
	- 检测这个流是否已经开始或已经被结束
	- 如果未开始或者已经结束就会返回`true`
10. **trigger(`const string&` error)**: `Log&`
	- 与`ErrorManager`协作
		- 调用*error*指向的错误处理函数
		- 唤醒正在等待*error*的函数/线程
11. **add(`std::string&` text)**: `Log&`
	- 添加一个消息到当前`Log`信息流中
12. **add(`std::string&&` text)**: `Log&`
	- 添加一个消息到当前`Log`信息流中
13. **addNumber(size_t number)**: `Log&`
	- 添加一个整数到当前`Log`信息流中
14. **addDouble(`double` number)**: `Log&`
	- 添加一个小数到当前`Log`信息流中
15. `template<FormatType T>`**addObject(`const T&` instance)**: `Log&` 
	- 添加一个拥有`<<(ostream&)`方法的对象到当前`Log`信息流中
16. **operator\[](`LogType` logType)**: `Log&`
	 - =`type()`
17. **operator()(`string&&` fileName)**: `Log&`
	 - =`toFile()`
18. **operator<<(`string&` text)**: `Log&` 
	 - =`add()`
19. **operator<<(`string&&` text)**: `Log&`
	- =`add()`
20. **operator<<(`size_t` number)**: `Log&`
	- =`addNumber()`
21. **operator<<(double number)**: `Log&`
	 - =`addDouble()`
22. `template<FormatType T>`**operator<<(const T& instance)**: `Log&`
	- =`addObject()`
23. **operator<<(`void` (func)(`Log&`))**
	- 用以接受`endl()`，以结束`Log`流的方法
