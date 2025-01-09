//
// Created by Lynn Meindertsma on 10 Dec 2024.
//

#include "connection.hpp"
/// Constructor for the Connection class.
/// Establishes a connection between an output pin of a logic gate and an input pin of another logic gate.
/// @param output The output pin number of the source logic gate.
/// @param target A pointer to the target logic gate to connect to.
/// @param input The input pin number of the target logic gate.
Connection::Connection(uint8_t output, ILogicComponent* target, uint8_t input) {
    output_pin = output;
    target_component = target;
    input_pin = input;
}