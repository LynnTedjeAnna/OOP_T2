//
// Created by Lynn Meindertsma on 10 Dec 2024.
//
#include "or_gate.hpp"
#include "exception.hpp"

/// Sets the input value for a specific pin and calculates the gate's output.
/// Propagates the output to connected components.
/// @param pin The pin number to set the input value for (0 or 1).
/// @param value The value to set (must be 0 or 1).
/// @throws Exception if the pin or value is invalid.
void Or_gate::set_input(uint8_t pin, uint8_t value) {
    validate_pin(pin, max_input_pins, "OR");
    validate_value(value, "OR");

    input_value[pin] = value;

    if (input_value[0] == 255){
        return;
    }
    if (input_value[1] == 255){
        return;
    }

    output_value[0] = input_value[0] || input_value[1];
    for (uint32_t i = 0; i < connections.size(); i++) {
        connections[i].target_component->set_input(connections[i].input_pin, output_value[0]);
    }
}
