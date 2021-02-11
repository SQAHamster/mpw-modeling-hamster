## Setup SDL

### General

* create a `CMakeListsLocalProperties.cmake` file
    * set a `CORE_DIR` variable: `set(CORE_DIR "<path-to-hamstersimulator-cpp-project-directory>")`
    * set a `CORE_LIB` variable: `set(CORE_LIB "<path-to-hamstersimulator-cpp-core-lib-file>")`
        * for Windows a `hamster_core_lib.lib` file, MacOS a `hamster_core_lib.a` file
    * Note: on Windows avoid backslashes

### MacOS

* `brew install sdl2`
* `brew install sdl2_image`

### Windows

* download development libraries, extract them to a directory
    * SDL2: https://libsdl.org/release/SDL2-devel-2.0.14-VC.zip
    * SDL2 Image: https://www.libsdl.org/projects/SDL_image/release/SDL2_image-devel-2.0.5-VC.zip
* extend `CMakeListsLocalProperties.cmake` file
    * set a `SDL2_DIR` variable: `set(SDL2_DIR "<path-to-sdl-dir>")`
    * set a `SDL2_IMAGE_DIR` variable: `set(SDL2_IMAGE_DIR "<path-to-sdl-image-dir>")`


### SDL notes

* setup based on: https://trenki2.github.io/blog/2017/07/04/using-sdl2-image-with-cmake/

## IDE

### CMake arguments

* suppress FindSDL2 warning: `-Wno-dev`