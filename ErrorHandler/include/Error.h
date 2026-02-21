#pragma once
#include <future>

#include "ClassInfo.h"

namespace ErrorHandler
{
	class Error
	{
		Log::ClassInfo m_classInfo;
		long long m_id;
		std::atomic_bool m_handled;
		char m_publisher[20];
		std::string m_message;

	private:
		void notify();
	public:
		Error(std::string_view publisher, std::string&& functionSig, const std::string& fileSig = "", long long lineNumber = 0);
		Error(std::string_view publisher,Log::ClassInfo&& move,std::string&& message = "");
		Error(std::string_view publisher, std::string&& message = "");
		Error();
		Error(Error&&) noexcept;
		Error(const Error&);
		Error& operator=(Error&& move) noexcept;
		Error& operator=(const Error&) = delete;
		std::string_view getPublisher();
		bool isHandled();
		long long getId();
		Log::ClassInfo& getClassInfo();
		const std::string& getMessage();
		void setClassInfo(Log::ClassInfo&& move);
		void setClassInfo(std::string&& functionSig, const std::string& fileSig = "", long long lineNumber = 0);
		void setMessage(std::string&& move);
		void handle(bool solved);
		~Error();
	};
}
