cmake_minimum_required(VERSION 3.15)
project(ITP_S2_Lab3)

set(CMAKE_CXX_STANDARD 20)

add_executable(ITP_S2_Lab3 main.cpp stack.h token.cpp token.h shunting_yard.cpp shunting_yard.h calculator.cpp calculator.h)