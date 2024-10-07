cmake_minimum_required(VERSION 3.28)
project(starter_assignment)

set(CMAKE_CXX_STANDARD 26)

include_directories(include src)

add_executable(starter_assignment src/main.cpp
        src/administration.cpp
        src/student.cpp
)
