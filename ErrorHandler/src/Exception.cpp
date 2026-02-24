//#include "Exception.h"
//
//#include "Log.h"
//
//namespace ErrorHandler
//{
//	Exception::Exception(std::string& message,std::string_view funcSig, std::string_view fileDirectory, long long lineNumber)
//	Exception::Exception(std::string&& message, std::string_view funcSig, std::string_view fileDirectory, long long lineNumber)
//		:m_message(std::move(message)), m_classInfo(funcSig, fileDirectory, lineNumber)
//	{}
//	const char* Exception::what() const
//	{
//		return m_message.c_str();
//	}
//	Log::ClassInfo& Exception::where()
//	{
//		return m_classInfo;
//	}
//	void Exception::generateLog()
//	{
//		Log::log[Log::LogType::Error]<<"Exception: "<<m_message<<m_classInfo.complete();
//	}
//}
