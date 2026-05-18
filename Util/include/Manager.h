#pragma once
#include <deque>
#include <functional>
#include <MultiThread.h>

namespace Util
{
	//class DepreciatedManager
	//{
	//	std::thread m_service;
	//	mutex m_conditionMutex;
	//	std::condition_variable m_threadNotifier;
	//	std::atomic_bool m_terminate;	
	//	void service(const std::function<void()>& customService, const std::function<bool()>& condition);
	//protected:

	//	void notify();
	//	void terminate();
	//	void join();
	//public:
	//	
	//	DepreciatedManager(const std::function<void()>& customService, const std::function<bool()>& condition);
	//	bool isThreadEmpty();

	//	~DepreciatedManager();
	//};
	using service = std::function<void()>;
	using awake_condition = std::function<bool()>;
	class ManagerService
	{
		//当前的任务的id
		unsigned char m_serviceId;
		//当前任务线程
		std::thread m_serviceThread;
		//线程终止标志
		std::atomic_bool m_termination = false;
		//线程正在执行标志
		std::atomic_bool m_executing= false;
		//线程执行条件
		std::atomic_bool m_condition =false;
        //线程唤醒次数
        std::atomic_uint m_count = 0;

		std::condition_variable m_threadNotifier;
		mutex m_conditionMutex;
		void managerService();
	public:
		ManagerService();
		ManagerService(ManagerService&& move)noexcept;
		void terminate();
		void terminateAndJoin();
		bool isTerminate();
		void setCondition(bool condition);
		bool isConditionHold()const;
		size_t getTaskId() const;
		void join();

		void notify();
		void notifyWithCondition(bool condition);
		ManagerService& operator=(ManagerService&& move)noexcept;
	};
	class Manager
	{
		//线程列表
		
	private:
		//static void manageService();
		//当前子类的唤醒条件
		awake_condition m_condition;
		//当前子类的服务id
		const size_t m_id;
	

		//注册线程池服务（在基类构造函数中调用）
		static void add(service&& service);
		//新增待执行服务
		static void newTask(size_t id);
		//新增紧急待执行服务
		static void urgentTask(size_t id);
        //判断需不需要分配新线程
		static bool allocateNewThread();
        //判断需不需要释放一个线程
		static bool deallocateAThread();
	protected:
		Manager(std::function<void()>&& customService, std::function<bool()>&& condition);
		//随机唤醒一个线程
		void notify() const;
        //注册一个待执行服务
		void submit() const;
        //随机唤醒一个线程，并优先执行注册服务
		void notifyNow() const;
	public:
		static void join();
		static bool isThreadEmpty();
		static void terminate();
		static void notifyTerminate();
		//线程池注册服务数量
		static size_t serviceSize();
		//线程池线程数量
		static size_t threadSize();
		//线程池待执行服务数量
		static size_t taskSize();
		//判断当前待执行服务列表是否为空
		static bool isEmpty();
		//判断当前待注册服务列表是否为空
		static bool isServiceEmpty();
		~Manager() = default;
	};
}
