//
// Created by Lynn Meindertsma on 14 Dec 2024.
//
#include "full_adder.hpp"
#include "exception.hpp"

// Definition of the Full_adder constructor
Full_adder::Full_adder() :ILogicComponent(3, 2, "FULL_ADDER") {
    input_pin[0].connect_output(0, &half_adder, 0);
    input_pin[1].connect_output(0, &half_adder, 1);
    half_adder.connect_output(0, &half2_adder, 0);
    input_pin[2].connect_output(0, &half2_adder, 1);
    half2_adder.connect_output(1, &or_gate, 0);
    half_adder.connect_output(1, &or_gate, 1);
    half2_adder.connect_output(0, &output_pin[0], 0);
    or_gate.connect_output(0, &output_pin[1], 0);
}

/// Sets the input value for a specific pin of the full adder and calculates the outputs.
/// Propagates the output values (Sum and Carry-out) to connected components.
/// @param pin The pin number to set the input value for (0, 1, or 2 for Carry-in).
/// @param value The value to set (0 or 1).
/// @throws Exception if the pin or value is invalid.
void Full_adder::set_input(uint8_t pin, uint8_t value) {
    validate_pin(pin, max_input_pins, "OR");
    validate_value(value, "OR");

    input_value[pin] = value;
    input_pin[pin].set_input(0, value);

    if (input_value[0] == 255){
        return;
    }        // no value set
    if (input_value[1] == 255){
        return;
    }        // no value set
    if (input_value[2] == 255){
        return;
    }        // no value set

    output_value[0] = output_pin[0].get_output(0);
    output_value[1] = output_pin[1].get_output(0);

    for (uint32_t i = 0; i < connections.size(); i++) {
        connections[i].target_component->set_input(connections[i].input_pin, output_value[connections[i].output_pin]);
    }
}