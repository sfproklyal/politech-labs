#ifndef LINE_LIST_H
#define LINE_LIST_H

#include <cstddef>
#include <iostream>
#include <string>

class LineList
{
public:
    LineList();
    LineList(const LineList& other);
    LineList& operator=(const LineList& other);
    ~LineList();

    void insert(int line);
    void clear();
    bool isEmpty() const;
    size_t getSize() const;
    std::string toString() const;
    void print(std::ostream& out) const;

private:
    struct Node {
        int line_;
        Node* next_;

        Node(int line, Node* next = nullptr);
    };

    Node* head_;
    Node* tail_;
    size_t size_;
};

#endif
