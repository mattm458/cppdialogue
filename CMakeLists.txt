cmake_minimum_required(VERSION 4.0)
project(CppDialogue)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(lib/sobjectizer/dev)
add_subdirectory(lib/SDL)
add_subdirectory(lib/whisper.cpp)

set(WAV_DIR ${CMAKE_SOURCE_DIR}/wav)
set(WAV_LINK ${CMAKE_BINARY_DIR}/wav)
add_custom_command(
    OUTPUT ${WAV_LINK}
    COMMAND ${CMAKE_COMMAND} -E create_symlink ${WAV_DIR} ${WAV_LINK}
)

add_custom_target(wav_dir ALL DEPENDS ${WAV_LINK})

add_executable(cppdialogue src/main.cpp)

target_link_libraries(cppdialogue PRIVATE sobjectizer::SharedLib SDL3::SDL3 whisper)