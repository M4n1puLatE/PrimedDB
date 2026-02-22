#pragma once
#include <future>

#include "ClassInfo.h"

namespace ErrorHandler
{
	class Error
	{
		long long m_id;
		long long m_typeId;
		std::atomic_bool m_handled;
		std::string m_message;
		
	public:
		Error();
		Error(std::string&& message);
		Error(std::string& message);
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
