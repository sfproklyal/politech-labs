#pragma once
#include <utility>
#include <stdexcept>
#include <iostream>


template <typename T>
class DoubleOrderedDuplicateList
{
private:
    struct Node {
        T data_;
        Node* next_;
        Node* prev_;

        Node(const T& value) : data_(value), next_(nullptr), prev_(nullptr) {};
        Node(T&& value) : data_(std::move(value)), next_(nullptr), prev_(nullptr) {};


    };


    Node* head_;
    Node* tail_;
    size_t size_;


    template <typename U>
    void insertTemplate(U&& value) {
        Node* newNode = new Node(std::forward<U>(value));
        try {
            if (head_ == nullptr) {
                head_ = newNode;
                tail_ = newNode;
                size_++;
                return;
            }

            if (newNode->data_ < head_->data_) {
                newNode->next_ = head_;
                head_->prev_ = newNode;
                head_ = newNode;
                size_++;
                return;
            }

            Node* current = head_;
            while (current->next_ != nullptr && !(newNode->data_ < current->next_->data_)) {
                current = current->next_;
            }

            newNode->next_ = current->next_;
            newNode->prev_ = current;

            if (current->next_ != nullptr) {
                current->next_->prev_ = newNode;
            }
            else {
                tail_ = newNode;
            }
            current->next_ = newNode;
            size_++;
        }
        catch (std::exception) {
            delete newNode;
            throw;
        }
       
    }

    void deleteNode(Node* node) {
        if (node == nullptr) return;
        if (node->prev_ != nullptr) {
            node->prev_->next_ = node->next_;
        }
        else {
            head_ = node->next_;
        }
        if (node->next_ != nullptr) {
            node->next_->prev_ = node->prev_;
        }
        else {
            tail_ = node->prev_;
        }
        delete node;
        size_--;

    }

    bool isEqual(const T& a, const T& b) const {
        return !(a < b) && !(b < a);
    }

public:
    DoubleOrderedDuplicateList() : head_(nullptr), tail_(nullptr), size_(0) {}
    DoubleOrderedDuplicateList(const T& value) : head_(new Node(value)), tail_(nullptr), size_(1) {
        tail_ = head_;
    }
    DoubleOrderedDuplicateList(const DoubleOrderedDuplicateList& other)
        : head_(nullptr), tail_(nullptr), size_(0) {
        try {
            Node* current = other.head_;
            while (current != nullptr) {
                insert(current->data_);
                current = current->next_;
            }
        }
        catch (std::exception) {
            clear();
            throw;
        }


    }
    DoubleOrderedDuplicateList(DoubleOrderedDuplicateList&& other)
        : head_(other.head_), tail_(other.tail_), size_(other.size_) {
        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.size_ = 0;
    }
    ~DoubleOrderedDuplicateList() {
        clear();
    }

    void swap(DoubleOrderedDuplicateList& other) {
        std::swap(head_, other.head_);
        std::swap(tail_, other.tail_);
        std::swap(size_, other.size_);
    }

    // operators

    DoubleOrderedDuplicateList& operator=(const DoubleOrderedDuplicateList& other) {
    if (this != &other) {
        DoubleOrderedDuplicateList temp(other);

        swap(temp);
    }
    return *this;
    }

    DoubleOrderedDuplicateList& operator=(DoubleOrderedDuplicateList&& other) {
        if (this != &other) {
            clear();

            head_ = other.head_;
            tail_ = other.tail_;
            size_ = other.size_;

            other.head_ = nullptr;
            other.tail_ = nullptr;
            other.size_ = 0;
        }
        return *this;
    }
    
    DoubleOrderedDuplicateList& operator+=(const T& value) {
        insert(value);
        return *this;
    }

    // access

    const T& head() const {
        if (head_ == nullptr) throw std::out_of_range("List is empty");
        return head_->data_;
    }

    const T& tail() const {
        if (tail_ == nullptr) throw std::out_of_range("List is empty");
        return tail_->data_;
    }

    bool search(const T& key) const {
        Node* current = head_;
        while (current != nullptr && current->data_ < key) {
            current = current->next_;
        }
        if (current != nullptr && isEqual(current->data_, key)) {
            return true;
        }
        return false;
    }

    // insert

    void insert(const T& value) {
        insertTemplate(value);
    }

    void insert(T&& value) {
        insertTemplate(std::move(value));
    }


    // remove

    void removeHead() {
        if (head_ == nullptr) {
            return;
        }

        Node* temp = head_;
        head_ = head_->next_;

        if (head_ != nullptr) {
            head_->prev_ = nullptr;
        }
        else {
            tail_ = nullptr;
        }

        delete temp;
        size_--;
    }

    void clear() {
        while (head_ != nullptr) {
            removeHead();
        }
    }

    // info

    size_t size() const {
        return size_;
    }

    bool isEmpty() const {
        return size_ == 0;
    }

    void print() const {
        Node* current = head_;
        while (current != nullptr) {
            std::cout << current->data_;
            current = current->next_;
        }
    }

    void printBack() const {
        Node* current = tail_;
        while (current != nullptr) {
            std::cout << current->data_;
            current = current->prev_;
        }
    }

    // var 4

    void removeKey(const T& keyBegin, const T& keyEnd) {
        if (head_ == nullptr) return;
        if (keyEnd < keyBegin) throw std::invalid_argument("removeKey: keyEnd < keyBegin");

        Node* current = head_;
        while (current != nullptr && current->data_ < keyBegin) {
            current = current->next_;
        }
        while (current != nullptr && !(keyEnd < current->data_)) {
            Node* next = current->next_;
            deleteNode(current);
            current = next;
        }
    }

     //dop zadanie
    void replace(const T& keyOld, const T& keyNew) {
        if (head_ == nullptr) return;

        size_t count = 0;
        Node* current = head_;
        while (current != nullptr) {
            Node* next = current->next_;
            if (isEqual(current->data_, keyOld)) {
                deleteNode(current);
                count++;
            }
            current = next;
        }
        for (size_t i = 0; i < count; i++) {
            insert(keyNew);
        }

    }

    void merge(DoubleOrderedDuplicateList& other) {
        if (this == &other || other.head_ == nullptr) {
            return;
        }

        Node* current = other.head_;
        while (current != nullptr) {
            Node* next = current->next_;

            current->prev_ = nullptr;
            current->next_ = nullptr;

            if (head_ == nullptr) {
                head_ = current;
                tail_ = current;
                size_++;
            }
            else if (current->data_ < head_->data_) {
                current->next_ = head_;
                head_->prev_ = current;
                head_ = current;
                size_++;
            }
            else {
                Node* pos = head_;
                while (pos->next_ != nullptr && !(current->data_ < pos->next_->data_)) {
                    pos = pos->next_;
                }

                current->next_ = pos->next_;
                current->prev_ = pos;

                if (pos->next_ != nullptr) {
                    pos->next_->prev_ = current;
                }
                else {
                    tail_ = current;
                }

                pos->next_ = current;
                size_++;
            }

            current = next;
        }

        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.size_ = 0;
    }


};
