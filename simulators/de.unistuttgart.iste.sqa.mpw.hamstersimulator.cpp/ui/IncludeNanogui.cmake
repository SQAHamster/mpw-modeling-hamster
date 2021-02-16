# SDL2 Nanogui toolkit
SET(NANOGUI_BUILD_EXAMPLE OFF)
include(FetchContent)
FetchContent_Declare(
        nanogui
        GIT_REPOSITORY https://github.com/dalerank/nanogui-sdl
        GIT_TAG 24fc12ca7a0789f52b72204d88ddbf0a1c3eb0be
        CMAKE_ARGS        "-Wno-dev"
)
FetchContent_GetProperties(nanogui)
FetchContent_MakeAvailable(nanogui)

include_directories(${nanogui_SOURCE_DIR})

get_directory_property(NANOGUI_SRCS DIRECTORY ${nanogui_SOURCE_DIR} DEFINITION NNGUI_BASIC_SOURCE)
string(REGEX REPLACE "(sdlgui/[a-z_]+\\.(h|cpp|c))" "${nanogui_SOURCE_DIR}/\\1" NANOGUI_SRCS "${NANOGUI_SRCS}")

add_library(nanogui_lib STATIC ${NANOGUI_SRCS})

if(CMAKE_CXX_COMPILER_ID STREQUAL Clang OR
        CMAKE_CXX_COMPILER_ID STREQUAL AppleClang)
    set_source_files_properties(${NANOGUI_SRCS}
            PROPERTIES
            COMPILE_FLAGS  "-Wno-c++11-narrowing")
endif()

target_include_directories(nanogui_lib PRIVATE ${NANOGUI_SRCS}/sdlgui)
set_target_properties(nanogui_lib PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(nanogui_lib PROPERTIES CMAKE_CXX_STANDARD 11)

# Disable Nanogui warnings
if ( CMAKE_COMPILER_IS_GNUCC )
    target_compile_options(nanogui_lib PRIVATE "-Wall -Wextra")
endif()
if ( MSVC )
    target_compile_options(nanogui_lib PRIVATE "/W4")
endif()
if ( CMAKE_CXX_COMPILER_ID MATCHES "Clang" )
    target_compile_options(nanogui_lib PRIVATE "-Wno-inconsistent-missing-override")
endif()