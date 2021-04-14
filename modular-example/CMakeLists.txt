cmake_minimum_required(VERSION 3.14)
project(modular_example C)

set(CMAKE_C_STANDARD 99)

add_executable(modular_example main.c shape.c movement.c)