//
// Created by Lynn Meindertsma on 14 Dec 2024.
//
#ifndef LOGIC_SIMULATOR_HALF_ADDER_HPP
#define LOGIC_SIMULATOR_HALF_ADDER_HPP
#include "base_logic.hpp"
#include "xor_gate.hpp"

class Half_adder : public base_logic{
public:
    Half_adder();   // Declaration of the constructor

    // Sets the state of an input pin.
    void SetInput(uint8_t pin, bool value) override;

private:
    Xor_gate xor_gate;
    And_gate and_gate;
    Pin input_pin[2];
    Pin output_pin[2];
};

#endif //LOGIC_SIMULATOR_HALF_ADDER_HPP
