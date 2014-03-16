#include <iostream>
using namespace std;
#include <Windows.h>

#include <vld.h>
#include "../BackBone/BackBone.h"
using namespace BackBone;

int main()
{
	if (SetDllDirectory("..\\DLL") == FALSE)
	{
		return -1;
	}

	if (!API::Init(NULL, 1024, 768, false))
	{
		return 1;
	}


	API::Flush();

	return 0;
}