#pragma once
#include <exception>
#include <string>
#include <Log.h>
#include "ClassInfo.h"

namespace ErrorHandler
{
	template<const std::string& name>
	class Exception : public std::exception
	{
		std::string m_message;
		Log::ClassInfo m_classInfo;
	public:
		Exception(std::string& message,std::string_view funcSig, std::string_view fileDirectory = "", long long lineNumber = 0)
			:m_message(message), m_classInfo(funcSig, fileDirectory, lineNumber)
		{}
		Exception(std::string&& message, std::string_view funcSig, std::string_view fileDirectory = "", long long lineNumber = 0)
		:m_message(std::move(message)), m_classInfo(funcSig, fileDirectory, lineNumber)
		{}
		const char* what() const override
		{
			return m_message.c_str();
		}
		Log::ClassInfo& where()
		{
			return m_classInfo;
		}
		void generateLog()
		{
			Log::log[Log::LogType::Error] << std::format("Exception<{}>: ",name) << m_message << m_classInfo.complete();
		}
	};
}
