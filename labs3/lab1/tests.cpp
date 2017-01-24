#include <iostream>
#include <fstream>
#include <string>
#include "include/gtest/gtest.h"
#include "hash.h"

//g++ -Lgtestbuild -I./include tests.cpp main.cpp input.cpp hash.cpp -lgtest
 
TEST (HashTests, EqualityOp)
{
	HashTable ht1;
	HashTable ht2;
	EXPECT_TRUE(ht1 == ht2);
	Value temp1 = {1, 1};
	ht1.insert("qwe", temp1);
	ht2.insert("qwe", temp1);
	EXPECT_TRUE(ht1 == ht2);
	ht1.insert("asd", temp1);
	ht2.insert("zxc", temp1);
	EXPECT_TRUE(ht1 != ht2);
	EXPECT_FALSE(ht1 == ht2);
}

TEST (HashTests, Erase)
{
	HashTable ht;
	Value temp = {1, 1};
	ht.insert("qwe", temp);
	ASSERT_FALSE(ht.empty());
	EXPECT_TRUE(ht.search("qwe"));
	ht.erase("qwe");
	EXPECT_TRUE(ht.empty());
	EXPECT_FALSE(ht.search("qwe"));
}

TEST (HashTests, GetHash)
{
	Key k = "eargaergvaefvawevajjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjkjhkjguyfcytcttt1777777777777777777wefwavwfevawefawefvavregvtgvarvgawevef";
	HashTable ht;
	int hash = ht.gethash(k);
	ASSERT_FALSE(hash < 0);
	ASSERT_FALSE(hash >= ht.getcapacity());
}

TEST (HashTests, Constructor)
{
	HashTable * pht = new HashTable;
	ASSERT_FALSE(pht->getcapacity() <= 0);
	EXPECT_TRUE(pht->getsize() == 0);
	EXPECT_TRUE(pht->empty());
	Value temp = {1, 1};
	pht->insert("qwe", temp);
	HashTable ht = *pht;
	ASSERT_FALSE(pht->getcapacity() <= 0);
	EXPECT_FALSE(ht.empty());
	EXPECT_FALSE(pht->getsize() == 0);
	ht.erase("qwe");
	EXPECT_TRUE(ht.empty());
	delete pht;
}

TEST (HashTests, Insert)
{
	HashTable ht;
	Value temp = {1, 1};
	bool check = ht.insert("qwe", temp);
	EXPECT_TRUE(check);
	EXPECT_FALSE(ht.empty());
	EXPECT_TRUE(ht.search("qwe"));
	check = ht.insert("qwe", temp);
	EXPECT_FALSE(check);
	check = ht.insert("abc", temp);
	EXPECT_TRUE(check);

	/*for (int i = 0; i < 50; ++i)
	{
		std::cout << "OK";
		std::string s;
		ht.insert(c, temp);
	}*/
}

TEST (HashTests, IndexOp)
{
	HashTable ht;
	Value check = ht["qwe"];
	EXPECT_EQ(check.age, -1);
	EXPECT_EQ(check.weight, -1);
	Value temp = {1, 1};
	ht.insert("qwe", temp);
	check = ht["qwe"];
	EXPECT_NE(check.age, -1);
	EXPECT_NE(check.weight, -1);
}

TEST (HashTests, ConstAt)
{
	HashTable ht;
	const Value temp = {1, 1};
	ht.insert("qwe", temp);
	const HashTable ht2 = ht;
	Value check = ht2.at("qwe");
	check.age = 0;
}

TEST (HashTests, At)
{
	HashTable ht;
	const Value temp = {1, 1};
	ht.insert("qwe", temp);
	bool check = true;
	try
  	{
    	Value ep = ht.at("qwe");
  	}
  	catch(int a)
  	{
    	cout << "Caught exception number:  " << a << endl;
    	check = false;
  	}
  	EXPECT_TRUE(check);
  	check = false;
  	cout << "No exception detected" << endl;
	ht.erase("qwe");
	try
  	{
    	Value ep = ht.at("qwe");
  	}
  	catch(int a)
  	{
    	cout << "Caught exception number:  " << a << endl;
    	check = true;
  	}
  	//cout << "No exception detected" << endl;
  	EXPECT_TRUE(check);
}

TEST (HashTests, Rehash)
{
	std::string str;
    std::ifstream input;
    input.open("crusoe.txt");
    HashTable ht;
    //std::cout << "REHASH TEST" << std::endl;
    int i = 0;
    HashTable ht2;
    while (getline(input, str))
    {
    	if (1000 == i)
    	{
    		ht2 = ht;
    	}
    	if (0 == i % 1000)
    	{
    		//std::cout << "ADDED " << i << std::endl;
    	}
        Key key = str;
        Value value;
        getkey(str, key);
        getvalue(str, value);
        ht.insert(key, value);
        ++i;
    }
    input.close();
    //std::cout << "FILE ADDED" << std::endl;
    bool safe_check = true;
    bool correct_check = true;
    bool full_check = true;
    bool size_check = true;
    for (int j = 0; i < ht2.getsize(); ++j)
    {
    	if (false == ht.search(ht2.get_data()[i].key))
    	{
    		safe_check = false;
    	}
    }
    Value temp = {1, 1};
    ht2.insert("rrrrr", temp);
    //ht.insert("rrrrr", temp);
    if (true == ht.search("rrrrr"))
    {
    	correct_check = false;
    }
    input.open("crusoe.txt");
    while (getline(input, str))
    {
        Key key = str;
        getkey(str, key);
       	if (false == ht.search(key))
       	{
       		full_check = false;
       	}
    }
    if (ht.getsize() != i)
    {
    	size_check = false;
    }
    input.close();
    EXPECT_TRUE(safe_check);
    EXPECT_TRUE(correct_check);
    EXPECT_TRUE(full_check);
    EXPECT_TRUE(size_check);
    
}


