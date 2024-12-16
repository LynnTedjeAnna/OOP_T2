//
// Created by Lynn Meindertsma on 14 Dec 2024.
//
#ifndef LOGIC_SIMULATOR_HALF_ADDER_HPP
#define LOGIC_SIMULATOR_HALF_ADDER_HPP
#include "logic_gate.hpp"
#include "xor_gate.hpp"

class Half_adder : public logic_gate{
public:
    Half_adder();  // Constructor to initialize the state of the NOT gate.

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
    uint8_t output_value[2] = {255, 255};
    std::vector<Connection> connection;

    Xor_gate xor_gate;
    And_gate and_gate;
    Pin input_pin[2];
    Pin output_pin[2];
};

#endif //LOGIC_SIMULATOR_HALF_ADDER_HPP
