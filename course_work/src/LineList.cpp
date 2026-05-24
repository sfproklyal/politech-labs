#include "LineList.h"

#include <stdexcept>

LineList::Node::Node(int line, Node* next) : line_(line), next_(next) {}

LineList::LineList() : head_(nullptr), tail_(nullptr), size_(0) {}

LineList::LineList(const LineList& other)
    : head_(nullptr),
      tail_(nullptr),
      size_(0)
{
    Node* current = other.head_;
    while (current != nullptr) {
        insert(current->line_);
        current = current->next_;
    }
}

LineList& LineList::operator=(const LineList& other)
{
    if (this == &other) {
        return *this;
    }

    clear();
    Node* current = other.head_;
    while (current != nullptr) {
        insert(current->line_);
        current = current->next_;
    }
    return *this;
}

LineList::~LineList()
{
    clear();
}

void LineList::insert(int line)
{
    if (line <= 0) {
        throw std::invalid_argument("Line number must be positive");
    }

    if (head_ == nullptr) {
        head_ = new Node(line);
        tail_ = head_;
        size_++;
        return;
    }

    if (tail_->line_ == line) {
        return;
    }

    if (line < head_->line_) {
        head_ = new Node(line, head_);
        size_++;
        return;
    }

    Node* current = head_;
    while (current->next_ != nullptr && current->next_->line_ < line) {
        current = current->next_;
    }

    if (current->line_ == line) {
        return;
    }
    if (current->next_ != nullptr && current->next_->line_ == line) {
        return;
    }

    current->next_ = new Node(line, current->next_);
    if (current->next_->next_ == nullptr) {
        tail_ = current->next_;
    }
    size_++;
}

void LineList::clear()
{
    while (head_ != nullptr) {
        Node* temp = head_;
        head_ = head_->next_;
        delete temp;
    }
    tail_ = nullptr;
    size_ = 0;
}

bool LineList::isEmpty() const
{
    return size_ == 0;
}

size_t LineList::getSize() const
{
    return size_;
}

void LineList::print(std::ostream& out) const
{
    Node* current = head_;
    while (current != nullptr) {
        out << current->line_;
        if (current->next_ != nullptr) {
            out << ", ";
        }
        current = current->next_;
    }
}
