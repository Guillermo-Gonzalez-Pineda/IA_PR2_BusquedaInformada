# Universidad de La Laguna
# Escuela Superior de Ingeniería y Tecnología
# Grado en Ingeniería Informática
# Algoritmos y Estructuras de Datos Avanzados
#
# @author Guillermo González Pineda alu0101574899
# @date September 24, 2024
# @brief CMakeLists.txt simple.
#        This does not generate documentation
#        It doesn't build any library
# CMakeLists.txt defines the whole build
# CMake reads CMakeLists.txt sequentially
#
# Build process:
#   1. cd <project_folder>
#   2. mkdir build
#   3. cd build
#   4. cmake ..
#   5. make
# Debug proccess:
#   1. cd <project_folder>
#   2. mkdir debug
#   3. cd debug
#   4. cmake -DCMAKE_BUILD_TYPE=Debug ..
#   5. make

cmake_minimum_required(VERSION 3.1)  # Mandatory

# set the project name 
project(BusquedaNoInformada                # Mandatory
    VERSION 1.0
    DESCRIPTION "A simple CMake project for the Change-Case application"
    LANGUAGES CXX)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)             # Use c++17
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Debug and release flags
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -Wall -Wextra -Wpedantic -Weffc++")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# Check if build type is Debug
if(CMAKE_BUILD_TYPE MATCHES Debug)
    # tell cmake to output binaries here:
    message(STATUS "Debug build.")
    set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/debug)  # Debug build: output to debug folder
else()
    # tell cmake to output binaries here:
    message(STATUS "Release build.")
    set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)  # Release build: output to build folder
endif()

# tell cmake where to look for *.h files
include_directories(${PROJECT_SOURCE_DIR}/src)

# Adds an executable target called "BusquedaNoInformada" to be built from the source files listed in the command invocation.
add_executable(Busqueda_A_Estrella
    src/main.cpp
    include/Nodo.hpp
    include/Laberinto.hpp
    include/Busqueda_A_estrella.hpp
    )

# Add expected compiler features to a target.
target_compile_features(Busqueda_A_Estrella PRIVATE cxx_std_17)

# Add compile options to a target.
target_compile_options(Busqueda_A_Estrella PRIVATE -Wall -Wextra -Wpedantic -Weffc++)