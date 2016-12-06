//
// Created by glavak on 23.09.16.
//

#ifndef MYARRAY_SMARTPOINTER_H
#define MYARRAY_SMARTPOINTER_H

#include <utility>

template<class T>
class SmartPointer
{
public:
    SmartPointer(T * obj)
    {
        this->obj = obj;
    }

    SmartPointer()
    {
        this->obj = nullptr;
    }

    // Copy constructor
    SmartPointer(SmartPointer & other)
    {
        this->obj = other.get();
        other.release();
    }

    ~SmartPointer()
    {
        delete obj;
    }

    // Copy assignment
    SmartPointer & operator=(SmartPointer & other)
    {
        if(&other != this)
        {
            reset(other.get());
            other.release();
        }
        return *this;
    }

    T * operator->() const
    {
        return obj;
    }

    T & operator*() const
    {
        return *obj;
    }

    explicit operator bool() const
    {
        return obj != nullptr;
    }

    T * get() const
    {
        return obj;
    }

    T * release()
    {
        T * res = obj;
        obj = nullptr;
        return res;
    }

    void reset(T * obj)
    {
        delete this->obj;
        this->obj = obj;
    }

    void swap(SmartPointer & other)
    {
        std::swap(this->obj, other.obj);
    }

private:
    T * obj;
};

#endif //MYARRAY_SMARTPOINTER_H
