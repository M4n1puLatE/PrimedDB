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
	class ClassInfo
	{
		using string = std::string;
		using string_view = std::string_view;
		static string_view GetClassName(string_view functionSig);
        static string_view GetFunctionName(string_view functionSig);
        static string_view GetParameterList(string_view functionSig);
        static string_view GetReturnType(string_view functionSig);
	public:
		ClassInfo();
		ClassInfo(string_view functionSig, size_t lineNumber= 0);
		ClassInfo(string_view functionSig,string_view sourceFileDirectory, size_t lineNumber=0);
		ClassInfo(const ClassInfo&);
		const string Raw;
		const string ClassName;
		const string FileDirectory;
		const string FunctionName;
		const size_t LineNumber;
		const string ParameterList;
		const string ReturnType;
		//返回全部信息，包括函数返回值类型，类名称，函数名称，参数列表
		string classInfo()const;
		//只返回关键信息，包括函数返回值类型，函数名称
		string functionInfo()const;
		//返回全部信息，包括函数返回值类型，类名称，函数名称，参数列表，文件名，行数
		string complete()const;
	};
}

#endif
