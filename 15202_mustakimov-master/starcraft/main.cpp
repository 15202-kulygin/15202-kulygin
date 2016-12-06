#include <iostream>
#include <string>
#include <memory>

#include "Unit.h"
#include "BattleCruiser.h"
#include "Zergling.h"
#include "Factory.h"

int main()
{
    Factory * f = Factory::getInstance();

    std::string uid = "siegetank";

    std::unique_ptr<Unit> u(f->create(uid));
    u->move(948751, 1);

    return 0;
}