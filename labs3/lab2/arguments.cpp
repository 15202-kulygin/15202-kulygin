#include "arguments.h"


std::string get_argument_value(char * argument)
{
	int arg_type_len = 1;
	int i = 0;
	while ('=' != argument[i])
	{
		++arg_type_len;
		++i;
	}
	int name_len = strlen(argument) - arg_type_len;
	char * result_char = new char[name_len + 1];
	for (int k = 0; k < name_len; ++k)
	{
		result_char[k] = argument[k + arg_type_len];
	}
	result_char[name_len] = '\0';
	std::string result(result_char);
	delete [] result_char;
	return result;
}

int get_matrix_from_file(FILE * input, int matrix[8][3])
{
	int rc = 0;
	int line_ind = 0;
	while (3 == (rc = fscanf(input, "%d %d %d", &matrix[line_ind][0], &matrix[line_ind][1], &matrix[line_ind][2])))
	{
		line_ind++;
	}
	return line_ind;
}