//
// Created by Lynn Meindertsma on 14 Dec 2024.
//
#include "xor_gate.hpp"
#include "exception.hpp"

// Definition of the Xor_gate constructor
Xor_gate::Xor_gate(): base_logic(2, 1, "XOR") {
    pin[0].ConnectOutput(0, &and1, 0);
    pin[0].ConnectOutput(0, &not2, 0);
    not2.ConnectOutput(0, &and2, 0);
    pin[1].ConnectOutput(0, &and2, 1);
    pin[1].ConnectOutput(0, &not1, 0);
    not1.ConnectOutput(0, &and1, 1);
    and1.ConnectOutput(0, &or_gate, 0);
    and2.ConnectOutput(0, &or_gate, 1);
}

/// Sets the input value for a specific pin and propagates the signal.
/// @param input_pin The pin number to set the input value for (0 or 1).
/// @param value The value to set (must be 0 or 1).
/// @throws Exception if the pin or value is invalid.
void Xor_gate::SetInput(uint8_t input_pin, bool value) {
    validate_pin(input_pin, max_input_pins, "OR");

    input_value[input_pin] = value;
    pin[input_pin].SetInput(0, value);
    if (input_value[0] == 255){
        return;
    }
    if (input_value[1] == 255){
        return;
    }

    output_value[0] = or_gate.GetOutput(0);

    for (uint32_t i = 0; i < connections.size(); i++) {
        connections[i].target_component->SetInput(connections[i].input_pin, output_value[0]);
    }
}


