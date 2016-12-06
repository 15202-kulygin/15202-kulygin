//
// Created by glavak on 14.10.16.
//

#ifndef STARCRAFT_FACTORY_H
#define STARCRAFT_FACTORY_H

#include <string>
#include <unordered_map>
#include "Unit.h"

class Factory
{
public:
    typedef Unit * (* creator_t)();

    static Factory * getInstance()
    {
        static Factory f;
        return &f;
    }

    Unit * create(const std::string & id);

    bool reg(const std::string & id, const creator_t & creator);

    Factory(const Factory &) = delete;

    Factory & operator=(const Factory &) = delete;

private:
    Factory()
    {}

    std::unordered_map<std::string, creator_t> creators;
};


#endif //STARCRAFT_FACTORY_H
