#ifndef HAMSTERSIMULATOR_CPP_SDLGAMEINPUTINTERFACE
#define HAMSTERSIMULATOR_CPP_SDLGAMEINPUTINTERFACE

#include "UserInputInterface.h"
#include "SdlApplication.h"
#include "util/InputDialogWindow.h"
#include "MpwSemaphore.h"

#include <SDL.h>
#include <sdlgui/screen.h>

#include <string>

namespace hamstersimulator {

/// \brief Convenience wrapper of a SDL application
class SdlGameInputInterface : public mpw::UserInputInterface {
public:

    SdlGameInputInterface(sdlgui::Screen& screen);

    void onRender(SDL_Renderer& renderer);
    void onEvent(SDL_Event& event);
    bool isActive() const;

    int readInteger(std::string message) override;
    std::string readString(std::string message) override;
    void confirmAlert(const std::exception& t) override;
    void abort() override;

private:

    void showMessage(const std::string& message, InputDialogWindow::Type type);
    void showMessageForTextInput(const std::string& message, InputDialogWindow::Type type);

    bool active = false;

    InputDialogWindow* inputDialog;

    sdlgui::Screen& screen;
    framework::Semaphore semaphore;

    void wait();
};

}

#endif //HAMSTERSIMULATOR_CPP_SDLGAMEINPUTINTERFACE
