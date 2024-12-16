//
// Created by Lynn Meindertsma on 14 Dec 2024.
//
#include "Pin.hpp"
#include "exception.hpp"

/// Retrieves the input value of the pin.
/// @param pin Must always be 0.
/// @return The input value of the pin.
/// @throws Exception if the pin is invalid or the input value is not set.
uint8_t Pin::get_input(uint8_t pin) {
    if (pin){throw Exception("Error, pin must be < 1 (pin)\n");}
    if (input_value == 255){throw Exception("Error, value not set (pin)\n");}

    return input_value;
}
/// Retrieves the output value of the pin.
/// @param pin Must always be 0.
/// @return The output value of the pin (same as input).
/// @throws Exception if the pin is invalid or the input value is not set.
uint8_t Pin::get_output(uint8_t pin) {
    if (pin){throw Exception("Error, pin must be < 1 (pin)\n");}
    if (input_value == 255){throw Exception("Error, value not set (pin)\n");}

    return input_value;
}

/// Connects the pin's output to another logic gate's input.
/// @param output_pin The output pin of this pin object (must be 0).
/// @param other The target logic gate to connect to.
/// @param input_pin The input pin of the target gate.
/// @throws Exception if the output pin or input pin is invalid.
void Pin::connect_output(uint8_t output_pin, logic_gate *other, uint8_t input_pin) {
    if (input_pin > 2){throw Exception("Error, input pin must be < 2 (pin)\n");}
    if (output_pin > 1){throw Exception("Error, output pin must be < 1 (pin)\n");}

    connection.emplace_back(output_pin, other, input_pin);
}

/// Sets the input value for the pin and propagates the signal to connected components.
/// @param pin Must always be 0.
/// @param value The value to set (must be 0 or 1).
/// @throws Exception if the pin or value is invalid.
void Pin::set_input(uint8_t pin, uint8_t value) {
    if (pin){throw Exception("Error, pin must be < 1 (pin)\n");}
    if (value > 2){throw Exception("Error, value must be < 2 (pin)\n");}

    input_value = value;

    for (uint32_t i = 0; i < connection.size(); i++) {
        connection[i].target_component->set_input(connection[i].input_pin, input_value);
    }
}

