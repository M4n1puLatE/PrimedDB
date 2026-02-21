#pragma once
#include <MultiThread.h>
#include <queue>

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
	//	bool isTerminate();

	//	~DepreciatedManager();
	//};
	class Manager
	{
		using service = std::function<void()>;
		using awake_condition = std::function<bool()>;

		static std::thread sm_service;
		static mutex sm_conditionMutex;
		static std::condition_variable sm_threadNotifier;
		static std::atomic_bool sm_terminate;
		static std::atomic_bool sm_conditionFlag;


		static std::vector<service> sm_serviceQueue;
		static std::deque<size_t> sm_executeQueue;
		static shared_mutex sm_queueMutex;

	private:
		static void manageService();


		awake_condition m_condition;
		const size_t m_id;
		static size_t taskSize();
		static size_t serviceSize();
		static void add(service&& service);
		static void newTask(size_t id);
		static bool isEmpty();
		static bool isServiceEmpty();
		static void urgentTask(size_t id);
	protected:
		Manager(std::function<void()>&& customService, std::function<bool()>&& condition);
		void notify() const;
		void submit() const;
		 
	public:
		static bool isTerminate();

		static void join();
		static void terminate();
		static void notifyTerminate();
		~Manager() = default;
	};
}
