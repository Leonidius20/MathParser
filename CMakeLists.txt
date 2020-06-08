cmake_minimum_required(VERSION 3.15)
project(MathParser)

set(CMAKE_CXX_STANDARD 20)

add_executable(MathParser main.cpp stack.h token.cpp token.h shunting_yard.cpp shunting_yard.h calculator.cpp calculator.h TreeNode.cpp TreeNode.h visitor.h Tree.h Tree.cpp evaluator.h evaluator.cpp optimizer.h optimizer.cpp)
