//
// Created by Lynn Meindertsma on 09 Dec 2024.
//
#ifndef LOGIC_SIMULATOR_NOT_GATE_HPP
#define LOGIC_SIMULATOR_NOT_GATE_HPP
#include "ILogicComponent.hpp"

class Not_gate : public ILogicComponent {
public:
    Not_gate(): ILogicComponent(1, 1, "NOT") {}

    // Sets the state of an input pin.
    void set_input(uint8_t pin, uint8_t value) override;
};

#endif //LOGIC_SIMULATOR_NOT_GATE_HPP
