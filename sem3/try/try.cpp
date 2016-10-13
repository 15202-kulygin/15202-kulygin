#include <iostream>
#include "include/gtest/gtest.h"
 
// g++ -Lgtestbuild -I./include test.cpp try.cpp -lgtest

GTEST_API_ int main(int argc, char **argv) {
  std::cout << "Running main() from testmain.cc\n";
 
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}