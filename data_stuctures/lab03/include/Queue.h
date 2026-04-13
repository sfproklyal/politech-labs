#pragma once

template <typename T> 
class Queue
{
public:
    virtual ~Queue() {};
    virtual void enQueue (const T& e) = 0;
    virtual T deQueue() = 0;
    virtual bool isEmpty() = 0;
};