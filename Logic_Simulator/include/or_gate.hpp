//
// Created by Lynn Meindertsma on 10 Dec 2024.
//
#ifndef LOGIC_SIMULATOR_OR_GATE_HPP
#define LOGIC_SIMULATOR_OR_GATE_HPP
#include "ILogicComponent.hpp"

class Or_gate : public ILogicComponent {
public:
    Or_gate(): ILogicComponent(2, 1, "OR") {}

    // Sets the state of an input pin.
    void set_input(uint8_t pin, uint8_t value) override;
};


#endif //LOGIC_SIMULATOR_OR_GATE_HPP
