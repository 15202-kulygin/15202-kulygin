#include <gtest/gtest.h>
#include "../MyArray.h"

TEST(MyArrayTests, AddGetTest)
{
	MyArray<int> arr;

    arr.add(2);
    arr.add(42);
    arr.add(-5513);

	ASSERT_EQ(2, arr[0]);
	ASSERT_EQ(42, arr.get(1));
	ASSERT_EQ(-5513, arr[2]);
}

TEST(MyArrayTests, SetTest)
{
	MyArray<int> arr;

    arr.add(2);
    arr.add(42);

	arr[0] = 5;
	arr[1] = 4;

	ASSERT_EQ(5, arr[0]);
	ASSERT_EQ(4, arr.get(1));
}

TEST(MyArrayTests, GetOutOfRange)
{
	MyArray<int> arr;

    arr.add(2);

	ASSERT_ANY_THROW(arr.get(-1));
	ASSERT_ANY_THROW(arr.get(1));
}

TEST(MyArrayTests, InsertGetTest)
{
	MyArray<int> arr;

	arr.insert(0, 2);
	arr.insert(0, 1);
	arr.insert(2, 3);

	ASSERT_EQ(1, arr[0]);
	ASSERT_EQ(2, arr[1]);
	ASSERT_EQ(3, arr[2]);
}

TEST(MyArrayTests, InsertOutOfRange)
{
	MyArray<int> arr;

	arr.insert(0, 2);

	ASSERT_ANY_THROW(arr.insert(-1, 5));
	ASSERT_ANY_THROW(arr.insert(5, 8));
}

TEST(MyArrayTests, CopyConstructorTest)
{
	MyArray<int> arr;

    arr.add(1);
    arr.add(2);
    arr.add(3);

	MyArray<int> arr2(arr);

	arr2[1] = 42;

	ASSERT_EQ(2, arr[1]);
	ASSERT_EQ(3, arr2[2]);
}

TEST(MyArrayTests, AssignOperatorTest)
{
	MyArray<int> arr;

    arr.add(1);
    arr.add(2);
    arr.add(3);

	MyArray<int> arr2;

	arr2 = arr;

	arr2[1] = 42;

	ASSERT_EQ(2, arr[1]);
	ASSERT_EQ(3, arr2[2]);
}