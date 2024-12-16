//
// Created by Lynn Meindertsma on 14 Dec 2024.
//
#include "full_adder.hpp"
#include "exception.hpp"


/// Constructor for the Full_adder class.
/// Sets up the internal connections between the input pins, two half adders,
/// the OR gate, and the output pins.
Full_adder::Full_adder() {
    input_pin[0].connect_output(0, &half_adder, 0);
    input_pin[1].connect_output(0, &half_adder, 1);
    half_adder.connect_output(0, &half2_adder, 0);
    input_pin[2].connect_output(0, &half2_adder, 1);
    half2_adder.connect_output(1, &or_gate, 0);
    half_adder.connect_output(1, &or_gate, 1);
    half2_adder.connect_output(0, &output_pin[0], 0);
    or_gate.connect_output(0, &output_pin[1], 0);
}

/// Retrieves the input value of a specific pin of the full adder.
/// @param pin The pin number (0, 1, or 2 for Carry-in).
/// @return The input value of the specified pin.
/// @throws Exception if the pin is invalid or the input value is not set.
uint8_t Full_adder::get_input(uint8_t pin) {
    if (pin > 2){throw Exception("Error, pin must be < 3 (f_adder)\n");}
    if (input_value[0] == 255){throw Exception("Error, value not set (f_adder)\n");}
    if (input_value[1] == 255){throw Exception("Error, value not set (f_adder)\n");}
    if (input_value[2] == 255){throw Exception("Error, value not set (f_adder)\n");}

    return input_value[pin];
}

/// Retrieves the output value of a specific pin of the full adder.
/// @param pin The pin number (0 for Sum, 1 for Carry-out).
/// @return The output value of the specified pin.
/// @throws Exception if the pin is invalid.
uint8_t Full_adder::get_output(uint8_t pin) {
    if (pin > 1){throw Exception("Error, pin must be < 2 (f_adder)\n");}
    return output_pin[pin].get_output(0);
}

/// Connects the output of the full adder to another logic gate's input.
/// @param out_pin The output pin of this full adder (0 for Sum, 1 for Carry-out).
/// @param other The target logic gate to connect to.
/// @param in_pin The input pin of the target gate.
/// @throws Exception if the output pin or input pin is invalid.
void Full_adder::connect_output(uint8_t out_pin, logic_gate *other, uint8_t in_pin) {
    if (in_pin > 2){throw Exception("Error, input pin must be < 3( f_adder)\n");}
    if (out_pin > 1){throw Exception("Error, output pin must be < 2 (f_adder)\n");}

    connection.emplace_back(out_pin, other, in_pin);
}


/// Sets the input value for a specific pin of the full adder and calculates the outputs.
/// Propagates the output values (Sum and Carry-out) to connected components.
/// @param pin The pin number to set the input value for (0, 1, or 2 for Carry-in).
/// @param value The value to set (0 or 1).
/// @throws Exception if the pin or value is invalid.
void Full_adder::set_input(uint8_t pin, uint8_t value) {
    if (pin > 2){throw Exception("Error, pin must be < 3 (f_adder)\n");}
    if (value > 1){throw Exception("Error, value < 2 (f_adder)\n");}

    input_value[pin] = value;
    input_pin[pin].set_input(0, value);

    if (input_value[0] == 255){ return;}        // no value set
    if (input_value[1] == 255){ return;}        // no value set
    if (input_value[2] == 255){ return;}        // no value set

    output_value[0] = output_pin[0].get_output(0);
    output_value[1] = output_pin[1].get_output(0);

    for (uint32_t i = 0; i < connection.size(); i++) {
        connection[i].target_component->set_input(connection[i].input_pin, output_value[connection[i].output_pin]);
    }
}