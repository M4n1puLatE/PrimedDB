#pragma once
#include <Timer.h>

namespace Util
{
	template<class TimeType>
	class TimerPlus: Timer<TimeType>
	{ 
        TimeType m_pauseBegin = TimeType(0);
	public:
		TimerPlus() = default;
		TimerPlus(const TimerPlus& copy)
			:Timer<TimeType>(copy), m_pauseBegin(copy.m_pauseBegin)
		{}
		TimerPlus(TimerPlus&& move) noexcept
			:Timer<TimeType>(move), m_pauseBegin(move.m_pauseBegin)
		{}
		void pause()
		{
			m_pauseBegin = Timer<TimeType>::Now();
		}
		bool isPaused() const
		{
			return m_pauseBegin == TimeType(0);
		}
        void resume()
        {
			if (isPaused())
			{
				this->m_begin += Timer<TimeType>::Now() - m_pauseBegin;
				m_pauseBegin = TimeType(0);
			}
        }
		TimerPlus& operator=(const TimerPlus& copy)
		{
			Timer<TimeType>::operator=(copy);
			m_pauseBegin = copy.m_pauseBegin;
			return *this;
		}
        TimerPlus& operator=(TimerPlus&& move) noexcept
        {
			Timer<TimeType>::operator=(move);
			m_pauseBegin = move.m_pauseBegin;
			return *this;
        }
	};
}
