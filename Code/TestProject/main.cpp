#include <iostream>
using namespace std;
#include <Windows.h>

#include <vld.h>
#include "../BackBone/Test.h"

int main()
{
	if (SetDllDirectory("..\\DLL") == FALSE)
	{
		return -1;
	}

	cout << BackBone::a << endl;
	BackBone::Hej();

	return 0;
}