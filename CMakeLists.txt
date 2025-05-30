cmake_minimum_required(VERSION 4.0)
project(CppDialogue)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add RaftLib as subdirectory
add_subdirectory(lib/sobjectizer/dev)

# Your executable
add_executable(cppdialogue src/main.cpp)

# Link RaftLib library
target_link_libraries(cppdialogue PRIVATE sobjectizer::SharedLib)