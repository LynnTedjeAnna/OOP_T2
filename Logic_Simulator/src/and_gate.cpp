//
// Created by Lynn Meindertsma on 10 Dec 2024.
//
#include "and_gate.hpp"
#include "exception.hpp"

/// Gets the input value for a given pin.
/// @param pin The pin number (either 0 or 1).
/// @return The input value for the specified pin.
uint8_t And_gate::get_input(uint8_t pin) {
    if (pin > 1){throw Exception("Error, pin must be < 2(and)\n");}
    if (input_value[0] == 255){throw Exception("Error, value not set (and)\n");}
    if (input_value[1] == 255){throw Exception("Error, value not set (and)\n");}

    return input_value[pin];
}

/// Gets the output value of the AND gate.
/// @param pin The pin number (should be 0).
/// @return The output value of the AND gate.
uint8_t And_gate::get_output(uint8_t pin) {
    if (pin > 1){throw Exception("Error, pin must be < 2 (and)\n");}
    if (output_value == 255){throw Exception("Error, value not set (and)\n");}

    return output_value;
}

/// Connects an output pin of this gate to an input pin of another gate.
/// @param output_pin The output pin number of this gate.
/// @param other A pointer to the target logic gate.
/// @param input_pin The input pin number of the target logic gate.
void And_gate::connect_output(uint8_t output_pin, logic_gate *other, uint8_t input_pin) {
    if (input_pin > 2){throw Exception("Error, input pin must be < 2 (and)\n");}
    if (output_pin > 1){throw Exception("Error, output pin must be < 1 (and)\n");}

    connection.emplace_back(output_pin, other, input_pin);
}

/// Sets the input value for a given pin and updates the output accordingly.
/// @param pin The pin number (either 0 or 1).
/// @param value The value to set (0 or 1).
void And_gate::set_input(uint8_t pin, uint8_t value) {
    if (pin > 1){throw Exception("Error, pin must be < 2 (and)");}
    if (value > 2){throw Exception("Error, value < 2 (and)\n");}
    input_value[pin] = value;

    if (input_value[0]== 1){
        if (input_value[1] == 1){
            output_value = 1;       // if both input is 1 output is 1
        }
    }

    for (uint32_t i = 0; i < connection.size(); i++) {
        connection[i].target_component->set_input(connection[i].input_pin, output_value);
    }
}