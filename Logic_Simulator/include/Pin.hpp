//
// Created by Lynn Meindertsma on 14 Dec 2024.
//
#ifndef LOGIC_SIMULATOR_PIN_HPP
#define LOGIC_SIMULATOR_PIN_HPP
#include "base_logic.hpp"

class Pin : public base_logic {
public:
    Pin(): base_logic(1, 1, "PIN") {};  // Constructor to initialize the state of the NOT gate.

    // Sets the state of an input pin.
    void SetInput(uint8_t pin, bool value) override;
};

#endif //LOGIC_SIMULATOR_PIN_HPP
