cmake_minimum_required(VERSION 4.0)
project(CppDialogue)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(lib/SDL)
add_subdirectory(lib/whisper.cpp)

set(EXAMPLE_DATA_DIR ${CMAKE_SOURCE_DIR}/example_data)
set(EXAMPLE_DATA_LINK ${CMAKE_BINARY_DIR}/example_data)
add_custom_command(
    OUTPUT ${EXAMPLE_DATA_LINK}
    COMMAND ${CMAKE_COMMAND} -E create_symlink ${EXAMPLE_DATA_DIR} ${EXAMPLE_DATA_LINK}
)

add_custom_target(example_data_dir ALL DEPENDS ${EXAMPLE_DATA_LINK})

add_executable(cppdialogue
    src/main.cpp
    src/PipelineExample/LowerCaseProcessor.cpp
    src/PipelineExample/StringConsumer.cpp
    src/PipelineExample/TextFileProducer.cpp
)

target_include_directories(cppdialogue PRIVATE include)

target_link_libraries(cppdialogue PRIVATE SDL3::SDL3)