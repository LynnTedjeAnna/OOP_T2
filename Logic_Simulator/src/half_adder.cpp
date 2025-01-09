//
// Created by Lynn Meindertsma on 14 Dec 2024.
//
#include "half_adder.hpp"
#include "exception.hpp"

// Definition of the Half_adder constructor
Half_adder::Half_adder(): base_logic(2, 2, "HALF_ADDER"){
    input_pin[0].ConnectOutput(0, &xor_gate, 0);
    input_pin[0].ConnectOutput(0, &and_gate, 0);
    input_pin[1].ConnectOutput(0, &xor_gate, 1);
    input_pin[1].ConnectOutput(0, &and_gate, 1);
    xor_gate.ConnectOutput(0, &output_pin[0], 0);      // Sum
    and_gate.ConnectOutput(0, &output_pin[1], 0);      // Carry
}

/// Sets the input value for a specific pin of the half adder and calculates the outputs.
/// Propagates the output values (Sum and Carry) to connected components.
/// @param pin The pin number to set the input value for (0 or 1).
/// @param value The value to set (0 or 1).
/// @throws Exception if the pin or value is invalid.
void Half_adder::SetInput(uint8_t pin, bool value) {
    if (pin > 1){throw Exception("Error, pin must be < 2 ()xor");}

    input_value[pin] = value;
    input_pin[pin].SetInput(0, value);

    if (input_value[0] == 255){
        return;
    }        // no value set
    if (input_value[1] == 255){
        return;
    }        // no value set

    output_value[0] = output_pin[0].GetOutput(0);
    output_value[1] = output_pin[1].GetOutput(0);

    for (uint32_t i = 0; i < connections.size(); i++) {
        connections[i].target_component->SetInput(connections[i].input_pin, output_value[connections[i].output_pin]);
    }
}
