#include <Tests.h>
#include "ManagerTester.h"

int main()
{
	ManagerTester tester;
    tester.run();

	Manager::terminate();
}
