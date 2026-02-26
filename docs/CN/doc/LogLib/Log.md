# Log
>是PrimedDB基于流的日志输出类型，会将待打印和待文件写入操作提交给[LogManager](CN/doc/LogLib/LogManager.md)执行。


# 类型原理
- 使用队列管理传入的消息。
- 在流截止时将队列字符串统一写入stringstream。
- 不使用stringstream保存数据的原因是节省字符串拷贝开销。

# 使用方法

# 类声明与接口
```cpp
class Log
{
	using string = std::string;


	std::deque<string> m_messageArray;
	LogType m_logType = LogType::None;
	string m_fileName;

	const std::string& getFileName() const;
	std::string getMessage()const;
	std::string getLabel() const;
	void writeTask(string&& message) const;
	static void printMessage(const string& message);
public:
	static string GetLogTypeName(LogType logType);
	bool isTerminated() const;
	bool isWriteToFile() const;
	Log& type(LogType logType);

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

## 接口