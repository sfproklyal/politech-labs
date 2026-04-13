#include <functional>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>
#include "BinarySearchTree.h"

namespace {

std::string captureOutput(const std::function<void()>& action) {
    std::ostringstream buffer;
    std::streambuf* oldBuffer = std::cout.rdbuf(buffer.rdbuf());
    action();
    std::cout.rdbuf(oldBuffer);
    return buffer.str();
}

void expect(bool condition, const std::string& message) {
    if (!condition) {
        throw std::runtime_error(message);
    }
}

void testDefaultConstructor() {
    BinarySearchTree<int> tree;

    expect(tree.getNumberOfNodes() == 0, "Default constructor: tree should be empty.");
    expect(tree.getHeight() == 0, "Default constructor: empty tree height should be 0.");
    expect(!tree.searchIterative(10), "Default constructor: search in empty tree should return false.");
    expect(captureOutput([&tree]() { tree.output(std::cout); }) == "null",
           "Default constructor: output for empty tree should be \"null\".");
    expect(captureOutput([&tree]() { tree.inorderWalk(); }).empty(),
           "Default constructor: recursive inorder traversal should print nothing.");
    expect(captureOutput([&tree]() { tree.inorderWalkIterative(); }).empty(),
           "Default constructor: iterative inorder traversal should print nothing.");
    expect(captureOutput([&tree]() { tree.walkByLevels(); }).empty(),
           "Default constructor: level-order traversal should print nothing.");
}

void testInsertSearchAndMetrics() {
    BinarySearchTree<int> tree;

    expect(tree.insert(10), "Insert should succeed for the root node.");
    expect(tree.insert(5), "Insert should succeed for the left child.");
    expect(tree.insert(15), "Insert should succeed for the right child.");
    expect(tree.insert(3), "Insert should succeed for the left-left child.");
    expect(tree.insert(7), "Insert should succeed for the left-right child.");
    expect(tree.insert(12), "Insert should succeed for the right-left child.");
    expect(tree.insert(18), "Insert should succeed for the right-right child.");
    expect(!tree.insert(10), "Insert should reject duplicate keys.");

    expect(tree.searchIterative(10), "Search should find the root key.");
    expect(tree.searchIterative(3), "Search should find a leaf in the left subtree.");
    expect(tree.searchIterative(18), "Search should find a leaf in the right subtree.");
    expect(!tree.searchIterative(100), "Search should return false for a missing key.");

    expect(tree.getNumberOfNodes() == 7, "Tree should contain 7 unique nodes.");
    expect(tree.getHeight() == 3, "Balanced sample tree should have height 3.");
    expect(captureOutput([&tree]() { tree.output(std::cout); }) == "10(5(3, 7), 15(12, 18))",
           "Structured output does not match the expected tree shape.");
}

void testTraversals() {
    BinarySearchTree<int> tree;

    for (int value : {10, 5, 15, 3, 7, 12, 18}) {
        expect(tree.insert(value), "Setup for traversal tests failed.");
    }

    expect(captureOutput([&tree]() { tree.inorderWalk(); }) == "35710121518",
           "Recursive inorder traversal printed an unexpected sequence.");
    expect(captureOutput([&tree]() { tree.inorderWalkIterative(); }) == "3 5 7 10 12 15 18 ",
           "Iterative inorder traversal printed an unexpected sequence.");
    expect(captureOutput([&tree]() { tree.walkByLevels(); }) == "10 5 15 3 7 12 18 \n",
           "Level-order traversal printed an unexpected sequence.");
}

void testMoveConstructor() {
    BinarySearchTree<int> source;
    for (int value : {10, 5, 15}) {
        expect(source.insert(value), "Setup for move constructor test failed.");
    }

    BinarySearchTree<int> moved(std::move(source));

    expect(moved.getNumberOfNodes() == 3, "Move constructor should transfer all nodes.");
    expect(moved.getHeight() == 2, "Moved tree should preserve its height.");
    expect(moved.searchIterative(5), "Moved tree should preserve searchable keys.");
    expect(source.getNumberOfNodes() == 0, "Moved-from tree should become empty.");
    expect(!source.searchIterative(10), "Moved-from tree should no longer contain old keys.");
}

void testMoveAssignment() {
    BinarySearchTree<int> source;
    for (int value : {8, 4, 10}) {
        expect(source.insert(value), "Setup for move assignment source failed.");
    }

    BinarySearchTree<int> destination;
    expect(destination.insert(100), "Setup for move assignment destination failed.");

    destination = std::move(source);

    expect(destination.getNumberOfNodes() == 3, "Move assignment should replace destination contents.");
    expect(destination.getHeight() == 2, "Move-assigned tree should preserve source height.");
    expect(destination.searchIterative(4), "Move-assigned tree should preserve source keys.");
    expect(!destination.searchIterative(100), "Old destination contents should be cleared on move assignment.");
    expect(source.getNumberOfNodes() == 0, "Moved-from source should become empty after move assignment.");
}

} // namespace

int main() {
    static_assert(!std::is_copy_constructible_v<BinarySearchTree<int>>,
                  "BinarySearchTree should not be copy constructible.");
    static_assert(!std::is_copy_assignable_v<BinarySearchTree<int>>,
                  "BinarySearchTree should not be copy assignable.");

    const std::pair<const char*, void(*)()> tests[] = {
        {"default constructor", testDefaultConstructor},
        {"insert/search/metrics", testInsertSearchAndMetrics},
        {"traversals", testTraversals},
        {"move constructor", testMoveConstructor},
        {"move assignment", testMoveAssignment},
    };
    const int testCount = static_cast<int>(sizeof(tests) / sizeof(tests[0]));

    int passed = 0;
    for (int i = 0; i < testCount; ++i) {
        const char* name = tests[i].first;
        void (*test)() = tests[i].second;

        try {
            test();
            ++passed;
            std::cout << "[PASS] " << name << '\n';
        } catch (const std::exception& ex) {
            std::cout << "[FAIL] " << name << ": " << ex.what() << '\n';
            return 1;
        }
    }

    std::cout << "\nAll tests passed: " << passed << " / " << testCount << '\n';
    return 0;
}
