//
// Created by glavak on 23.09.16.
//

#include <gtest/gtest.h>
#include "../SharedPointer.h"

struct test
{
    int a;
};

TEST(SharedPointerTests, SwapTest)
{
    SharedPointer<test> pointerA(new test());
    SharedPointer<test> pointerB(new test());

    (*pointerA).a = 5;
    pointerB->a = 6;

    pointerA.swap(pointerB);

    ASSERT_EQ((*pointerA).a, 6);
    ASSERT_EQ(pointerB->a, 5);
}

TEST(SharedPointerTests, BoolTest)
{
    SharedPointer<test> pointerA(new test());
    if (!pointerA) FAIL();

    SharedPointer<test> pointerB;
    if (pointerB) FAIL();
}

TEST(SharedPointerTests, CounterTest)
{
    SharedPointer<test> pointerA(new test());

    pointerA->a = 5;

    {
        SharedPointer<test> pointerB(new test());
        pointerA = pointerB;

        pointerB->a = 42;
    }

    if (!pointerA) FAIL();
    ASSERT_EQ(pointerA->a, 42);
}