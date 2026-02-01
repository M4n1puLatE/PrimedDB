#pragma once
#include <Tester.h>
#include <ClassInfo.h>
namespace Tester
{
	class ClassInfoTester : public Tester<ClassInfoTester>
	{ 
		THIS_IS_A_TEST(ClassInfoTester);

		std::unique_ptr<Log::ClassInfo> m_ptr = nullptr;
		string m_name = "generateFunction";
		 string m_returnType = "void";
		 string m_parameterList = "(void)";
		 string m_fileName = "ClassInfoTester.cpp";
		 size_t line = 20;

		 string m_className = "Tester::ClassInfoTester";

		string m_raw;


		void generateFunction();

		void init();
		
		bool testRaw()const;
		bool testClassName() const;
        bool testFunctionName() const;
        bool testParameterList() const;
        bool testReturnType() const;
        bool testFileDirectory() const;
        bool testLineNumber() const;
        bool testClassInfo() const;
        bool testFunctionInfo() const;
		bool testComplete() const;
	public:
		ClassInfoTester();
	};
}