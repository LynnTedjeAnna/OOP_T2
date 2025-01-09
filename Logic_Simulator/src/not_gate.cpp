//
// Created by Lynn Meindertsma on 09 Dec 2024.
//
#include "not_gate.hpp"
#include "exception.hpp"

/// Sets the input value for the NOT gate and calculates the inverted output.
/// Propagates the output to connected components.
/// @param pin Must always be 0.
/// @param value The value to set (must be 0 or 1).
/// @throws Exception if the pin or value is invalid.
void Not_gate::set_input(uint8_t pin, uint8_t value) {
    validate_pin(pin, max_input_pins, "AND");
    validate_value(value, "AND");
    input_value[pin] = value;
    output_value[pin] = !value;

    for (uint32_t i = 0; i < connections.size(); i++) {
        connections[i].target_component->set_input(connections[i].input_pin, output_value[pin]);
    }
}
