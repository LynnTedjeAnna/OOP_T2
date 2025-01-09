//
// Created by Lynn Meindertsma on 09 Jan 2025.
//

#ifndef LOGIC_SIMULATOR_BASE_LOGIC_HPP
#define LOGIC_SIMULATOR_BASE_LOGIC_HPP

#include <cstdint>
#include "connection.hpp"
#include "ILogicComponent.hpp"
#include <vector>
#include "exception.hpp"

class base_logic : public ILogicComponent {
public:
    // Constructor to initialize input/output values and component name
    base_logic(uint8_t input_pins = 2, uint8_t output_pins = 1, const std::string& component_name = "Base");

    void validate_pin(uint8_t pin, uint8_t max_pin, const std::string& gate_name);
    uint8_t GetInput(uint8_t pin) override;
    uint8_t GetOutput(uint8_t pin) override;
    void ConnectOutput(uint8_t output_pin, ILogicComponent* other, uint8_t input_pin) override;

//private:
    std::vector<Connection> connections;   // This will store the connections for each logic gate
    uint8_t* input_value = nullptr;        // Default input values (uninitialized)
    uint8_t* output_value = nullptr;       // Default output value (uninitialized)
};

#endif //LOGIC_SIMULATOR_BASE_LOGIC_HPP
