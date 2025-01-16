//
// Created by Lynn Meindertsma on 14 Jan 2025.
//

#ifndef LOGIC_SIMULATOR_CONNECTION_ALREADY_CREATED_HPP
#define LOGIC_SIMULATOR_CONNECTION_ALREADY_CREATED_HPP
#include "exception.hpp"

// Derived connection_already_created class
class connection_already_created : public Exception {
public:
    explicit connection_already_created(const std::string& msg)
            : Exception(msg) {}
};


#endif //LOGIC_SIMULATOR_CONNECTION_ALREADY_CREATED_HPP
