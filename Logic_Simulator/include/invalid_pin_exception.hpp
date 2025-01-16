//
// Created by Lynn Meindertsma on 14 Jan 2025.
//

#ifndef LOGIC_SIMULATOR_INVALID_PIN_EXCEPTION_HPP
#define LOGIC_SIMULATOR_INVALID_PIN_EXCEPTION_HPP
#include "exception.hpp"

// Derived invalid_pin_exception class
class invalid_pin_exception : public Exception {
public:
    explicit invalid_pin_exception(const std::string& msg)
            : Exception(msg) {}
};

#endif //LOGIC_SIMULATOR_INVALID_PIN_EXCEPTION_HPP
