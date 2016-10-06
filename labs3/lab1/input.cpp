#include "input.h"

bool inputcheck(int argc, char ** argv) /* check if filename was put in */
{
	if ((argc == 1) || (NULL == argv[1]))
	{
		return false;
	}
	else
	{
		return true;
	}
}
bool filecheck(int argc, char ** argv, FILE* input_file) /* check if it's possible to open input file */
{
	if (NULL == input_file)
	{
		return false;
	}
	else
	{
		return true;
	}
}

