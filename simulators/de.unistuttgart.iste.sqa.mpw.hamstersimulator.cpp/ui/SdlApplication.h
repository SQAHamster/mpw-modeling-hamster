#ifndef HAMSTERSIMULATOR_CPP_SDLAPPLICATION_H
#define HAMSTERSIMULATOR_CPP_SDLAPPLICATION_H

#include <SDL.h>
#undef main // fixes compile error on Windows
#include <SDL_image.h>

#include <string>
#include <vector>
#include "SdlApplicationListener.h"

namespace hamstersimulator {

/// \brief Convenience wrapper of a SDL application
class SdlApplication {
public:

    SdlApplication(std::string title, SdlApplicationListener& listener);

    void initialize(int width, int height);

    void runApplication();

    SDL_Texture& loadTexture(const std::string& path);

    void setTimerInterval(long milliseconds);

    void dispose();

private:

    const std::string title;
    SdlApplicationListener& listener;

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    std::vector<SDL_Texture*> loadedTextures;

    bool running = false;
    bool disposed = false;
};

}

#endif //HAMSTERSIMULATOR_CPP_SDLAPPLICATION_H
