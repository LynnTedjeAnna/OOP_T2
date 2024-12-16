//
// Created by Lynn Meindertsma on 10 Dec 2024.
//
#include "or_gate.hpp"
#include "exception.hpp"

/// Retrieves the input value of a specified pin.
/// @param pin The pin number to retrieve the input from (0 or 1).
/// @return The input value of the specified pin.
/// @throws Exception if the pin is invalid or the input value is not set.
uint8_t Or_gate::get_input(uint8_t pin) {
    if (pin > 1){throw Exception("Error, pin must be < 2 (or)\n");}
    if (input_value[0] == 255){throw Exception("Error, value not set (or)\n");}
    if (input_value[1] == 255){throw Exception("Error, value not set (or)\n");}

    return input_value[pin];
}

/// Retrieves the output value of the gate.
/// @param pin Must always be 0.
/// @return The output value of the gate.
/// @throws Exception if the pin is invalid or the output value is not set.
uint8_t Or_gate::get_output(uint8_t pin) {
    if (pin > 1){throw Exception("Error, pin must be < 2 (or)\n");}
    if (output_value == 255){throw Exception("Error, value not set (or)\n");}

    return output_value;
}

/// Connects the gate's output to another logic gate's input.
/// @param output_pin The output pin of this gate (must be 0).
/// @param other The target logic gate to connect to.
/// @param input_pin The input pin of the target gate.
/// @throws Exception if the output pin or input pin is invalid.
void Or_gate::connect_output(uint8_t output_pin, logic_gate *other, uint8_t input_pin) {
    if (input_pin > 2){throw Exception("Error, input pin must be < 2 (or)\n");}
    if (output_pin > 1){throw Exception("Error, output pin must be < 1 (or)\n");}

    connection.emplace_back(output_pin, other, input_pin);
}

/// Sets the input value for a specific pin and calculates the gate's output.
/// Propagates the output to connected components.
/// @param pin The pin number to set the input value for (0 or 1).
/// @param value The value to set (must be 0 or 1).
/// @throws Exception if the pin or value is invalid.
void Or_gate::set_input(uint8_t pin, uint8_t value) {
    if (pin > 1){throw Exception("Error, pin must be < 2 (or)\n");}
    if (value > 2){throw Exception("Error, value < 2 (or)\n");}
    input_value[pin] = value;

    if (input_value[0] == 255){ return;}
    if (input_value[1] == 255){ return;}

    output_value = input_value[0] || input_value[1];
    for (uint32_t i = 0; i < connection.size(); i++) {
        connection[i].target_component->set_input(connection[i].input_pin, output_value);
    }
}
