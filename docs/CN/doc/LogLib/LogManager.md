# LogManager (Singleton)
>用于处理不同的`Log`流提交的打印以及异步地输出到文件的操作

# 基类
`Manager`, `Singleton`

# 类型原理
使用`Manager`类型提供的管理线程异步地处理`Log`提交的打印请求。

# 类声明与接口
```cpp
class LogManager final:public Util::Singleton<LogManager>,public Util::Manager
{ 
	THIS_IS_SINGLETON;
	std::queue<std::pair<std::string, std::string>> m_writeQueue;
	std::shared_mutex m_queueMutex;
	LogManager();
	void task();
	bool condition() const; 

public:
	void print(const std::string& message);
	void write(std::string&& fileDir, std::string&& message);
	void write(const std::string& fileDir, std::string&& message);
	size_t size();
	bool isEmpty();


	~LogManager()=default;
};
```

## 成员变量和类型别名
1. **m_writeQueue**: `std::queue<std::pair<std::string, std::string>>`
	- 所有待执行的打印和写入操作
2. **m_queueMutex**: `std::shared_mutex`
	- 待打印和写入队列的读写锁

## 接口
### 私有接口
1. **LogManager()**
	- 初始化`LogManager`
	- 将`task()`注册为基类的服务
	- 将`condition()`注册为服务的触发条件
2. **task()**
	- 从待打印列表中取出信息并打印
	- 同时按照设置写入文本
3. **condition() const**: bool 
	- 用以重设基类的`m_condition`，以防止虚假唤醒
### 公用接口
1. **print(`const std::string&` message)**
	 - 触发异步打印。
2. **write(`std::string&&` fileDir, `std::string&&` message)**
	- 将指定消息写入给定文件中
3. **write(`const std::string&` fileDir, `std::string&&` message)**
	- 将指定消息写入给定文件中
4. **size()**: `size_t` 
	- 获取当前未执行任务数量
5. **isEmpty()**: `bool`
	- 获取当前未执行任务数是否为0