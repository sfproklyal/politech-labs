#pragma once

template <typename T>
class Stack
{
public:
    virtual ~Stack() {};
    virtual void push(const T& e) = 0;
    virtual T pop() = 0;
    virtual bool isEmpty() const = 0;
};


