cmake_minimum_required(VERSION 4.0)
project(CppDialogue)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(lib/sobjectizer/dev)
add_subdirectory(lib/SDL)
add_subdirectory(lib/whisper.cpp)

add_executable(cppdialogue src/main.cpp)

target_link_libraries(cppdialogue PRIVATE sobjectizer::SharedLib SDL3::SDL3 whisper)