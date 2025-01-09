cmake_minimum_required(VERSION 3.25)
project(Logic_Simulator)

set(CMAKE_CXX_STANDARD 20)

include_directories(src)
include_directories(include)

add_executable(Logic_Simulator main.cpp
src/not_gate.cpp
src/connection.cpp
src/and_gate.cpp
src/or_gate.cpp
src/Pin.cpp
src/xor_gate.cpp
src/half_adder.cpp
src/full_adder.cpp
src/base_logic.cpp
)
