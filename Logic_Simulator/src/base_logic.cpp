//
// Created by Lynn Meindertsma on 09 Jan 2025.
//

#include "base_logic.hpp"

// Constructor to initialize input/output values and component name
base_logic::base_logic(uint8_t input_pins, uint8_t output_pins, const std::string& component_name)
        : ILogicComponent(){
    // Dynamically allocate memory for input and output arrays
    input_value = new uint8_t[input_pins];
    output_value = new uint8_t[output_pins];
     component = component_name;
     max_input_pins = input_pins;
     max_output_pins = output_pins;

    // Initialize all values to 255 using a loop (no memset)
    for (uint8_t i = 0; i < input_pins; ++i) {
        input_value[i] = 255;  // Use array indexing
    }

    for (uint8_t i = 0; i < output_pins; ++i) {
        output_value[i] = 255;  // Use array indexing
    }
}


void base_logic::validate_pin(uint8_t pin, uint8_t max_pin, const std::string& gate_name) {
    if (pin >= max_pin) {
        throw Exception("Error, pin must be < " + std::to_string(max_pin) + " (" + gate_name + ")\n");
    }
}


// Centralized logic for getting input values
uint8_t base_logic::GetInput(uint8_t pin) {
    validate_pin(pin, max_input_pins, component);
    return input_value[pin];
}

// Centralized logic for getting output values
uint8_t base_logic::GetOutput(uint8_t pin) {
    validate_pin(pin, max_output_pins, component);
    return output_value[pin];
}

// Connects an output of this component to an input of another component.
void base_logic::ConnectOutput(uint8_t output_pin, ILogicComponent* other, uint8_t input_pin) {
    validate_pin(output_pin, max_output_pins, component);
    validate_pin(input_pin, other->max_input_pins, other->component);
    connections.emplace_back(output_pin, other, input_pin);
}




