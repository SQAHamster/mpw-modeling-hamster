#ifndef HAMSTERSIMULATOR_CPP_SDLGAMEINPUTINTERFACE
#define HAMSTERSIMULATOR_CPP_SDLGAMEINPUTINTERFACE

#include "UserInputInterface.h"
#include "SdlApplication.h"
#include "util/InputDialogWindow.h"

#include <SDL.h>
#include <sdlgui/screen.h>

#include <string>

#include <mutex>

namespace hamstersimulator {

/// \brief Convenience wrapper of a SDL application
class SdlGameInputInterface : public mpw::UserInputInterface {
public:

    SdlGameInputInterface(SdlApplication& sdlApplication);

    void onRender(SDL_Renderer& renderer);
    void onEvent(SDL_Event& event);
    bool isActive() const;

    int readInteger(std::string message) override;
    std::string readString(std::string message) override;
    void confirmAlert(std::runtime_error t) override;
    void abort() override;

private:

    void showMessage(const std::string& message, InputDialogWindow::Type type);
    void showMessageForTextInput(const std::string& message, InputDialogWindow::Type type);

    bool active = false;

    const std::unique_ptr<sdlgui::Screen> screen;
    InputDialogWindow* inputDialog;

    SdlApplication& sdlApplication;
    std::condition_variable conditionVariable;

    void wait();
};

}

#endif //HAMSTERSIMULATOR_CPP_SDLGAMEINPUTINTERFACE
