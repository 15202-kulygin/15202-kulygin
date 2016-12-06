//
// Created by glavak on 16.10.16.
//

#include "Traitor.h"
#include "../Factory.h"

namespace
{
    Strategy * create()
    {
        return new Traitor();
    }

    bool registered = Factory<Strategy, std::string>::getInstance()->reg("traitor", create);
}

Traitor::~Traitor()
{

}

Decision Traitor::Decide()
{
    return Decision::Defect;
}

void Traitor::PrintData(std::ostream & stream) const
{
    stream << "Traitor";
}
