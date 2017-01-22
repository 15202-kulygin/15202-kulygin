#if !defined (INPUT_H)
#define INPUT_H
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

typedef std::string Key;

typedef struct Value {
	unsigned int age;
	unsigned int weight;
} Value;

bool inputcheck(int argc, char ** argv);
bool filecheck(int argc, char ** argv, FILE* input_file);
void getkey(std::string str, Key& k);
void getvalue(std::string str, Value& v);



#endif 