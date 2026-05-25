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

class QueueOverflow : public std::overflow_error {
public:
    QueueOverflow(const std::string& message = "Queue overflow error\n") : std::overflow_error(message) {};
};

class QueueUnderflow : public std::underflow_error {
public:
    QueueUnderflow(const std::string& message = "Queue underflow error\n") : std::underflow_error(message) {};
};

class WrongQueueSize : public std::invalid_argument {
public:
    WrongQueueSize(const std::string& message = "Wrong queue size error\n") : std::invalid_argument(message) {};
};

