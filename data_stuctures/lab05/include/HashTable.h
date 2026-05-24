#pragma once
#include <string>
#include <cstddef>
#include <iostream>
#include <stdexcept>



class HashTable {
private:
    struct Node {
        double key_;
        std::string data_;
        Node* next_;

        Node(double key, const std::string& data, Node* next = nullptr)
            : key_(key), data_(data), next_(next) {}
    };

    int size_;
    Node** table_;
    int number_;

    int getHash(double key) const {
        if (key < 0) { 
            throw std::invalid_argument("Key must be non-negative");
        }

        int intKey = static_cast<int>(key);
        int index = intKey % size_;

        return index;
    }

public:
    HashTable(int size = 11) 
        : size_(size), table_(nullptr), number_(0) 
    {
        if (size_ <= 0){
            throw std::invalid_argument("Table size must be non-negative");
        }

        table_ = new Node*[size_];
        for (int i = 0; i < size_; i++) {
            table_[i] = nullptr;
        }

    }

    ~HashTable() {
        for (int i = 0; i < size_; i++) {
            Node* current = table_[i];

            while (current != nullptr) {
                Node* temp = current;
                current = current->next_;
                delete temp;
            }
        }
        delete[] table_;
    }

    HashTable(const HashTable&) = delete;
    HashTable(HashTable&&) = delete;
    HashTable& operator=(const HashTable&) = delete;
    HashTable& operator=(HashTable&&) = delete;



    bool insert(double key, const std::string& data) {
        int index = getHash(key);
        
        Node* current = table_[index];
        while (current != nullptr) {
            if (current->key_ == key) {
                return false;
            }
            current = current->next_;
        }
        
        Node* newNode = new Node(key, data, table_[index]);
        table_[index] = newNode;
        ++number_;
        return true;
    }

    bool find(double key, std::string& data) const  {
        int index = getHash(key);

        Node* current = table_[index];
        while (current != nullptr) {
            if (current->key_ == key) {
                data = current->data_;
                return true;
            }
            current = current->next_;
        }
        return false;
    }

    bool remove(double key) {
        int index = getHash(key);
        
        Node* current = table_[index];
        Node* previous = nullptr;

        while (current != nullptr) {
            if (current->key_ == key) {
                if (previous == nullptr) {
                    table_[index] = current->next_;
                }
                else {
                    previous->next_ = current->next_;
                }

                delete current;
                --number_;
                return true;

            }

            previous = current;
            current = current->next_;

        }
        
        return false;
    };

    void print() const {
        for (int i = 0; i < size_; ++i) {
            std::cout << "[" << i << "]: "; 

            Node* current = table_[i];
            if (current == nullptr) {
                std::cout << "empty";
            }

            while (current != nullptr) {
                std::cout << "(" << current->key_ << ", " << current->data_ << ")";
                
                if (current->next_ != nullptr) {
                    std::cout << " -> ";
                }

                current = current->next_;
            }
            std::cout << "\n";
        }
    }

    int longestChain() const {
        int maxLength = 0;

        for (int i = 0; i < size_; i++) {

            int currentLength = 0;
            Node* current = table_[i];

            while (current != nullptr) {
                ++currentLength;
                current = current->next_;
            }

            if (currentLength > maxLength) {
                maxLength = currentLength;
            }
        }
        
        return maxLength;
    }

    

}; 
