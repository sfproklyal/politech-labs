#pragma once
#include <cstddef>
#include "Exceptions.h"
#include "Queue.h"

template <typename T>
class QueueVector : public Queue
{
private:
    T* data_;
    size_t size_;
    size_t capacity_
    size_t head_;
    size_t tail_;
public:
    

};