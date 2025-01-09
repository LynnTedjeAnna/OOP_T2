//
// Created by Lynn Meindertsma on 14 Dec 2024.
//
#ifndef LOGIC_SIMULATOR_XOR_GATE_HPP
#define LOGIC_SIMULATOR_XOR_GATE_HPP
#include "base_logic.hpp"
#include "not_gate.hpp"
#include "or_gate.hpp"
#include "and_gate.hpp"
#include "Pin.hpp"

class Xor_gate : public base_logic {
public:
    Xor_gate();   // Declaration of the constructor

    // Sets the state of an input pin.
    void SetInput(uint8_t pin, bool value) override;

private:
    Not_gate not1;
    Not_gate not2;
    And_gate and1;
    And_gate and2;
    Or_gate or_gate;
    Pin pin[2];
};


#endif //LOGIC_SIMULATOR_XOR_GATE_HPP
