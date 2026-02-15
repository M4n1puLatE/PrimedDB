# Manager
>是实现PrimedDB中管理者类型的基类。其提供一个独立线程，当用户注册的`condition`成立且线程被`notify`时执行子类注册的`service`。

所属命名空间： `Util`

# 使用方法
继承`Manager`方法并在子类中实现`service`（`Manager`线程中运行的管理服务）和`condition`（线程启动条件）并传入构造函数进行构造（使用`bind`或`lambda`表达式）


# 类声明与接口
```cpp
class Manager
{
	std::thread m_service;
	mutex m_conditionMutex;
	std::condition_variable m_threadNotifier;
	std::atomic_bool m_terminate;	
protected:
	void service(const std::function<void()>& customService, const std::function<bool()>& condition);
	void notify();
	void terminate();
	void join();
public:
	Manager(const std::function<void()>& customService, const std::function<bool()>& condition);
	bool isTerminate();

	~Manager();
};
```

## 成员变量
1. **m_service**: `thread`
	- 管理员类型的服务线程
2. **m_conditionMutex**: `std::mutex`
	- 服务线程中的条件变量锁。
3. **m_threadNotifier**: `std::condition_variable`
	- 服务线程中的条件变量
4. **m_terminate**: `std::atomic_bool`
	- 服务线程状态（true为结束，false为正在运行或等待）

---
## 构造函数
- **Manager(const std::function<void()>& customService, const std::function<bool()>& condition)**
	- 注册服务和服务线程的唤醒条件。


---
## 私有方法
- **service(const std::function<void()>& customService, const std::function<bool()>& condition)**
---
## 继承类内部接口
- **notify()**
	- 唤醒服务线程（如果条件成立的情况下）
- **terminate()**
	- 结束当前服务线程（在当前服务完成后）
	- 如果当前服务未完成将会阻塞调用线程
- **join()**
	- 等待服务线程结束

---
## 公有接口
- **isTerminate()**: bool
	- 检测服务线程是否结束

---
## 析构行为
- 调用`teminate()`函数结束当前线程。
