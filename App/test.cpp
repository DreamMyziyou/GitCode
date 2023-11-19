#include <iostream>
#include "Common/CommonModule.h"

using namespace std;

int main(int argc, char** argv)
{
	cout << "Hello, world!" << endl;

    CommonModule::instance().test();

	return 0;
}