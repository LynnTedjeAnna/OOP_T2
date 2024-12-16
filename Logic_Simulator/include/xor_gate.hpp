//
// Created by Lynn Meindertsma on 14 Dec 2024.
//
#ifndef LOGIC_SIMULATOR_XOR_GATE_HPP
#define LOGIC_SIMULATOR_XOR_GATE_HPP
#include "logic_gate.hpp"
#include "not_gate.hpp"
#include "or_gate.hpp"
#include "and_gate.hpp"
#include "Pin.hpp"

class Xor_gate : public logic_gate {
public:
    Xor_gate();  // Constructor to initialize the state of the NOT gate.

    // Returns the state of an input pin.
    uint8_t get_input(uint8_t pin) override;

    // Returns the state of an output pin.
    uint8_t get_output(uint8_t pin) override;

    // Connects an output of this component to an input of another component.
    void connect_output(uint8_t output_pin, logic_gate* other, uint8_t input_pin) override;

    // Sets the state of an input pin.
    void set_input(uint8_t pin, uint8_t value) override;

private:
    uint8_t input_value[2] = {255, 255 };
    uint8_t output_value = 0;
    std::vector<Connection> connection;

    Not_gate not1;
    Not_gate not2;
    And_gate and1;
    And_gate and2;
    Or_gate or_gate;
    Pin pin[2];
};


#endif //LOGIC_SIMULATOR_XOR_GATE_HPP
