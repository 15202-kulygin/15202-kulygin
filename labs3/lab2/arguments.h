#ifndef ARGUMENTS_H
#define ARGUMENTS_H

#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>

std::string get_argument_value(char * argument);
int get_matrix_from_file(FILE * input, int matrix[8][3]);


#endif