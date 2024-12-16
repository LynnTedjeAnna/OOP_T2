//
// Created by Lynn Meindertsma on 12 Dec 2024.
//
#ifndef LOGIC_SIMULATOR_EXCEPTION_HPP
#define LOGIC_SIMULATOR_EXCEPTION_HPP

#include <exception>
#include <string>

class Exception : public std::exception {
public:
    Exception(const std::string& msg) : message(msg) {}

    const char* what() const noexcept override {
        return message.c_str();
    }
private:
    std::string message;
};

#endif //LOGIC_SIMULATOR_EXCEPTION_HPP
