#pragma once
#include <exception>
#include <string>

#include "ClassInfo.h"

namespace ErrorHandler
{
	class Exception:public std::exception
	{
		std::string m_message;
		Log::ClassInfo m_classInfo;
	public:
		Exception(std::string_view funcSig, std::string_view fileDirectory = "", long long lineNumber = 0);
		const char* what() const override;
		Log::ClassInfo& where();
		void generateLog();
	};
}
