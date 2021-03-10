# SDL2 Nanogui toolkit
SET(NANOGUI_BUILD_EXAMPLE OFF)
include(FetchContent)
FetchContent_Declare(
        nanogui
        GIT_REPOSITORY https://github.com/dalerank/nanogui-sdl
        GIT_TAG 24fc12ca7a0789f52b72204d88ddbf0a1c3eb0be
        CMAKE_ARGS "-Wno-dev"
)
FetchContent_GetProperties(nanogui)
FetchContent_MakeAvailable(nanogui)

include_directories(SYSTEM ${nanogui_SOURCE_DIR}) # use SYSTEM to avoid warnings

get_directory_property(NANOGUI_SRCS DIRECTORY ${nanogui_SOURCE_DIR} DEFINITION NNGUI_BASIC_SOURCE)
string(REGEX REPLACE "(sdlgui/[a-z_]+\\.(h|cpp|c))" "${nanogui_SOURCE_DIR}/\\1" NANOGUI_SRCS "${NANOGUI_SRCS}")

# Fix removed usage of std::unary_function in nanogui src (function is removed by C++ 17)
file(READ "${nanogui_SOURCE_DIR}/sdlgui/nanort.h" nanort_header_file_content)
string(REGEX REPLACE "std::unary_function\\<unsigned int, bool\\>" "std::function<bool(unsigned int)>" nanort_header_file_content "${nanort_header_file_content}")
file(WRITE "${nanogui_SOURCE_DIR}/sdlgui/nanort.h" "${nanort_header_file_content}")

add_library(nanogui_lib STATIC ${NANOGUI_SRCS})

# Disable Nanogui warnings
if (CMAKE_COMPILER_IS_GNUCC)
    set_source_files_properties(${NANOGUI_SRCS}
            PROPERTIES
            COMPILE_FLAGS "-Wno-all -Wno-extra -Wno-format-truncation -Wno-narrowing")
endif ()
if (CMAKE_CXX_COMPILER_ID STREQUAL Clang OR
        CMAKE_CXX_COMPILER_ID STREQUAL AppleClang)
    set_source_files_properties(${NANOGUI_SRCS}
            PROPERTIES
            COMPILE_FLAGS "-Wno-c++11-narrowing -Wno-inconsistent-missing-override")
endif ()
if (MSVC)
    set_source_files_properties(${NANOGUI_SRCS}
            PROPERTIES
            COMPILE_FLAGS "/w")
endif ()

target_include_directories(nanogui_lib PRIVATE ${nanogui_SOURCE_DIR}/sdlgui)
set_target_properties(nanogui_lib PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(nanogui_lib PROPERTIES CMAKE_CXX_STANDARD 11)
