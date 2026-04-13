#ifndef _BINARY_SEARCH_TREE_H
#define _BINARY_SEARCH_TREE_H

#include <algorithm>
#include <iostream>
#include <ostream>
#include <stack>
#include <queue>

template <typename T>
class BinarySearchTree
{
private:
    struct Node {
        T key_;
        Node *left_;
        Node *right_;
        Node *p_;

        Node(T key, Node *left = nullptr, Node *right = nullptr, Node *p = nullptr) : 
            key_(key), left_(left), right_(right), p_(p) {};

    };

    Node* root_;

    void clear(Node* node) {
        if (node == nullptr) return;

        clear(node->left_);
        clear(node->right_);
        delete node;
    }

    Node* searchNodeIterative(const T& key) const {
        Node* current = root_;

        while (current != nullptr) {
            if (key == current->key_) return current;
            else if (key < current->key_) current = current->left_;
            else current = current->right_;
        }
        return nullptr;
    }

    Node* minimum(Node* node) const {
        if (node == nullptr) return nullptr;
        while (node->left_ != nullptr) node = node->left_;
        return node; 
    }

    void output(std::ostream& out, Node* root) const {
        if (root == nullptr) {
            out << "null";
            return;
        }

        out << root->key_;

        if (root->left_ != nullptr || root->right_ != nullptr) { // если есть хотя бы один ребёнок
            out << "(";
            output(out, root->left_);
            out << ", ";
            output(out, root->right_);
            out << ")";
        }
    }

    int getNumberOfNodes(const Node* node) const {
        if (node == nullptr) return 0;
        return 1 + getNumberOfNodes(node->left_) + getNumberOfNodes(node->right_);
    }

    int getHeight(const Node* node) const {
        if (node == nullptr) return 0;
        return 1 + std::max(getHeight(node->left_), getHeight(node->right_));
    }

    void inorderWalk(Node* node) const {
        if (node == nullptr) return;
        
        inorderWalk(node->left_);
        std::cout << node->key_ << " ";
        inorderWalk(node->right_);
    }


public:
    BinarySearchTree() : root_(nullptr) {};
    BinarySearchTree(const BinarySearchTree& other) = delete;
    BinarySearchTree(BinarySearchTree&& other) noexcept : root_(other.root_) { 
        other.root_ = nullptr;
    }
    ~BinarySearchTree() {
        clear(root_);
    }
    
    BinarySearchTree& operator=(const BinarySearchTree& other) = delete;
    BinarySearchTree& operator=(BinarySearchTree&& other) noexcept {
        if (this != &other) {
            clear(root_);
            root_ = other.root_;
            other.root_ = nullptr;
        }
        return *this;
    }


    // public methods
    bool searchIterative(const T& key) const {
        return searchNodeIterative(key) != nullptr;
    }

    bool insert(const T& key) {
        Node* parent = nullptr;
        Node* current = root_;

        while (current != nullptr) {
            parent = current;

            if (key == current->key_) return false;
            else if (key < current->key_) current = current->left_;
            else current = current->right_;
        }

        Node* newNode = new Node(key, nullptr, nullptr, parent);

        if (parent == nullptr) root_ = newNode;
        else if (key < parent->key_) parent->left_ = newNode;
        else parent->right_ = newNode;
        
        return true;
    }

    void output(std::ostream& out) const {
        output(out, root_);
    }
    
    int getNumberOfNodes() const {
        return getNumberOfNodes(root_);
    }

    int getHeight() const {
        return getHeight(root_);
    }

    void inorderWalkIterative() const{
        std::stack<Node*> st;
        Node* current = root_;
        while (current != nullptr || !st.empty()) {
            while (current != nullptr) {
                st.push(current);
                current = current->left_;
            }

            current = st.top();
            st.pop();

            std::cout << current->key_ << " ";
            current = current->right_;
        }
        
    }

    void inorderWalk() const { // рекурсивный
        inorderWalk(root_);
    }

    void walkByLevels() const {
        if (root_ == nullptr) return;

        std::queue<Node*> q;
        q.push(root_);
        while (!q.empty()) {
            Node* current = q.front();
            q.pop();

            std::cout << current->key_ << " ";
            if (current->left_ != nullptr) q.push(current->left_);
            if (current->right_ != nullptr) q.push(current->right_);
        }
        std::cout << '\n';
    }


};



#endif
