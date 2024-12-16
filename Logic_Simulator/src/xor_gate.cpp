//
// Created by Lynn Meindertsma on 14 Dec 2024.
//
#include "xor_gate.hpp"
#include "exception.hpp"

/// Constructs the Xor_gate object and sets up internal connections.
Xor_gate::Xor_gate() {
    pin[0].connect_output(0, &and1, 0);
    pin[0].connect_output(0, &not2, 0);
    not2.connect_output(0, &and2, 0);
    pin[1].connect_output(0, &and2, 1);
    pin[1].connect_output(0, &not1, 0);
    not1.connect_output(0, &and1, 1);
    and1.connect_output(0, &or_gate, 0);
    and2.connect_output(0, &or_gate, 1);
}
/// Retrieves the input value of a specified pin.
/// @param pin The pin number to retrieve the input from (0 or 1).
/// @return The input value of the pin.
/// @throws Exception if the pin is invalid or the input value is not set.
uint8_t Xor_gate::get_input(uint8_t pin) {
    if (pin > 1){throw Exception("Error, pin must be < 2 (xor)\n");}
    if (input_value[0] == 255){throw Exception("Error, value not set (xor)\n");}
    if (input_value[1] == 255){throw Exception("Error, value not set (xor)\n");}

    return input_value[pin];
}
/// Retrieves the output value of the gate.
/// @param pin The pin number to retrieve the output from (must be 0).
/// @return The output value.
/// @throws Exception if the pin is invalid or the output value is not set.
uint8_t Xor_gate::get_output(uint8_t pin) {
    if (pin > 1){throw Exception("Error, pin must be < 2 (xor)\n");}
    if (output_value == 255){throw Exception("Error, value not set (xor)\n");}

    return output_value;
}

/// Connects the gate's output to another logic gate's input.
/// @param output_pin The output pin of this gate (must be 0).
/// @param other The target logic gate to connect to.
/// @param input_pin The input pin of the target gate.
/// @throws Exception if pins are out of range.
void Xor_gate::connect_output(uint8_t output_pin, logic_gate *other, uint8_t input_pin) {
    if (input_pin > 2){throw Exception("Error, input pin must be < 2 (xor)\n");}
    if (output_pin > 1){throw Exception("Error, output pin must be < 1 (xor)\n");}

    connection.emplace_back(output_pin, other, input_pin);
}

/// Sets the input value for a specific pin and propagates the signal.
/// @param input_pin The pin number to set the input value for (0 or 1).
/// @param value The value to set (must be 0 or 1).
/// @throws Exception if the pin or value is invalid.
void Xor_gate::set_input(uint8_t input_pin, uint8_t value) {
    if (input_pin > 1){throw Exception("Error, pin must be < 2 (xor)\n");}
    if (value > 2){throw Exception("Error, value < 2 (xor)\n");}

    input_value[input_pin] = value;
    pin[input_pin].set_input(0, value);
    if (input_value[0] == 255){ return;}
    if (input_value[1] == 255){ return;}

    output_value = or_gate.get_output(0);

    for (uint32_t i = 0; i < connection.size(); i++) {
        connection[i].target_component->set_input(connection[i].input_pin, output_value);
    }
}


