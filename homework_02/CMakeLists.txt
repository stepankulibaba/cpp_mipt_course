cmake_minimum_required(VERSION 3.16)
project(calculator_patterns LANGUAGES CXX)

add_executable(calculator_demo
    src/main.cpp
    src/calculator.cpp
)

target_compile_features(calculator_demo PRIVATE cxx_std_17)

if(MINGW)
    target_link_options(calculator_demo PRIVATE -static)
endif()
