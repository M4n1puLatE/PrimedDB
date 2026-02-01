#pragma once
#include <Timer.h>

namespace Util
{
	template<class TimeType>
	class TimerPlus: Timer<TimeType>
	{ 
		bool m_paused = false;
        TimeType m_pauseBegin;
	public:
		void pause()
		{
			if (!m_paused)
			{
				m_paused = true;
				m_pauseBegin = Timer<TimeType>::now();
			}
		}
		bool isPaused() const
		{
			return m_paused;
		}
        void resume()
        {
            if (m_paused)
            {
                m_paused = false;
                this->m_begin += Timer<TimeType>::now() - m_pauseBegin;
            }
        }
	};
}
