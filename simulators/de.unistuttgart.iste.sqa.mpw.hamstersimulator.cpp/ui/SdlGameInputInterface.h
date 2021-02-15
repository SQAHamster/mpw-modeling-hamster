#ifndef HAMSTERSIMULATOR_CPP_SDLGAMEINPUTINTERFACE
#define HAMSTERSIMULATOR_CPP_SDLGAMEINPUTINTERFACE

#include "UserInputInterface.h"
#include <SDL.h>

#include <string>

namespace hamstersimulator {

/// \brief Convenience wrapper of a SDL application
class SdlGameInputInterface : public mpw::UserInputInterface {
public:

    void onRender(SDL_Renderer& renderer);
    void onEvent(SDL_Event& event);
    bool isActive() const;

    const std::string& getUserInput();

    int readInteger(std::string message) override;
    std::string readString(std::string message) override;
    void confirmAlert(std::runtime_error t) override;
    void abort() override;

private:

    void showMessage(const std::string& message) const;
    void showMessageForTextInput(const std::string& message) const;

    bool active = false;

};

}

#endif //HAMSTERSIMULATOR_CPP_SDLGAMEINPUTINTERFACE
