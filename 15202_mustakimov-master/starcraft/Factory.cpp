//
// Created by glavak on 14.10.16.
//

#include "Factory.h"

Unit * Factory::create(const std::string & id)
{
    return creators.at(id)();
}

bool Factory::reg(const std::string & id, const creator_t & creator)
{
    creators[id] = creator;
    return true;
}
