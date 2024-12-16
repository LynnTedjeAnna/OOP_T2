//
// Created by Lynn Meindertsma on 14 Dec 2024.
//
#include "half_adder.hpp"
#include "exception.hpp"

/// Constructor for the Half_adder class.
/// Initializes the internal connections between the XOR gate, AND gate, and output pins.
Half_adder::Half_adder() {
    input_pin[0].connect_output(0, &xor_gate, 0);
    input_pin[0].connect_output(0, &and_gate, 0);
    input_pin[1].connect_output(0, &xor_gate, 1);
    input_pin[1].connect_output(0, &and_gate, 1);
    xor_gate.connect_output(0, &output_pin[0], 0);      // Sum
    and_gate.connect_output(0, &output_pin[1], 0);      // Carry
}

/// Retrieves the input value of a specific pin of the half adder.
/// @param pin The pin number (0 or 1).
/// @return The input value of the specified pin.
/// @throws Exception if the pin is invalid or the input value is not set.
uint8_t Half_adder::get_input(uint8_t pin) {
    if (pin > 1){throw Exception("Error, pin must be < 2 (h_adder)\n");}
    if (input_value[0] == 255){throw Exception("Error, value not set (h_adder)\n");}
    if (input_value[1] == 255){throw Exception("Error, value not set (h_adder)\n");}

    return input_value[pin];
}

/// Retrieves the output value of a specific pin of the half adder.
/// @param pin The pin number (0 for Sum, 1 for Carry).
/// @return The output value of the specified pin.
/// @throws Exception if the pin is invalid.
uint8_t Half_adder::get_output(uint8_t pin) {
    if (pin > 1){throw Exception("Error, pin must be < 2 (h_adder)\n");}
    return output_pin[pin].get_output(0);
}

/// Connects the output of the half adder to another logic gate's input.
/// @param out_pin The output pin of this half adder (0 for Sum, 1 for Carry).
/// @param other The target logic gate to connect to.
/// @param in_pin The input pin of the target gate.
/// @throws Exception if the output pin or input pin is invalid.
void Half_adder::connect_output(uint8_t out_pin, logic_gate *other, uint8_t in_pin) {
    if (in_pin > 1){throw Exception("Error, input pin must be < 2");}
    if (out_pin > 1){throw Exception("Error, output pin must be < 2");}

    connection.emplace_back(out_pin, other, in_pin);
}

/// Sets the input value for a specific pin of the half adder and calculates the outputs.
/// Propagates the output values (Sum and Carry) to connected components.
/// @param pin The pin number to set the input value for (0 or 1).
/// @param value The value to set (0 or 1).
/// @throws Exception if the pin or value is invalid.
void Half_adder::set_input(uint8_t pin, uint8_t value) {
    if (pin > 1){throw Exception("Error, pin must be < 2 ()xor");}
    if (value > 1){throw Exception("Error, value < 2 (xor)\n");}

    input_value[pin] = value;
    input_pin[pin].set_input(0, value);

    if (input_value[0] == 255){ return;}        // no value set
    if (input_value[1] == 255){ return;}        // no value set

    output_value[0] = output_pin[0].get_output(0);
    output_value[1] = output_pin[1].get_output(0);

    for (uint32_t i = 0; i < connection.size(); i++) {
        connection[i].target_component->set_input(connection[i].input_pin, output_value[connection[i].output_pin]);
    }
}
