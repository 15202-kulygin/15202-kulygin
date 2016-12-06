//
// Created by glavak on 02.11.16.
//

#ifndef PRISONERS_ERRORPOLICIES_H
#define PRISONERS_ERRORPOLICIES_H

#include <string>

class ExceptionErrorPolicy
{
public:
    static void* HandleError(const std::string & errorMessage)
    {
        throw "Unknown id" + errorMessage;
    }
};

class NullPtrErrorPolicy
{
public:
    static void* HandleError(const std::string & errorMessage)
    {
        return nullptr;
    }
};

#endif //PRISONERS_ERRORPOLICIES_H
