#ifndef LOGIC_SIMULATOR_AND_GATE_HPP
#define LOGIC_SIMULATOR_AND_GATE_HPP
#include "ILogicComponent.hpp"

class And_gate : public ILogicComponent {
public:
    And_gate() : ILogicComponent(2, 1, "AND") {}

    // Sets the state of an input pin and calculates the output.
    void set_input(uint8_t pin, uint8_t value) override;
};

#endif // LOGIC_SIMULATOR_AND_GATE_HPP