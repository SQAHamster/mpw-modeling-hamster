cmake_minimum_required(VERSION 3.17)
project(de_unistuttgart_iste_sqa_mpw_hamstersimulator_cpp)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_POSITION_INDEPENDENT_CODE ON) # -fPIC on gcc

## Setup MPW Simulator Framework

include(FetchContent)
FetchContent_Populate(mpw_lib
    GIT_REPOSITORY https://github.com/Fumapps/mpw-modeling-framework.git
    GIT_TAG cpp-framework
    SOURCE_DIR mpw_lib
)
add_subdirectory(${mpw_lib_SOURCE_DIR} mpw_lib/build)

include_directories(${mpw_lib_SOURCE_DIR}/core/src/generated)
include_directories(${mpw_lib_SOURCE_DIR}/core/src/impl)
include_directories(${mpw_lib_SOURCE_DIR}/core/src/framework)

## Hamstersimulator

add_subdirectory(core/src/generated)
add_subdirectory(core/src/impl)
set(SRCS ${GEN_SRCS} ${IMPL_SRCS} ${FRAMEWORK_SRCS})

include_directories(core/src/generated)
include_directories(core/src/impl)

add_library(hamster_core SHARED ${SRCS})
target_link_libraries(hamster_core mpw_framework_core_lib)

add_library(hamster_core_lib STATIC ${SRCS})
target_link_libraries(hamster_core_lib mpw_framework_core_lib)

add_subdirectory(ui)

## Setup GTEST

enable_testing()

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.10.0
)
FetchContent_MakeAvailable(googletest)

add_subdirectory(core/test)
