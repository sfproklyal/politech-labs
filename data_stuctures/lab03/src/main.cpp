#include <cstring>
#include <iostream>
#include <stdexcept>
#include "StackArray.h"
#include "checkBalanceBrackets.h"

void printResult(const char* testName, bool passed) {
    std::cout << testName << ": " << (passed ? "PASSED" : "FAILED") << '\n';
}

void updateOverall(bool& allPassed, const char* testName, bool passed) {
    printResult(testName, passed);
    allPassed = allPassed && passed;
}

int main() {
    bool allPassed = true;

    {
        StackArray<int> stack(3);
        updateOverall(allPassed, "stack empty after construction", stack.isEmpty());
    }

    {
        StackArray<int> stack(3);
        stack.push(10);
        stack.push(20);
        stack.push(30);

        bool passed = !stack.isEmpty();
        passed = passed && (stack.pop() == 30);
        passed = passed && (stack.pop() == 20);
        passed = passed && (stack.pop() == 10);
        passed = passed && stack.isEmpty();

        updateOverall(allPassed, "stack push/pop order", passed);
    }

    {
        StackArray<int> stack(1);
        bool passed = false;

        stack.push(42);
        try {
            stack.push(99);
        } catch (const StackOverflow&) {
            passed = true;
        } catch (...) {
            passed = false;
        }

        updateOverall(allPassed, "stack overflow throws", passed);
    }

    {
        StackArray<int> stack(1);
        bool passed = false;

        try {
            stack.pop();
        } catch (const StackUnderflow&) {
            passed = true;
        } catch (...) {
            passed = false;
        }

        updateOverall(allPassed, "stack underflow throws", passed);
    }

    {
        bool passed = false;

        try {
            StackArray<int> stack(0);
        } catch (const WrongStackSize&) {
            passed = true;
        } catch (...) {
            passed = false;
        }

        updateOverall(allPassed, "stack wrong size throws", passed);
    }

    {
        StackArray<int> source(3);
        source.push(1);
        source.push(2);

        StackArray<int> copy(1);
        copy = source;
        source.pop();
        source.push(99);

        bool passed = (copy.pop() == 2);
        passed = passed && (copy.pop() == 1);
        passed = passed && copy.isEmpty();

        updateOverall(allPassed, "stack copy assignment", passed);
    }

    {
        StackArray<int> source(3);
        source.push(4);
        source.push(5);

        StackArray<int> copy(source);
        source.pop();
        source.push(9);

        bool passed = (copy.pop() == 5);
        passed = passed && (copy.pop() == 4);
        passed = passed && copy.isEmpty();

        updateOverall(allPassed, "stack copy constructor", passed);
    }

    {
        StackArray<int> source(3);
        source.push(7);
        source.push(8);

        StackArray<int> moved(std::move(source));

        bool passed = (moved.pop() == 8);
        passed = passed && (moved.pop() == 7);
        passed = passed && moved.isEmpty();
        passed = passed && source.isEmpty();

        updateOverall(allPassed, "stack move constructor", passed);
    }

    {
        StackArray<int> source(3);
        source.push(11);
        source.push(12);

        StackArray<int> moved(1);
        moved = std::move(source);

        bool passed = (moved.pop() == 12);
        passed = passed && (moved.pop() == 11);
        passed = passed && moved.isEmpty();
        passed = passed && source.isEmpty();

        updateOverall(allPassed, "stack move assignment", passed);
    }

    {
        StackOverflow ex;
        bool passed = std::strcmp(ex.what(), "Stack overflow error\n") == 0;
        updateOverall(allPassed, "stack overflow message", passed);
    }

    {
        StackUnderflow ex;
        bool passed = std::strcmp(ex.what(), "Stack underflow error\n") == 0;
        updateOverall(allPassed, "stack underflow message", passed);
    }

    {
        WrongStackSize ex;
        bool passed = std::strcmp(ex.what(), "Wrong stack size error\n") == 0;
        updateOverall(allPassed, "wrong size message", passed);
    }

    {
        bool passed = checkBalanceBrackets("([]{})", 10);
        updateOverall(allPassed, "brackets balanced simple", passed);
    }

    {
        bool passed = checkBalanceBrackets("a + (b * [c - {d}])", 10);
        updateOverall(allPassed, "brackets ignore other chars", passed);
    }

    {
        bool passed = !checkBalanceBrackets("([)]", 10);
        updateOverall(allPassed, "brackets wrong nesting", passed);
    }

    {
        bool passed = !checkBalanceBrackets("(()", 10);
        updateOverall(allPassed, "brackets missing closing", passed);
    }

    {
        bool passed = !checkBalanceBrackets("())", 10);
        updateOverall(allPassed, "brackets extra closing", passed);
    }

    {
        bool passed = !checkBalanceBrackets("(((())))", 3);
        updateOverall(allPassed, "brackets depth overflow", passed);
    }

    {
        bool passed = false;

        try {
            checkBalanceBrackets(nullptr, 5);
        } catch (const std::invalid_argument&) {
            passed = true;
        } catch (...) {
            passed = false;
        }

        updateOverall(allPassed, "brackets null input throws", passed);
    }

    {
        bool passed = false;

        try {
            checkBalanceBrackets("()", 0);
        } catch (const std::invalid_argument&) {
            passed = true;
        } catch (...) {
            passed = false;
        }

        updateOverall(allPassed, "brackets invalid depth throws", passed);
    }

    std::cout << (allPassed ? "ALL TESTS PASSED" : "SOME TESTS FAILED") << '\n';
    return allPassed ? 0 : 1;
}
