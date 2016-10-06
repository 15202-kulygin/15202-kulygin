#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include "input.h"
#include "hash.h"

using namespace std;

int main (int argc, char ** argv)
{	
	string str;
    ifstream input;
    input.open("qwe.txt");
    HashTable * ht = new HashTable();
    while (getline(input, str))
    {
        //cout << "STRING " << str << endl;
        Key key = str;
        Value value;
        getkey(str, key);
        getvalue(str, value);
        //cout << key << ' ' << value.age << ' ' << value.weight << " JJJJJJJ" << endl;
        ht->insert(key, value);
        //cout << "ok " << endl;
    }
    cout << endl << endl;
    ht->print();
    input.close();
	
}