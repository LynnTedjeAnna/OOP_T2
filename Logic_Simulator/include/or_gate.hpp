//
// Created by Lynn Meindertsma on 10 Dec 2024.
//
#ifndef LOGIC_SIMULATOR_OR_GATE_HPP
#define LOGIC_SIMULATOR_OR_GATE_HPP
#include "base_logic.hpp"

class Or_gate : public base_logic {
public:
    Or_gate() : base_logic(2, 1, "OR") {}

    // Sets the state of an input pin.
    void SetInput(uint8_t pin, bool value) override;
};


#endif //LOGIC_SIMULATOR_OR_GATE_HPP
