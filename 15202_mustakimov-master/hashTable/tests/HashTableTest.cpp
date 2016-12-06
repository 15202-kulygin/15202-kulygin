#include <gtest/gtest.h>
#include "../HashTable.h"

TEST(MyArrayTests, AddGetTest)
{
    HashTable table;

    table.insert("Aab", Value{18, 42});
    table.insert("Aba", Value{19, 100});
    table.insert("Harold", Value{18, 64});

    ASSERT_EQ(42, table.at("Aab").weight);
    ASSERT_EQ(19, table.at("Aba").age);
    ASSERT_ANY_THROW(table.at("Simon"));
}

TEST(MyArrayTests, RehashTest)
{
    HashTable table;

    table.insert("Aab", Value{18, 42});
    table.insert("Aba", Value{19, 100});
    table.insert("Harold", Value{18, 64});

    for (int i = 0; i < 1000; i++)
    {
        table.insert(std::to_string(i).c_str(), Value{5,3});
    }

    ASSERT_EQ(42, table.at("Aab").weight);
    ASSERT_EQ(19, table.at("Aba").age);
    ASSERT_ANY_THROW(table.at("Simon"));
}

TEST(MyArrayTests, ClearEmptyTest)
{
    HashTable table;

    table.insert("Aab", Value{18, 42});
    table.insert("Aba", Value{19, 100});
    table.insert("Harold", Value{18, 64});

    ASSERT_FALSE(table.empty());

    table.clear();

    ASSERT_TRUE(table.empty());

    ASSERT_ANY_THROW(table.at("Aab"));
    ASSERT_FALSE(table.contains("Aba"));
    ASSERT_FALSE(table.contains("Harold"));
}

TEST(MyArrayTests, EraseContainTest)
{
    HashTable table;

    table.insert("Aab", Value{18, 42});
    table.insert("Aba", Value{19, 100});
    table.insert("Harold", Value{18, 64});

    ASSERT_TRUE(table.contains("Harold"));
    ASSERT_FALSE(table.contains("Shaw"));

    ASSERT_TRUE(table.erase("Aab"));
    ASSERT_FALSE(table.erase("John"));
    ASSERT_TRUE(table.erase("Harold"));

    ASSERT_TRUE(table.contains("Aba"));
    ASSERT_FALSE(table.contains("Harold"));

    ASSERT_ANY_THROW(table.at("Aab"));
    ASSERT_ANY_THROW(table.at("Bob"));
    ASSERT_EQ(100, table.at("Aba").weight);
}

TEST(MyArrayTests, OperatorSizeTest)
{
    HashTable table;

    table["Aab"] = Value{18, 42};
    table["Aba"] = Value{19, 100};
    table["Harold"] = Value{18, 64};

    ASSERT_EQ(3, table.size());

    ASSERT_TRUE(table.contains("Harold"));

    ASSERT_EQ(18, table["Aab"].age);
    ASSERT_EQ(64, table["Harold"].weight);

    table["Aab"].age = 42;
    table["Shaw"].age = 30;

    ASSERT_EQ(4, table.size());

    ASSERT_EQ(42, table["Aab"].age);
    ASSERT_EQ(30, table["Shaw"].age);
}

TEST(MyArrayTests, CopyTest)
{
    HashTable table;

    table["Aab"] = Value{18, 42};
    table["Aba"] = Value{19, 100};
    table["Harold"] = Value{18, 64};

    HashTable table2 = table;

    table2["Aab"].age = 42;
    table["Harold"].age = 30;

    ASSERT_EQ(18, table["Aab"].age);
    ASSERT_EQ(30, table["Harold"].age);

    ASSERT_EQ(42, table2["Aab"].age);
    ASSERT_EQ(18, table2["Harold"].age);

    table["Shaw"].age = 30;

    ASSERT_FALSE(table2.contains("Shaw"));
}

TEST(MyArrayTests, SwapTest)
{
    HashTable table;

    table["Aab"] = Value{18, 42};
    table["Aba"] = Value{19, 100};
    table["Harold"] = Value{18, 64};

    HashTable table2 = table;

    table2["Aab"].age = 42;
    table["Harold"].age = 30;

    ASSERT_EQ(18, table["Aab"].age);
    ASSERT_EQ(30, table["Harold"].age);

    ASSERT_EQ(42, table2["Aab"].age);
    ASSERT_EQ(18, table2["Harold"].age);

    table["Shaw"].age = 30;

    ASSERT_FALSE(table2.contains("Shaw"));

    table.swap(table2);

    ASSERT_EQ(18, table2["Aab"].age);
    ASSERT_EQ(30, table2["Harold"].age);

    ASSERT_EQ(42, table["Aab"].age);
    ASSERT_EQ(18, table["Harold"].age);

    ASSERT_FALSE(table.contains("Shaw"));
}

TEST(MyArrayTests, EqualityTest)
{
    HashTable table;
    table["Aab"] = Value{18, 42};
    table["Aba"] = Value{19, 100};
    table["Harold"] = Value{42, 64};

    HashTable table2 = table;
    table2["Aab"] = Value{18, 42};
    table2["Aba"] = Value{19, 100};
    table2["Harold"] = Value{42, 64};

    ASSERT_TRUE(table == table2);
    ASSERT_FALSE(table != table2);

    table2["Aab"] = Value{20, 42};
    ASSERT_FALSE(table == table2);
    ASSERT_TRUE(table != table2);

    table2["Aab"] = Value{18, 42};
    table2["Shaw"] = Value{18, 42};
    ASSERT_FALSE(table == table2);
    ASSERT_TRUE(table != table2);
}