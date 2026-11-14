cmake_minimum_required(VERSION 3.16)
project(fizkat LANGUAGES CXX)

add_executable(fizkat main.cpp inventory.cpp fleet.cpp)
target_compile_features(fizkat PRIVATE cxx_std_17)
set_target_properties(fizkat PROPERTIES CXX_EXTENSIONS OFF)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(fizkat PRIVATE -Wall -Wextra -Wpedantic)
endif()
if(MINGW)
    target_link_options(fizkat PRIVATE -static)
endif()
