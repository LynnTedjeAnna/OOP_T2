//
// Created by Lynn Meindertsma on 09 Dec 2024.
//
#ifndef LOGIC_SIMULATOR_NOT_GATE_HPP
#define LOGIC_SIMULATOR_NOT_GATE_HPP
#include "base_logic.hpp"

class Not_gate : public base_logic {
public:
    Not_gate(): base_logic(1, 1, "NOT") {}

    // Sets the state of an input pin.
    void SetInput(uint8_t pin, bool value) override;
};

#endif //LOGIC_SIMULATOR_NOT_GATE_HPP
