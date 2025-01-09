//
// Created by Lynn Meindertsma on 14 Dec 2024.
//
#ifndef LOGIC_SIMULATOR_PIN_HPP
#define LOGIC_SIMULATOR_PIN_HPP
#include "ILogicComponent.hpp"

class Pin : public ILogicComponent {
public:
    Pin(): ILogicComponent(1, 1, "PIN") {};  // Constructor to initialize the state of the NOT gate.

    // Sets the state of an input pin.
    void set_input(uint8_t pin, uint8_t value) override;
};

#endif //LOGIC_SIMULATOR_PIN_HPP
