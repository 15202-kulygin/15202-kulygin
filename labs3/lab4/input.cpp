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

void getkey(string str, Key& k)
{
    char * newstr = (char *)str.c_str();
    int i = 0;
    char * key = new char[100];
    while(' ' != newstr[i]) // getting the key
    {
        key[i] = newstr[i];
        ++i;
    }
    key[i] = '\0';
    k = key;
    delete [] key;

}
void getvalue(string str, Value& v)
{
    //cout << v.age << v.weight << "check << endl;"
    char * newstr = (char *)str.c_str();
    char * age = new char[100];
    char * weight = new char[100];
    int i = 0;
    int age_ind = 0;
    int weight_ind = 0;
    while(' ' != newstr[i]) 
    {
        ++i;
    }
    ++i;
    while(' ' != newstr[i]) 
    {
        age[age_ind] = newstr[i];
        ++age_ind;
        ++i;
    }
    ++i;
    while('\0' != newstr[i]) 
    {
        weight[weight_ind] = newstr[i];
        ++weight_ind;
        ++i;
    }
    int res_age = atoi(age);
    int res_weight = atoi(weight);
    delete [] age;
    delete [] weight;
    
    v.age = res_age;
   // cout << "ok" << endl;
    v.weight = res_weight;
}
