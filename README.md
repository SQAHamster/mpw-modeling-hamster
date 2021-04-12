# MPW Hamstersimulator (C++ Library)

Branch used to provide a release repository as a C++ source library.

The C++ simulator is deployed by the source code directly. This is done like
GTEST, where the source code gets pulled by CMake and compiled with the same compiler like
the target program.
CMake has built-in functionality to fetch the dependency from source (FetchContent).