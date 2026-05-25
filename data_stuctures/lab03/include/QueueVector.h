#pragma once
#include <cstddef>
#include "Exceptions.h"
#include "Queue.h"

template <typename T>
class QueueVector : public Queue<T>
{
private:
    T* data_;
    size_t size_;
    size_t capacity_;
    size_t head_;
    size_t tail_;

    void resize() {
        const size_t newCapacity = capacity_ * 2;
        T* newData = new T[newCapacity];

        for (size_t i = 0; i < size_; ++i) {
            newData[i] = data_[(head_ + i) % capacity_];
        }

        delete[] data_;
        data_ = newData;
        capacity_ = newCapacity;
        head_ = 0;
        tail_ = size_;
    }

public:
    QueueVector() = delete;

    explicit QueueVector(size_t newCapacity) {
        if (newCapacity == 0) throw WrongQueueSize();

        data_ = new T[newCapacity];
        size_ = 0;
        capacity_ = newCapacity;
        head_ = 0;
        tail_ = 0;
    }

    QueueVector(const QueueVector& other) {
        data_ = new T[other.capacity_];
        size_ = other.size_;
        capacity_ = other.capacity_;
        head_ = 0;
        tail_ = size_;

        for (size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[(other.head_ + i) % other.capacity_];
        }
    }

    QueueVector(QueueVector&& other)
        : data_(other.data_),
          size_(other.size_),
          capacity_(other.capacity_),
          head_(other.head_),
          tail_(other.tail_) {
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
        other.head_ = 0;
        other.tail_ = 0;
    }

    ~QueueVector() override {
        delete[] data_;
    }

    void enQueue(const T& e) override {
        if (size_ == capacity_) {
            resize();
        }

        data_[tail_] = e;
        tail_ = (tail_ + 1) % capacity_;
        ++size_;
    }

    T deQueue() override {
        if (isEmpty()) {
            throw QueueUnderflow();
        }

        T result = data_[head_];
        head_ = (head_ + 1) % capacity_;
        --size_;
        return result;
    }

    bool isEmpty() override {
        return size_ == 0;
    }

    QueueVector& operator=(const QueueVector& other) {
        if (this == &other) return *this;

        T* newData = new T[other.capacity_];
        for (size_t i = 0; i < other.size_; ++i) {
            newData[i] = other.data_[(other.head_ + i) % other.capacity_];
        }

        delete[] data_;
        data_ = newData;
        size_ = other.size_;
        capacity_ = other.capacity_;
        head_ = 0;
        tail_ = size_;

        return *this;
    }

    QueueVector& operator=(QueueVector&& other) {
        if (this == &other) return *this;

        delete[] data_;
        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        head_ = other.head_;
        tail_ = other.tail_;

        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
        other.head_ = 0;
        other.tail_ = 0;

        return *this;
    }
};
