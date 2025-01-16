//
// Created by Lynn Meindertsma on 09 Dec 2024.
//
#ifndef LOGIC_SIMULATOR_LOGIC_GATE_HPP
#define LOGIC_SIMULATOR_LOGIC_GATE_HPP
#include <vector>
#include "connection.hpp"

class ILogicComponent {
public:
    virtual ~ILogicComponent() = default;

    // Returns the state of an input pin.
    virtual bool GetInput(uint8_t pin) = 0;

    // Returns the state of an output pin.
    virtual bool GetOutput(uint8_t pin) = 0;

    // Sets the state of an input pin.
    virtual void SetInput(uint8_t pin, bool value) = 0;

    // Connects an output of this component to an input of another component.
    virtual void ConnectOutput(uint8_t output_pin, ILogicComponent* other, uint8_t input_pin) = 0;
};

#endif //LOGIC_SIMULATOR_LOGIC_GATE_HPP
