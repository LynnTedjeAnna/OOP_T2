//
// Created by Lynn Meindertsma on 09 Jan 2025.
//

#include "base_logic.hpp"
#include "invalid_pin_exception.hpp"
#include "connection_already_created.hpp"

// Constructor to initialize input/output values and component name
base_logic::base_logic(uint8_t input_pins, uint8_t output_pins, const std::string& component_name)
        : ILogicComponent(){
    // Dynamically allocate memory for input and output arrays
    input_value = new bool[input_pins];
    output_value = new bool[output_pins];
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
        throw invalid_pin_exception("Invalid PIN entered."+ std::to_string(max_pin) + " (" + gate_name + ")\n");
    }
}

// Centralized logic for getting input values
bool base_logic::GetInput(uint8_t pin) {
    bool value;
    validate_pin(pin, max_input_pins, component);
    value = input_value[pin];
    return value;
}

// Centralized logic for getting output values
bool base_logic::GetOutput(uint8_t pin) {
    bool value;
    validate_pin(pin, max_output_pins, component);
    value = output_value[pin];
    return value;
}

// Connects an output of this component to an input of another component.
void base_logic::ConnectOutput(uint8_t output_pin, ILogicComponent* other, uint8_t input_pin) {
    validate_pin(output_pin, max_output_pins, component);
    // Check if the connection already exists
    for (std::vector<Connection>::iterator it = connections.begin(); it != connections.end(); ++it) {
        if (it->output_pin == output_pin && it->input_pin == input_pin && it->target_component == other) {
            throw connection_already_created("Connection already exists between output pin " +
                                        std::to_string(output_pin) + " and input pin " +
                                        std::to_string(input_pin) + " of the other component.");
        }
    }

    try {
        // Attempt to set the input pin of the other component
        other->SetInput(input_pin, false);
    } catch (const invalid_pin_exception& e) {
        throw invalid_pin_exception("Failed to connect output pin " + std::to_string(output_pin) +
                                    " of component '" + component +
                                    "' to input pin " + std::to_string(input_pin) +
                                    " of the other component: " + e.what());
    }
    connections.emplace_back(output_pin, other, input_pin);
}




