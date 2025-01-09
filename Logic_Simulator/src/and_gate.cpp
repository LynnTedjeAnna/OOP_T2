//
// Created by Lynn Meindertsma on 10 Dec 2024.
//
#include "and_gate.hpp"
#include "exception.hpp"


/// Sets the input value for a given pin and updates the output accordingly.
/// @param pin The pin number (either 0 or 1).
/// @param value The value to set (0 or 1).
void And_gate::SetInput(uint8_t pin, bool value) {
    validate_pin(pin, max_input_pins, "AND");
    input_value[pin] = value;

    // Compute the output: AND logic
    output_value[0] = (input_value[0] == 1 && input_value[1] == 1) ? 1 : 0;

    for (uint32_t i = 0; i < connections.size(); i++) {
        connections[i].target_component->SetInput(connections[i].input_pin, output_value[0]);
    }
}

