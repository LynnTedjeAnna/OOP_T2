//
// Created by Lynn Meindertsma on 14 Dec 2024.
//
#ifndef LOGIC_SIMULATOR_FULL_ADDER_HPP
#define LOGIC_SIMULATOR_FULL_ADDER_HPP
#include "half_adder.hpp"

class Full_adder : public ILogicComponent{
public:
    Full_adder(); // Declaration of the constructor

    // Sets the state of an input pin.
    void set_input(uint8_t pin, uint8_t value) override;

private:
    Half_adder half_adder;
    Half_adder half2_adder;
    Or_gate or_gate;
    Pin input_pin[3];
    Pin output_pin[2];
};


#endif //LOGIC_SIMULATOR_FULL_ADDER_HPP
