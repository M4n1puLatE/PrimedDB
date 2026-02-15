# Manager
>是实现PrimedDB中管理者类型的基类。其提供一个独立线程，当用户注册的`condition`成立且线程被`notify`时执行子类注册的`service`。

所属命名空间： `Util`

# 使用方法

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