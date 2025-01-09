#ifndef LOGIC_SIMULATOR_AND_GATE_HPP
#define LOGIC_SIMULATOR_AND_GATE_HPP
#include "ILogicComponent.hpp"
#include "base_logic.hpp"
class And_gate : public base_logic {
public:
    And_gate() : base_logic(2, 1, "AND") {}

    // Sets the state of an input pin and calculates the output.
    void SetInput(uint8_t pin, bool value) override;
};

#endif // LOGIC_SIMULATOR_AND_GATE_HPP