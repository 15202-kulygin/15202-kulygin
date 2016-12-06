//
// Created by glavak on 23.09.16.
//

#ifndef MYARRAY_SHAREDPOINTER_H
#define MYARRAY_SHAREDPOINTER_H

#include <utility>

template<class T>
struct PointerCounter
{
    T * obj = nullptr;
    int count = 1;
};

template<class T>
class SharedPointer
{
public:
    SharedPointer(T * obj)
    {
        this->counter = new PointerCounter<T>();
        this->counter->obj = obj;
    }

    SharedPointer()
    {
        this->counter = nullptr;
    }

    // Copy constructor
    SharedPointer(SharedPointer & other)
    {
        this->counter = other.counter;
        counter->count++;
    }

    ~SharedPointer()
    {
        if (counter != nullptr)
        {
            counter->count--;
            if (counter->count == 0)
            {
                delete counter->obj;
                delete counter;
            }
        }
    }

    // Copy assignment
    SharedPointer & operator=(SharedPointer & other)
    {
        counter->count--;
        if (counter->count == 0)
        {
            delete counter->obj;
            delete counter;
        }

        this->counter = other.counter;
        this->counter->count++;

        return *this;
    }

    T * operator->() const
    {
        return get();
    }

    T & operator*() const
    {
        return *get();
    }

    explicit operator bool() const
    {
        return counter != nullptr;
    }

    T * get() const
    {
        return counter->obj;
    }

    void reset(T * obj)
    {
        counter->count--;
        if (counter->count == 0)
        {
            delete counter->obj;
            delete counter;
        }

        this->counter = new PointerCounter<T>();
        this->counter->obj = obj;
    }

    void swap(SharedPointer & other)
    {
        std::swap(this->counter, other.counter);
    }

private:
    PointerCounter<T> * counter;
};

#endif //MYARRAY_SHAREDPOINTER_H
