#include "RedBlackTree.h"

#include <stdexcept>

RedBlackTree::Node::Node(const std::string& key, int line, Node* nil)
    : key_(key),
      lines_(),
      color_(COLOR_RED),
      left_(nil),
      right_(nil),
      parent_(nil)
{
    if (line > 0) {
        lines_.insert(line);
    }
}

RedBlackTree::RedBlackTree()
    : root_(nullptr), nil_(new Node("", 0, nullptr))
{
    nil_->color_ = COLOR_BLACK;
    nil_->left_ = nil_;
    nil_->right_ = nil_;
    nil_->parent_ = nil_;
    root_ = nil_;
}

RedBlackTree::~RedBlackTree()
{
    clear(root_);
    delete nil_;
}

void RedBlackTree::leftRotate(Node* node)
{
    // Rotation keeps the binary-search order and changes only local links.
    Node* right = node->right_;
    node->right_ = right->left_;

    if (right->left_ != nil_) {
        right->left_->parent_ = node;
    }

    right->parent_ = node->parent_;

    if (node->parent_ == nil_) {
        root_ = right;
    }
    else if (node == node->parent_->left_) {
        node->parent_->left_ = right;
    }
    else {
        node->parent_->right_ = right;
    }

    right->left_ = node;
    node->parent_ = right;
}

void RedBlackTree::rightRotate(Node* node)
{
    // Rotation keeps the binary-search order and changes only local links.
    Node* left = node->left_;
    node->left_ = left->right_;

    if (left->right_ != nil_) {
        left->right_->parent_ = node;
    }

    left->parent_ = node->parent_;

    if (node->parent_ == nil_) {
        root_ = left;
    }
    else if (node == node->parent_->right_) {
        node->parent_->right_ = left;
    }
    else {
        node->parent_->left_ = left;
    }

    left->right_ = node;
    node->parent_ = left;
}

void RedBlackTree::fixInsert(Node* node)
{
    // Restore red-black properties after adding a red node.
    while (node->parent_->color_ == COLOR_RED) {
        if (node->parent_ == node->parent_->parent_->left_) {
            Node* uncle = node->parent_->parent_->right_;

            if (uncle->color_ == COLOR_RED) {
                node->parent_->color_ = COLOR_BLACK;
                uncle->color_ = COLOR_BLACK;
                node->parent_->parent_->color_ = COLOR_RED;
                node = node->parent_->parent_;
            }
            else {
                if (node == node->parent_->right_) {
                    node = node->parent_;
                    leftRotate(node);
                }

                node->parent_->color_ = COLOR_BLACK;
                node->parent_->parent_->color_ = COLOR_RED;
                rightRotate(node->parent_->parent_);
            }
        }
        else {
            Node* uncle = node->parent_->parent_->left_;

            if (uncle->color_ == COLOR_RED) {
                node->parent_->color_ = COLOR_BLACK;
                uncle->color_ = COLOR_BLACK;
                node->parent_->parent_->color_ = COLOR_RED;
                node = node->parent_->parent_;
            }
            else {
                if (node == node->parent_->left_) {
                    node = node->parent_;
                    rightRotate(node);
                }

                node->parent_->color_ = COLOR_BLACK;
                node->parent_->parent_->color_ = COLOR_RED;
                leftRotate(node->parent_->parent_);
            }
        }
    }

    root_->color_ = COLOR_BLACK;
}

void RedBlackTree::transplant(Node* oldNode, Node* newNode)
{
    if (oldNode->parent_ == nil_) {
        root_ = newNode;
    }
    else if (oldNode == oldNode->parent_->left_) {
        oldNode->parent_->left_ = newNode;
    }
    else {
        oldNode->parent_->right_ = newNode;
    }

    newNode->parent_ = oldNode->parent_;
}

void RedBlackTree::fixRemove(Node* node)
{
    // Restore black height after deleting a black node.
    while (node != root_ && node->color_ == COLOR_BLACK) {
        if (node == node->parent_->left_) {
            Node* brother = node->parent_->right_;

            if (brother->color_ == COLOR_RED) {
                brother->color_ = COLOR_BLACK;
                node->parent_->color_ = COLOR_RED;
                leftRotate(node->parent_);
                brother = node->parent_->right_;
            }

            if (brother->left_->color_ == COLOR_BLACK &&
                brother->right_->color_ == COLOR_BLACK) {
                brother->color_ = COLOR_RED;
                node = node->parent_;
            }
            else {
                if (brother->right_->color_ == COLOR_BLACK) {
                    brother->left_->color_ = COLOR_BLACK;
                    brother->color_ = COLOR_RED;
                    rightRotate(brother);
                    brother = node->parent_->right_;
                }

                brother->color_ = node->parent_->color_;
                node->parent_->color_ = COLOR_BLACK;
                brother->right_->color_ = COLOR_BLACK;
                leftRotate(node->parent_);
                node = root_;
            }
        }
        else {
            Node* brother = node->parent_->left_;

            if (brother->color_ == COLOR_RED) {
                brother->color_ = COLOR_BLACK;
                node->parent_->color_ = COLOR_RED;
                rightRotate(node->parent_);
                brother = node->parent_->left_;
            }

            if (brother->right_->color_ == COLOR_BLACK &&
                brother->left_->color_ == COLOR_BLACK) {
                brother->color_ = COLOR_RED;
                node = node->parent_;
            }
            else {
                if (brother->left_->color_ == COLOR_BLACK) {
                    brother->right_->color_ = COLOR_BLACK;
                    brother->color_ = COLOR_RED;
                    leftRotate(brother);
                    brother = node->parent_->left_;
                }

                brother->color_ = node->parent_->color_;
                node->parent_->color_ = COLOR_BLACK;
                brother->left_->color_ = COLOR_BLACK;
                rightRotate(node->parent_);
                node = root_;
            }
        }
    }

    node->color_ = COLOR_BLACK;
}

RedBlackTree::Node* RedBlackTree::searchNode(const std::string& key) const
{
    Node* current = root_;
    while (current != nil_) {
        if (key == current->key_) {
            return current;
        }
        if (key < current->key_) {
            current = current->left_;
        }
        else {
            current = current->right_;
        }
    }
    return nil_;
}

RedBlackTree::Node* RedBlackTree::minimum(Node* node) const
{
    while (node->left_ != nil_) {
        node = node->left_;
    }
    return node;
}

void RedBlackTree::clear(Node* node)
{
    if (node == nil_) {
        return;
    }

    clear(node->left_);
    clear(node->right_);
    delete node;
}

void RedBlackTree::print(Node* node, std::ostream& out) const
{
    if (node == nil_) {
        return;
    }

    print(node->left_, out);
    out << node->key_ << " : ";
    node->lines_.print(out);
    out << '\n';
    print(node->right_, out);
}

void RedBlackTree::appendToString(Node* node, std::string& result) const
{
    if (node == nil_) {
        return;
    }

    appendToString(node->left_, result);
    result += node->key_;
    result += " : ";
    result += node->lines_.toString();
    result += '\n';
    appendToString(node->right_, result);
}

void RedBlackTree::printTree(Node* node, std::ostream& out) const
{
    if (node == nil_) {
        out << "null";
        return;
    }

    out << node->key_ << "(";
    out << (node->color_ == COLOR_RED ? "R" : "B");
    out << ")";
    if (node->left_ != nil_ || node->right_ != nil_) {
        out << "(";
        printTree(node->left_, out);
        out << ", ";
        printTree(node->right_, out);
        out << ")";
    }
}

bool RedBlackTree::insert(const std::string& key, int line)
{
    if (key.empty()) {
        throw std::invalid_argument("Key is empty");
    }
    if (line <= 0) {
        throw std::invalid_argument("Line number must be positive");
    }

    Node* parent = nil_;
    Node* current = root_;

    while (current != nil_) {
        parent = current;

        if (key == current->key_) {
            current->lines_.insert(line);
            return false;
        }

        if (key < current->key_) {
            current = current->left_;
        }
        else {
            current = current->right_;
        }
    }

    Node* newNode = new Node(key, line, nil_);
    newNode->parent_ = parent;

    if (parent == nil_) {
        root_ = newNode;
    }
    else if (key < parent->key_) {
        parent->left_ = newNode;
    }
    else {
        parent->right_ = newNode;
    }

    fixInsert(newNode);
    return true;
}

const LineList* RedBlackTree::search(const std::string& key) const
{
    Node* node = searchNode(key);
    if (node == nil_) {
        return nullptr;
    }
    return &node->lines_;
}

bool RedBlackTree::remove(const std::string& key)
{
    Node* node = searchNode(key);
    if (node == nil_) {
        return false;
    }

    Node* replacement = node;
    Color oldColor = replacement->color_;
    Node* child = nil_;

    if (node->left_ == nil_) {
        child = node->right_;
        transplant(node, node->right_);
    }
    else if (node->right_ == nil_) {
        child = node->left_;
        transplant(node, node->left_);
    }
    else {
        replacement = minimum(node->right_);
        oldColor = replacement->color_;
        child = replacement->right_;

        if (replacement->parent_ == node) {
            child->parent_ = replacement;
        }
        else {
            transplant(replacement, replacement->right_);
            replacement->right_ = node->right_;
            replacement->right_->parent_ = replacement;
        }

        transplant(node, replacement);
        replacement->left_ = node->left_;
        replacement->left_->parent_ = replacement;
        replacement->color_ = node->color_;
    }

    delete node;

    if (oldColor == COLOR_BLACK) {
        fixRemove(child);
    }

    return true;
}

bool RedBlackTree::isEmpty() const
{
    return root_ == nil_;
}

bool RedBlackTree::isValid() const
{
    if (nil_->color_ != COLOR_BLACK) {
        return false;
    }
    if (root_ == nil_) {
        return true;
    }
    if (root_->color_ != COLOR_BLACK || root_->parent_ != nil_) {
        return false;
    }
    if (!isBinarySearchTree(root_, nullptr, nullptr)) {
        return false;
    }
    if (!hasCorrectParents(root_, nil_)) {
        return false;
    }
    if (!hasNoRedRedViolation(root_)) {
        return false;
    }
    return getBlackHeight(root_) != -1;
}

std::string RedBlackTree::toString() const
{
    std::string result;
    appendToString(root_, result);
    return result;
}

void RedBlackTree::print(std::ostream& out) const
{
    out << toString();
}

void RedBlackTree::printTree(std::ostream& out) const
{
    printTree(root_, out);
}

bool RedBlackTree::isBinarySearchTree(Node* node,
                                      const std::string* minKey,
                                      const std::string* maxKey) const
{
    if (node == nil_) {
        return true;
    }
    if (minKey != nullptr && node->key_ <= *minKey) {
        return false;
    }
    if (maxKey != nullptr && node->key_ >= *maxKey) {
        return false;
    }
    return isBinarySearchTree(node->left_, minKey, &node->key_) &&
           isBinarySearchTree(node->right_, &node->key_, maxKey);
}

bool RedBlackTree::hasCorrectParents(Node* node, Node* parent) const
{
    if (node == nil_) {
        return true;
    }
    if (node->parent_ != parent) {
        return false;
    }
    return hasCorrectParents(node->left_, node) &&
           hasCorrectParents(node->right_, node);
}

bool RedBlackTree::hasNoRedRedViolation(Node* node) const
{
    if (node == nil_) {
        return true;
    }
    if (node->color_ == COLOR_RED) {
        if (node->left_->color_ == COLOR_RED ||
            node->right_->color_ == COLOR_RED) {
            return false;
        }
    }
    return hasNoRedRedViolation(node->left_) &&
           hasNoRedRedViolation(node->right_);
}

int RedBlackTree::getBlackHeight(Node* node) const
{
    if (node == nil_) {
        return 1;
    }

    int leftHeight = getBlackHeight(node->left_);
    int rightHeight = getBlackHeight(node->right_);

    if (leftHeight == -1 || rightHeight == -1 || leftHeight != rightHeight) {
        return -1;
    }

    if (node->color_ == COLOR_BLACK) {
        return leftHeight + 1;
    }
    return leftHeight;
}
