//
// Created by Lynn Meindertsma on 10 Dec 2024.
//

#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include <cstdint>

// Forward declaration of logic_gate
class logic_gate;

class Connection {
public:
    // Constructor for easier connection creation
    Connection(uint8_t output, logic_gate* target, uint8_t input);

    uint8_t output_pin;
    logic_gate* target_component;
    uint8_t input_pin;
};

#endif // CONNECTION_HPP