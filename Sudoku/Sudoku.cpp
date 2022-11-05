// De Cooman Jarno - 2022
#include "pch.h"
#include "SaveMatrix.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

int main()
{
	SaveMatrix<int>* matrix = new SaveMatrix<int>{ 2,2 };
	delete matrix;


	_CrtDumpMemoryLeaks();
}
