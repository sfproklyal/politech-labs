#pragma once
#include <cstddef>
#include "Stack.h"
#include "Exceptions.h"


template <typename T>
class StackArray : public Stack <T>
{
private:
    T* data_;
    size_t size_;
    size_t capacity_;
public:
    StackArray() = delete;
    StackArray(size_t newCapacity) {
        if (newCapacity == 0) throw WrongStackSize();
        data_ = new T[newCapacity];
        size_ = 0;
        capacity_ = newCapacity;

    };

    StackArray(const StackArray& other) {
        data_ = new T[other.capacity_];
        for (size_t i = 0; i < other.size_; i++) {
            data_[i] = other.data_[i];
        }
        size_ = other.size_;
        capacity_ = other.capacity_;
    };

    StackArray(StackArray&& other) : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    };

    ~StackArray() override {
        delete[] data_;
    };

    //methods
    void push(const T& e) override {
        if (size_ == capacity_) {
            throw StackOverflow();
        }
        data_[size_] = e;
        size_++;
    };


    T pop() override {
        if (size_ == 0) {
            throw StackUnderflow();
        }
        --size_;
        return data_[size_];
    };

    bool isEmpty() const override {
        return size_ == 0;
    };

    //operators
    StackArray& operator=(const StackArray& other) {
        if (this == &other) return *this;

        T* newData = new T[other.capacity_];
        for (size_t i = 0; i < other.size_; ++i) {
            newData[i] = other.data_[i];
        }

        delete[] data_;
        data_ = newData;
        size_ = other.size_;
        capacity_ = other.capacity_;

        return *this;
    };

    StackArray& operator=(StackArray&& other) {
        if (this == &other) return *this;
        
        delete[] data_;
        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;

        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;

        return *this;
    };
};
