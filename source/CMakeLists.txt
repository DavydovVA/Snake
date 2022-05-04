cmake_minimum_required(VERSION 3.10)

# Project name
project(Snake VERSION 1.0)

# C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Cmake install path
# Path, which specifies where to look for required custom libraries (.dll, .lib) ??????????
set(CMAKE_INSTALL_PATH "$ORIGIN/../lib")

# Executable
add_executable(Snake Source.cpp)

target_include_directories(Snake PUBLIC
                                                "$(PROJECT_BINARY_DIR)"
                                               )

install(TARGETS Snake DESTINATION bin)