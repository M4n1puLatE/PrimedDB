#include <ClassInfoTester.h>

namespace Tester
{
	void ClassInfoTester::init()
	{
		add("TestRaw",TEST_FUNCTION(testRaw));
		add("TestClassName", TEST_FUNCTION(testClassName));
        add("TestFunctionName", TEST_FUNCTION(testFunctionName));
        add("TestParameterList", TEST_FUNCTION(testParameterList));
        add("TestReturnType", TEST_FUNCTION(testReturnType));
        add("TestFileDirectory", TEST_FUNCTION(testFileDirectory));
        add("TestLineNumber", TEST_FUNCTION(testLineNumber));
        add("TestFunctionInfo", TEST_FUNCTION(testFunctionInfo));
        add("TestClassInfo", TEST_FUNCTION(testClassInfo));
        add("TestComplete", TEST_FUNCTION(testComplete));
        enableTimer();
	}
	void ClassInfoTester::generateFunction()
	{
        m_ptr = std::make_unique<Log::ClassInfo>(THIS_FUNC, THIS_FILE, THIS_LINE);
        m_raw = THIS_FUNC;
	}
    bool ClassInfoTester::testRaw()const
	{
        if (!m_ptr)
            return false;
        //std::cout << m_ptr->Raw << endl;
		return m_ptr->Raw == m_raw;
	}
    bool ClassInfoTester::testClassName() const
	{
        if (!m_ptr)
            return false;
        //std::cout << m_ptr->ClassName << endl;
		return m_ptr->ClassName == m_className;
	}
    bool ClassInfoTester::testFunctionName() const
	{
        if (!m_ptr)
            return false;
        //std::cout << m_ptr->FunctionName << endl;
        return m_ptr->FunctionName == m_name;
	}
    bool ClassInfoTester::testParameterList() const
	{
        if (!m_ptr)
            return false;
        //std::cout << m_ptr->ParameterList << endl;
        return m_ptr->ParameterList == m_parameterList;
	}
    bool ClassInfoTester::testReturnType() const
	{
        if (!m_ptr)
            return false;
        //std::cout << m_ptr->ReturnType << endl;
        return m_ptr->ReturnType == m_returnType;
	}
    bool ClassInfoTester::testFileDirectory() const
	{
        if (!m_ptr)
            return false;
        //std::cout << m_ptr->FileDirectory << endl;
        return m_ptr->FileDirectory.find(m_fileName)!=string::npos;
	}
    bool ClassInfoTester::testLineNumber() const
	{
        if (!m_ptr)
            return false;
        //std::cout << m_ptr->LineNumber << endl;
		return m_ptr->LineNumber - line <= 5;
	}
    bool ClassInfoTester::testClassInfo() const
	{
        if (!m_ptr)
            return false;

        //cout << m_ptr->classInfo() << endl;
        return true;
	}
    bool ClassInfoTester::testFunctionInfo() const
	{
        if (!m_ptr)
            return false;
        //cout << m_ptr->functionInfo() << endl;
        return true;
	}
    bool ClassInfoTester::testComplete() const
	{
        if (!m_ptr)
            return false;
        //cout << m_ptr->complete() << endl;
        return true;
	}
    ClassInfoTester::ClassInfoTester()
    {
        generateFunction();
    }
}
