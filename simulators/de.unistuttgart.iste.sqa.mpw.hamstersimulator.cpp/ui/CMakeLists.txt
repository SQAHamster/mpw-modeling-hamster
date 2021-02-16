project(hamstersimulator_sdl2)

set(CMAKE_CXX_STANDARD 17)

if (MSVC)
  include(CMakeListsLocalProperties.cmake) # define SDL properties on Windows
endif()

# SDL
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/") ## use helper SDL2 cmake file (see https://github.com/trenki2/SDL2Test/tree/master/cmake)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIR} ${SDL2TTF_INCLUDE_DIR})
include_directories(${SDL2_INCLUDE_DIRS}/.. ${SDL2IMAGE_INCLUDE_DIR}/.. ${SDL2TTF_INCLUDE_DIR}/..) # for nanogui internal includes

include(IncludeNanogui.cmake)

# Own Sources
include_directories(.)
set(SRCS SdlApplicationListener.h
    SdlApplication.cpp SdlApplication.h
    HamsterApplicationHandler.cpp HamsterApplicationHandler.h
    SdlGameInputInterface.cpp SdlGameInputInterface.h
    util/InputDialogWindow.cpp util/InputDialogWindow.h)

# Executable
add_executable(hamstersimulator_cpp main.cpp ${SRCS})
target_link_libraries(hamstersimulator_cpp hamster_core_lib ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES} nanogui_lib)

# Examples
add_executable(hamstersimulator_example01 examples/Example01.cpp ${SRCS})
target_link_libraries(hamstersimulator_example01 hamster_core_lib ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES} nanogui_lib)

add_executable(hamstersimulator_example02 examples/Example02.cpp ${SRCS})
target_link_libraries(hamstersimulator_example02 hamster_core_lib ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES} nanogui_lib)

# Copy resources
add_custom_command(TARGET hamstersimulator_cpp PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources/ ${CMAKE_CURRENT_BINARY_DIR}/resources)
add_custom_command(TARGET hamstersimulator_cpp PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/resources/ ${CMAKE_CURRENT_BINARY_DIR}/resources)

add_custom_command(TARGET hamstersimulator_example01 PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources/ ${CMAKE_CURRENT_BINARY_DIR}/resources)
add_custom_command(TARGET hamstersimulator_example01 PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/resources/ ${CMAKE_CURRENT_BINARY_DIR}/resources)

add_custom_command(TARGET hamstersimulator_example02 PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources/ ${CMAKE_CURRENT_BINARY_DIR}/resources)
add_custom_command(TARGET hamstersimulator_example02 PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/resources/ ${CMAKE_CURRENT_BINARY_DIR}/resources)

add_custom_command(TARGET hamstersimulator_example02 PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources/ ${CMAKE_CURRENT_BINARY_DIR}/resources)
add_custom_command(TARGET hamstersimulator_example02 PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/resources/ ${CMAKE_CURRENT_BINARY_DIR}/resources)

if (MSVC)
  # copy SDL DLLs to output
  add_custom_command(TARGET hamstersimulator_cpp POST_BUILD
          COMMAND ${CMAKE_COMMAND} -E copy_directory
          ${SDL2_DIR}/lib/x64/ $<TARGET_FILE_DIR:hamstersimulator_cpp>)
  # copy SDL_image DLLs to output
  add_custom_command(TARGET hamstersimulator_cpp POST_BUILD
          COMMAND ${CMAKE_COMMAND} -E copy_directory
          ${SDL2_IMAGE_DIR}/lib/x64/ $<TARGET_FILE_DIR:hamstersimulator_cpp>)
  # copy SDL_ttf DLLs to output
  add_custom_command(TARGET hamstersimulator_cpp POST_BUILD
          COMMAND ${CMAKE_COMMAND} -E copy_directory
          ${SDL2_TTF_DIR}/lib/x64/ $<TARGET_FILE_DIR:hamstersimulator_cpp>)
endif()

## From Stackoverflow (https://stackoverflow.com/a/62645348)
# Never set CMAKE_CXX_FLAGS in your CMakeLists.txt
# Never use include_directories or link_directories
# Never use target_link_libraries without a visibility specifier.
# Never set paths to libs manually.
# Don't set your target names equal to the project name. It's pointless complexity and bad style.