//
// Created by Lynn Meindertsma on 09 Dec 2024.
//
#ifndef LOGIC_SIMULATOR_LOGIC_GATE_HPP
#define LOGIC_SIMULATOR_LOGIC_GATE_HPP
#include <vector>
#include "connection.hpp"

class logic_gate {
public:
    virtual ~logic_gate() = default;

    // Returns the state of an input pin.
    virtual uint8_t get_input(uint8_t pin) = 0;

    // Returns the state of an output pin.
    virtual uint8_t get_output(uint8_t pin) = 0;

    // Sets the state of an input pin.
    virtual void set_input(uint8_t pin, uint8_t value) = 0;

    // Connects an output of this component to an input of another component.
    virtual void connect_output(uint8_t output_pin, logic_gate* other, uint8_t input_pin) = 0;

    // This will store the connections for each logic gate
    std::vector<Connection> connections;
};

#endif //LOGIC_SIMULATOR_LOGIC_GATE_HPP
