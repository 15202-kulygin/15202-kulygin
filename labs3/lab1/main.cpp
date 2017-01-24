#include <iostream>
#include <fstream>
#include <string>
#include "input.h"
#include "hash.h"
#include "include/gtest/gtest.h"

//g++ -Lgtestbuild -I./include --coverage tests.cpp main.cpp input.cpp hash.cpp -lgtest
//gcov -abcfu tests.cpp main.cpp input.cpp hash.cpp 


//assignment --- *ht = *ht2;

using namespace std;

GTEST_API_ int main (int argc, char ** argv)
{	
	string str;
    ifstream input;
    input.open("qwe.txt");
    HashTable ht;
    while (getline(input, str))
    {
        Key key = str;
        Value value;
        getkey(str, key);
        getvalue(str, value);
        ht.insert(key, value);
    }

    cout << endl << endl;
    //ht->print();

    input.close();
    ht.print();
    input.open("asd.txt");
    HashTable ht2;
    //ht2.print();
    //input.close();
    while (getline(input, str))
    {
        
        Key key = str;
        Value value;
        getkey(str, key);
        getvalue(str, value);
        
        ht2.insert(key, value);
        
    }
    input.close();
    ht2.print();
    cout << "Running tests\n" << endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
 
}
