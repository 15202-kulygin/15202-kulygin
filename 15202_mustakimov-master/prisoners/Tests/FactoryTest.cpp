//
// Created by glavak on 21.10.16.
//

#include <gtest/gtest.h>
#include "../Factory.h"
#include "../Strategies/Traitor.h"

Traitor * expected = new Traitor();

Strategy * testCreator()
{
    return static_cast<Strategy*>(expected);
}

TEST(FactoryTests, Test)
{
    Factory<Strategy, std::string>::getInstance()->reg("test", testCreator);

    auto actual = Factory<Strategy, std::string>::getInstance()->create("test");

    ASSERT_EQ(expected, actual);
}
