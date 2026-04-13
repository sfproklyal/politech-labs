#pragma once
#include "Stack.h"
#include <stdexcept>

template <typename T>
class StackArray : public Stack<T> {
private:
    T* data_;
    size_t size_;
    size_t capacity_;

public:
    StackArray() = delete;
    StackArray(const size_t& newCapacity) : data_(nullptr), size_(0), capacity_(0) {
        if (newCapacity == 0) {
            throw std::out_of_range("Wrong stack size");
        }

        data_ = new T[newCapacity];
        capacity_ = newCapacity;
        
    };

    StackArray(const StackArray& other) : data_(nullptr), size_(other.size_), capacity_(other.capacity_) {
        data_ = new T[other.capacity_];
        for (int i = 0; i < other.size_; i++) {
            data_[i] = other.data_[i];
        }
    }

    StackArray(StackArray&& other) : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {     
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;

    }

    ~StackArray() {
        delete[] data_;
    }
    
    StackArray& operator=(const StackArray& other) {
        if (this == &other) return *this;

        T* newData = new T[other.capacity_];
        for (size_t i = 0; i < other.size_; i++) {
            newData[i] = other.data_[i];
        }

        delete[] data_;
        data_ = newData;
        size_ = other.size_;
        capacity_ = other.capacity_;

        return *this;
    }

    //StackArray& operator=(StackArray&& other) {
    //    if (this == &other) return *this;


    //}

    void push(const T& e) override {
        if (size_ == capacity_) {
            throw std::out_of_range("Stack overflow");
        }
        data_[size_++] = e;   
    }

    T pop() override {
        if (size_ == 0) {
            throw std::out_of_range("Stack underflow");
        }
        return data_[--size_];
    }

    bool isEmpty() override {
        if (size_ == 0) return true;
        return false;
    }

    

};
