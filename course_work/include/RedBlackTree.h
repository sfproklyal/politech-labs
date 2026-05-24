#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include <iostream>
#include <string>

#include "LineList.h"

class RedBlackTree
{
public:
    RedBlackTree();
    RedBlackTree(const RedBlackTree&) = delete;
    RedBlackTree& operator=(const RedBlackTree&) = delete;
    ~RedBlackTree();

    bool insert(const std::string& key, int line);
    const LineList* search(const std::string& key) const;
    bool remove(const std::string& key);
    bool isEmpty() const;
    bool isValid() const;
    void print(std::ostream& out) const;
    void printTree(std::ostream& out) const;

private:
    enum Color {
        COLOR_RED,
        COLOR_BLACK
    };

    struct Node {
        std::string key_;
        LineList lines_;
        Color color_;
        Node* left_;
        Node* right_;
        Node* parent_;

        Node(const std::string& key, int line, Node* nil);
    };

    Node* root_;
    Node* nil_;

    void leftRotate(Node* node);
    void rightRotate(Node* node);
    void fixInsert(Node* node);
    void transplant(Node* oldNode, Node* newNode);
    void fixRemove(Node* node);

    Node* searchNode(const std::string& key) const;
    Node* minimum(Node* node) const;

    bool isBinarySearchTree(Node* node,
                            const std::string* minKey,
                            const std::string* maxKey) const;
    bool hasCorrectParents(Node* node, Node* parent) const;
    bool hasNoRedRedViolation(Node* node) const;
    int getBlackHeight(Node* node) const;

    void clear(Node* node);
    void print(Node* node, std::ostream& out) const;
    void printTree(Node* node, std::ostream& out) const;
};

#endif
