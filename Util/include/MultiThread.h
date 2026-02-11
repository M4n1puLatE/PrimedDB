#pragma once
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
	using unique_lock = std::unique_lock<mutex>;
}
