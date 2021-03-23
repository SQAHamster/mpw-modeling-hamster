project(hamstersimulator_examples)

set(CMAKE_CXX_STANDARD 17)

# Executable Examples
add_executable(hamstersimulator_example01 Example01.cpp)
target_link_libraries(hamstersimulator_example01 hamstersimulator_main_lib)

add_executable(hamstersimulator_example02 Example02.cpp)
target_link_libraries(hamstersimulator_example02 hamstersimulator_main_lib)

add_executable(hamstersimulator_example03 Example03.cpp)
target_link_libraries(hamstersimulator_example03 hamstersimulator_main_lib)

# Copy resources from binary root (only trigger for one example)
add_custom_command(TARGET hamstersimulator_example01 PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_BINARY_DIR}/resources/ ${CMAKE_CURRENT_BINARY_DIR}/resources)
