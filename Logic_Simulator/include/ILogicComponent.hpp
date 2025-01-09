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
    virtual uint8_t GetInput(uint8_t pin) = 0;

    // Returns the state of an output pin.
    virtual uint8_t GetOutput(uint8_t pin) = 0;

    // Sets the state of an input pin.
    virtual void SetInput(uint8_t pin, bool value) = 0;

    // Connects an output of this component to an input of another component.
    virtual void ConnectOutput(uint8_t output_pin, ILogicComponent* other, uint8_t input_pin) = 0;

    // This will store the connections for each logic gate
    std::vector<Connection> connections;

    uint8_t max_input_pins = 0;            // Default maximum input pins
    uint8_t max_output_pins = 0;           // Default maximum output pins
    std::string component = "Component";
};

#endif //LOGIC_SIMULATOR_LOGIC_GATE_HPP
