#include "int_stack.h"
#include <stddef.h>
#include <iostream>

namespace xi {

    IntStack::IntStack(size_t sz)
    {
        _head = -1;
        _ssize = sz;
        _stack = new int[sz];
    }

    IntStack::~IntStack()
    {
        delete[] _stack;
    }

    void IntStack::push(int el)
    {
        if(isFull())
            throw std::logic_error("Stack overflow");
        _stack[++_head] = el;
    }

    int IntStack::pop()
    {
        if(isEmpty())
            throw std::logic_error("Stack is empty");
        return _stack[_head--];
    }

    int IntStack::top()
    {
        if(isEmpty())
            throw std::logic_error("Stack is empty");
        return _stack[_head];
    }

    void IntStack::clear()
    {
        _head = -1;
    }

    bool IntStack::isEmpty() const
    {
        return _head == -1;
    }

    bool IntStack::isFull() const
    {
        return _head + 1 == _ssize;
    }

} // namespace xi