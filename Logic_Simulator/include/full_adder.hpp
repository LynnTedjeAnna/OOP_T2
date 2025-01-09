//
// Created by Lynn Meindertsma on 14 Dec 2024.
//
#ifndef LOGIC_SIMULATOR_FULL_ADDER_HPP
#define LOGIC_SIMULATOR_FULL_ADDER_HPP
#include "base_logic.hpp"
#include "half_adder.hpp"

class Full_adder : public base_logic{
public:
    Full_adder(); // Declaration of the constructor

    // Sets the state of an input pin.
    void SetInput(uint8_t pin, bool value) override;

private:
    Half_adder half_adder;
    Half_adder half2_adder;
    Or_gate or_gate;
    Pin input_pin[3];
    Pin output_pin[2];
};


#endif //LOGIC_SIMULATOR_FULL_ADDER_HPP
