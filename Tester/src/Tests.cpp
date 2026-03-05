#include <Tests.h>

#include "LexerTester.h"
#include "Log.h"
#include "LogManager.h"
#include "LogTester.h"

int main()
{
	UtilTester utilTest;
	utilTest.run();
	ClassInfoTester classInfoTest;
    classInfoTest.run();
    TimeStampTester timeStampTest;
    timeStampTest.run();
	//LogTester logTest;
	//logTest.run();
	LexerTester lexerTest;
    lexerTest.run();

	Util::Manager::terminate();
	//Log::log[Log::LogType::Warn].toFile("2月.txt") << "123" << Log::Log::endl;
}
