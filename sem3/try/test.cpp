#include "include/gtest/gtest.h"

//g++ -Lgtestbuild -I./include test.cpp try.cpp -lgtest
 
TEST(firstTest, abs)
{
  EXPECT_EQ(1, abs( -1 ));
  EXPECT_EQ(1, abs( 1 ));
}