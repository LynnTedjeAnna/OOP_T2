//
// Created by Lynn Meindertsma on 14 Dec 2024.
//
#ifndef LOGIC_SIMULATOR_PIN_HPP
#define LOGIC_SIMULATOR_PIN_HPP
#include "logic_gate.hpp"

class Pin : public logic_gate {
public:
    Pin() = default;  // Constructor to initialize the state of the NOT gate.

    // Returns the state of an input pin.
    uint8_t get_input(uint8_t pin) override;

    // Returns the state of an output pin.
    uint8_t get_output(uint8_t pin) override;

    // Connects an output of this component to an input of another component.
    void connect_output(uint8_t output_pin, logic_gate* other, uint8_t input_pin) override;

    // Sets the state of an input pin.
    void set_input(uint8_t pin, uint8_t value) override;

private:
    uint8_t input_value = 255;
    std::vector<Connection> connection;
};

#endif //LOGIC_SIMULATOR_PIN_HPP
