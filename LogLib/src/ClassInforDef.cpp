#include <ClassInfor.h>
#include <format>
#include <sstream>
ACTIVE_STD;
namespace Log
{
    string_view ClassInfo::GetClassName(string_view functionSig)
    {
        auto end = functionSig.find_last_of("::");
        //证明当前函数是类成员函数或者在命名空间中
        if (end != string::npos)
        {
            auto substr = functionSig.substr(0, end);
            auto begin = substr.find_last_of(' ');
            return substr.substr(begin + 1);
        }
        return "";
    }
    string_view ClassInfo::GetFunctionName(string_view functionSig)
    {
        auto begin = functionSig.find_last_of("::");
        if (begin != string::npos)
        {
            auto substr = functionSig.substr(begin + 1);
            auto end = substr.find_first_of('(');
            return substr.substr(0, end);
        }
        return "";
    }
    string_view ClassInfo::GetParameterList(string_view functionSig)
    {
        auto begin = functionSig.find_first_of('(');
        auto end = functionSig.find_last_of(')');
        if (begin != string::npos && end != string::npos)
        {
            return functionSig.substr(begin + 1, end - begin - 1);
        }
        return "";
    }
    string_view ClassInfo::GetReturnType(string_view functionSig)
    {
        auto end = functionSig.find_first_of(' ');
        return functionSig.substr(0, end);
    }
    ClassInfo::ClassInfo(string_view functionSig)
        : ClassInfo(functionSig, "", 0)
    {
        
    }
    ClassInfo::ClassInfo(string_view functionSig, size_t lineNumber)
        : ClassInfo(functionSig, "", lineNumber)
    {
        
    }
    ClassInfo::ClassInfo(string_view functionSig, string_view sourceFileDirectory, size_t lineNumber)
        : ClassName(GetClassName(functionSig)),
          FileDirectory(sourceFileDirectory),
          FunctionName(GetFunctionName(functionSig)),
          LineNumber(lineNumber),
          ParameterList(GetParameterList(functionSig)),
          ReturnType(GetReturnType(functionSig))
    {
        
    }
    string ClassInfo::classInfo()const
    {
        stringstream ss;
        ss << ReturnType << " " << ClassName << "::" << FunctionName << "(" << ParameterList << ")";
        return ss.str();
    }
    //只返回关键信息，包括函数返回值类型，函数名称
    string ClassInfo::functionInfo()const
    {
        stringstream ss;
        ss << ReturnType << " " << FunctionName << "(" << ParameterList << ")";
        return ss.str();
    }
    //返回全部信息，包括函数返回值类型，类名称，函数名称，参数列表
    string ClassInfo::complete()const
    {
        stringstream ss;
        ss << ReturnType << " " 
        << ClassName << "::" 
        << FunctionName << "(" 
        << ParameterList << ")"
        << " in "<<FileDirectory
        << " at line " << LineNumber;
        return ss.str();
    }
}