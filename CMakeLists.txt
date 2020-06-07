cmake_minimum_required(VERSION 3.15)
project(MathParser)

set(CMAKE_CXX_STANDARD 20)

add_executable(MathParser main.cpp stack.h token.cpp token.h calculator.cpp calculator.h TreeNode.cpp TreeNode.h lexer.cpp lexer.h parser.h parser.cpp shunting_yard.h shunting_yard.cpp)
