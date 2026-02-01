#ifndef L_CLASSINFOR_H
#define L_CLASSINFOR_H
#include<string>
#include<filesystem>
#include<fstream>
#include <memory>
#define USE_STD using namespace std
#define THIS_LINE __LINE__
#define THIS_FILE __FILE__
#ifdef _WIN32
#define THIS_FUNC __FUNCSIG__
#else 
#define THISFUNC __PRETTY_FUNCTION__
#endif

namespace Log
{
	class ClassInfo:std::enable_shared_from_this<ClassInfo>
	{
		using string = std::string;
		using string_view = std::string_view;
		static string_view GetClassName(string_view functionSig);
        static string_view GetFunctionName(string_view functionSig);
        static string_view GetParameterList(string_view functionSig);
        static string_view GetReturnType(string_view functionSig);
	public:
		ClassInfo(string_view functionSig);
		ClassInfo(string_view functionSig, size_t lineNumber= 0);
		ClassInfo(string_view functionSig,string_view sourceFileDirectory, size_t lineNumber=0);
		const string_view Raw;
		const string_view ClassName;
		const string_view FileDirectory;
		const string_view FunctionName;
		const size_t LineNumber;
		const string_view ParameterList;
		const string_view ReturnType;
		//返回全部信息，包括函数返回值类型，类名称，函数名称，参数列表
		string classInfo()const;
		//只返回关键信息，包括函数返回值类型，函数名称
		string functionInfo()const;
		//返回全部信息，包括函数返回值类型，类名称，函数名称，参数列表，文件名，行数
		string complete()const;
	};
}

#endif
