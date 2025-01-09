//
// Created by Lynn Meindertsma on 14 Dec 2024.
//
#include "Pin.hpp"
#include "exception.hpp"


/// Sets the input value for the pin and propagates the signal to connected components.
/// @param pin Must always be 0.
/// @param value The value to set (must be 0 or 1).
/// @throws Exception if the pin or value is invalid.
void Pin::SetInput(uint8_t pin, bool value) {
    validate_pin(pin, max_input_pins, "PIN");

    input_value[pin] = value;
    output_value[pin] = value;

    for (uint32_t i = 0; i < connections.size(); i++) {
        connections[i].target_component->SetInput(connections[i].input_pin, input_value[pin]);
    }
}

