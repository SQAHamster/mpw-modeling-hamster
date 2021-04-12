#ifndef HAMSTERSIMULATOR_CPP_SDLAPPLICATIONLISTENER_H
#define HAMSTERSIMULATOR_CPP_SDLAPPLICATIONLISTENER_H

#include <SDL.h>

namespace hamstersimulator {

class SdlApplication;

class SdlApplicationListener {
public:

    virtual ~SdlApplicationListener() = default;

    virtual void onInitialized(SdlApplication& application) = 0;

    virtual void onEvent(SDL_Event& event) = 0;

    virtual void onRender(SDL_Renderer& renderer) = 0;

    virtual void onClose() = 0;
};

}

#endif //HAMSTERSIMULATOR_CPP_SDLAPPLICATIONLISTENER_H
