#include <future>
#include <thread>
#include <condition_variable>
#include <functional>
#include <atomic>
#include <shared_mutex>

namespace Util
{
	using shared_mutex = std::shared_mutex;
	using mutex = std::mutex;
	using read_lock = std::shared_lock<shared_mutex>;
	using write_lock = std::unique_lock<shared_mutex>;
	using unique_lock = std::unique_lock<std::mutex>;
	class Manager
	{
		std::thread m_service;
		mutex m_conditionMutex;
		unique_lock m_conditionLock;
		std::condition_variable m_threadNotifier;
		std::atomic_bool m_terminate;	
	protected:
		void service(const std::function<void()>& customService, const std::function<bool()>& condition);
		void notify();
	public:
		Manager();
		bool isTerminate();
		~Manager();
	};
}
