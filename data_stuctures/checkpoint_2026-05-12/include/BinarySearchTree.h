#include <iostream>

class BSTRee {
private:
    struct Node {
        int key_;
        Node* left_;
        Node* right_;
        Node* p_;
        
        Node(int key) : key_(key), left_(nullptr), right_(nullptr), p_(nullptr) {}
    }



};