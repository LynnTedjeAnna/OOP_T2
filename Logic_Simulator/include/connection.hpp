//
// Created by Lynn Meindertsma on 10 Dec 2024.
//

#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include <cstdint>

// Forward declaration of ILogicComponent
class ILogicComponent;

class Connection {
public:
    // Constructor for easier connection creation
    Connection(uint8_t output, ILogicComponent* target, uint8_t input);

    uint8_t output_pin;
    ILogicComponent* target_component;
    uint8_t input_pin;
};

#endif // CONNECTION_HPP