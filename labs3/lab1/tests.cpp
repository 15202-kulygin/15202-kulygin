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