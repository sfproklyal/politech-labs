#include <iostream>
#include "BinarySearchTree.h"

int main() {
    BinarySearchTree<int> tree;

    std::cout << "empty nodes: " << tree.getNumberOfNodes() << '\n';
    std::cout << "empty height: " << tree.getHeight() << '\n';
    std::cout << "search 10 in empty: " << tree.searchIterative(10) << '\n';

    std::cout << "insert 10: " << tree.insert(10) << '\n';
    std::cout << "insert 5: " << tree.insert(5) << '\n';
    std::cout << "insert 15: " << tree.insert(15) << '\n';
    std::cout << "insert 3: " << tree.insert(3) << '\n';
    std::cout << "insert 7: " << tree.insert(7) << '\n';
    std::cout << "insert 12: " << tree.insert(12) << '\n';
    std::cout << "insert 18: " << tree.insert(18) << '\n';
    tree.insert(13);

    tree.remove(10);
    // std::cout << "insert duplicate 10: " << tree.insert(10) << '\n';

    std::cout << "nodes after insert: " << tree.getNumberOfNodes() << '\n';
    std::cout << "height after insert: " << tree.getHeight() << '\n';
    std::cout << "search 7: " << tree.searchIterative(7) << '\n';
    std::cout << "search 100: " << tree.searchIterative(100) << '\n';

    std::cout << "tree: ";
    tree.output(std::cout);
    std::cout << '\n';

    std::cout << "inorder: ";
    tree.inorderWalkIterative();
    std::cout << '\n';

    std::cout << "levels: ";
    tree.walkByLevels();

    std::cout << "remove leaf 3: " << tree.remove(3) << '\n';
    std::cout << "tree after remove 3: ";
    tree.output(std::cout);
    std::cout << '\n';
    std::cout << "nodes: " << tree.getNumberOfNodes() << '\n';
    std::cout << "height: " << tree.getHeight() << '\n';

    std::cout << "remove node with two children 15: " << tree.remove(15) << '\n';
    std::cout << "tree after remove 15: ";
    tree.output(std::cout);
    std::cout << '\n';
    std::cout << "nodes: " << tree.getNumberOfNodes() << '\n';
    std::cout << "height: " << tree.getHeight() << '\n';

    std::cout << "remove root 10: " << tree.remove(10) << '\n';
    std::cout << "tree after remove 10: ";
    tree.output(std::cout);
    std::cout << '\n';
    std::cout << "nodes: " << tree.getNumberOfNodes() << '\n';
    std::cout << "height: " << tree.getHeight() << '\n';

    std::cout << "remove missing 100: " << tree.remove(100) << '\n';

    std::cout << "final inorder: ";
    tree.inorderWalkIterative();
    std::cout << '\n';
    return 0;
}