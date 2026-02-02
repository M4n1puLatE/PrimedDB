#include <Log.h>
#include <fstream>
namespace Log
{
	const char* Log::GetLogTypeName(LogType logType)
	{
		if (logType == LogType::Debug)
            return "[Debug]";
        if (logType == LogType::Error)
            return "[Error]";
        if (logType == LogType::Fatal)
            return "[Fatal]";
        if (logType == LogType::Info)
            return "[Info]";
        if (logType == LogType::Warn)
            return "[Warn]";


		return "";
	}
	bool Log::isTerminated()
	{
		return m_messageStream.peek() == std::stringstream::traits_type::eof();
	}
	bool Log::isUseTimeStamp() const
	{
		return m_useTimeStamp;
	}

	Log& Log::ToFile(string& fileName)
	{
		m_fileName = std::move(fileName);
        return *this;
	}
	Log& Log::useTimeStamp()
	{
		m_useTimeStamp = true;
		return *this;
	}
	bool Log::isWriteToFile() const
	{
		return !m_fileName.empty();
	}
	void Log::clear()
	{
		m_messageStream.str("");
		m_messageStream.clear();
		m_fileName.clear();
        m_logType = LogType::None;
		m_useTimeStamp = false;
	}
	bool Log::empty()
	{
		return m_messageStream.peek() == m_messageStream.eof();
	}
	Log& Log::add(const std::string& text)
	{
		if (!empty())
			m_messageStream << ' ';
		m_messageStream << text;
		return *this;
	}
	Log& Log::addNumber(size_t number)
	{
		return add(std::to_string(number));
	}
	Log& Log::addDouble(double number)
	{
		return add(std::to_string(number));
	}
	Log& Log::operator<<(const string& text)
	{
		return add(text);
	}
	Log& Log::operator<<(size_t number)
	{
		return addNumber(number);
	}
	Log& Log::operator<<(double number)
	{
		return addDouble(number);
	}
	void Log::operator<<(void(*func)(Log*))
	{
		func(this);
	}
	void Log::end()
	{
		std::string print = m_messageStream.str();
		print = getLabel() + print;
		bool isError = m_logType >= LogType::Error;
		if (isUseTimeStamp()|| isError)
		{
			Util::TimeStamp time = Util::TimeStamp::Now();
			print = time.getString() + " - " + print;
		}

		if (isWriteToFile())
		{
			std::ofstream file(m_fileName);
			file << print << std::endl;
		}
		else if (isError)
		{
			std::ofstream file("Error.log");
			file << print << std::endl;
		}
		clear();
	}
	Log& Log::trigger(const string& error)
	{
		//Trigger error manager with a specific error.
		return *this;
	}
	void endl(Log& obj)
	{
		obj.end();
	}
}
