#include "SdlApplication.h"

#include <iostream>
#include <utility>

namespace hamstersimulator {

static std::string getSdlErrorAsString() {
    return std::string("SDL Error: ") + SDL_GetError();
}
static void throwExceptionWithSdlError(const std::string& message) {
    throw std::runtime_error(message + " " + getSdlErrorAsString());
}

SdlApplication::SdlApplication(std::string title, SdlApplicationListener& listener)
        : title(std::move(title))
        , listener(listener) {
}

void SdlApplication::initialize(int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throwExceptionWithSdlError("SDL could not initialize!");
    } else {
        window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                  width, height, SDL_WINDOW_SHOWN);
        if (window == nullptr) {
            throwExceptionWithSdlError("Window could not be created!");
        } else {
            int imageFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imageFlags) & imageFlags)) {
                throwExceptionWithSdlError("SDL_image could not initialize!");
            } else {
                renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
                if (renderer == nullptr) {
                    throwExceptionWithSdlError("Renderer could not be created!");
                } else {
                    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                    listener.onInitialized(*this);
                }
            }
        }
    }

}


void SdlApplication::runApplication() {
    running = true;

    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            listener.onEvent(event);
        }

        SDL_RenderClear(renderer);

        listener.onRender(*renderer);

        SDL_RenderPresent(renderer);
    }

    listener.onClose();

    dispose();
}

SDL_Texture& SdlApplication::loadTexture(const std::string& path) {
    SDL_Texture* newTexture = nullptr;

    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr) {
        throwExceptionWithSdlError("Unable to load image " + path);
    } else {
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        SDL_FreeSurface(loadedSurface);
        if (newTexture == nullptr) {
            throwExceptionWithSdlError("Unable to texture from " + path);
        }
    }

    loadedTextures.push_back(newTexture);

    return *newTexture;
}

void SdlApplication::setTimerInterval(long milliseconds) {

}

void SdlApplication::dispose() {
    if (disposed) {
        return;
    }

    for (auto texture : loadedTextures) {
        SDL_DestroyTexture(texture);
    }
    loadedTextures.clear();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = nullptr;
    renderer = nullptr;

    IMG_Quit();
    SDL_Quit();

    disposed = true;
}

}
