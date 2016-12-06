//
// Created by glavak on 23.09.16.
//

#include <gtest/gtest.h>
#include "../SmartPointer.h"

struct test
{
    int a;
};

TEST(SmartPointerTests, SwapTest)
{
    SmartPointer<test> pointerA(new test());
    SmartPointer<test> pointerB(new test());

    (*pointerA).a = 5;
    pointerB->a = 6;

    pointerA.swap(pointerB);

    ASSERT_EQ((*pointerA).a, 6);
    ASSERT_EQ(pointerB->a, 5);
}

TEST(SmartPointerTests, BoolTest)
{
    SmartPointer<test> pointerA(new test());

    pointerA->a = 5;

    if (!pointerA) FAIL();

    pointerA.release();

    if (pointerA) FAIL();
}