#pragma once
#include <string>
#include <stdexcept>


class StackOverflow : public std::overflow_error {
public:
    StackOverflow(const std::string& message = "Stack overflow error\n") : std::overflow_error(message) {};
};

class StackUnderflow : public std::underflow_error {
public:
    StackUnderflow(const std::string& message = "Stack underflow error\n") : std::underflow_error(message) {};
};

class WrongStackSize : public std::invalid_argument {
public:
    WrongStackSize(const std::string& message = "Wrong stack size error\n") : std::invalid_argument(message) {};
};





