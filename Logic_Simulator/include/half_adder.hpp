//
// Created by Lynn Meindertsma on 14 Dec 2024.
//
#ifndef LOGIC_SIMULATOR_HALF_ADDER_HPP
#define LOGIC_SIMULATOR_HALF_ADDER_HPP
#include "ILogicComponent.hpp"
#include "xor_gate.hpp"

class Half_adder : public ILogicComponent{
public:
    Half_adder();   // Declaration of the constructor

    // Sets the state of an input pin.
    void set_input(uint8_t pin, uint8_t value) override;

private:
    Xor_gate xor_gate;
    And_gate and_gate;
    Pin input_pin[2];
    Pin output_pin[2];
};

#endif //LOGIC_SIMULATOR_HALF_ADDER_HPP
