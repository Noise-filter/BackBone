#include <iostream>
using namespace std;
#include <Windows.h>

#include <vld.h>
#include "../BackBone/BackBone.h"

int main()
{
	if (SetDllDirectory("..\\DLL") == FALSE)
	{
		return -1;
	}

	
	

	return 0;
}