#pragma once
#include <chrono>
namespace Util {
	using seconds = std::chrono::seconds;
	using minutes = std::chrono::minutes;
	using hours = std::chrono::hours;
	using milliseconds = std::chrono::milliseconds;
	using nanoseconds = std::chrono::nanoseconds;
	template<class TimeType>
	class Timer
	{
		TimeType m_begin;
		static auto now()
		{
			return std::chrono::duration_cast<TimeType>(std::chrono::system_clock::now().time_since_epoch());
		}
	public:
		Timer()
			:m_begin(0)
		{}
		Timer(TimeType begin)
			:m_begin(begin),m_started(true)
		{}
		bool isStarted() const
		{
			return m_begin != 0;
		}
		void start()
		{
			m_begin = now();
		}
		void reset()
		{
			m_begin = 0;
		}
		TimeType end()
		{
			auto interval = now() - m_begin;
			reset();
			return interval;
		}
		bool isEmpty()const
		{
			return m_begin == TimeType(0);
		}
		TimeType get()
		{
			return m_begin;
		}
		static TimeType Get()
		{
			return now();
		}
	};
}