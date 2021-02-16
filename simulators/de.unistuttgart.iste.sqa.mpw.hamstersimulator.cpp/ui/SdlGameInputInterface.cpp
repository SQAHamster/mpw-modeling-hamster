#include "SdlGameInputInterface.h"

using namespace sdlgui;

namespace hamstersimulator {

static Vector2i GetWindowSize(SDL_Window& window) {
    Vector2i size;
    SDL_GetWindowSize(&window, &size.x, &size.y);
    return size;
}

static std::string GetWindowTitle(SDL_Window& window) {
    return std::string(SDL_GetWindowTitle(&window));
}

SdlGameInputInterface::SdlGameInputInterface(hamstersimulator::SdlApplication& sdlApplication)
        : sdlApplication(sdlApplication),
          screen(std::make_unique<Screen>(&sdlApplication.getWindow(), GetWindowSize(sdlApplication.getWindow()),
                                          GetWindowTitle(sdlApplication.getWindow()), true, true)) {
    screen->performLayout(screen->sdlRenderer());
}

void SdlGameInputInterface::onRender(SDL_Renderer& renderer) {
    screen->drawAll();
}

void SdlGameInputInterface::onEvent(SDL_Event& event) {
    screen->onEvent(event);
}

bool SdlGameInputInterface::isActive() const {
    return active;
}

int SdlGameInputInterface::readInteger(std::string message) {
    showMessageForTextInput(message, sdlgui::MessageDialog::Type::Information);
    inputDialog->setNumeric(true);
    wait();

    try {
        return std::stoi(inputDialog->getInputText());
    } catch (std::exception& e) {
        return 0;
    }
}

void SdlGameInputInterface::wait() {
    std::mutex mutex;
    std::__1::unique_lock<std::mutex> lock(mutex);
    active = true;
    conditionVariable.wait(lock);
    active = false;
}

std::string SdlGameInputInterface::readString(std::string message) {
    showMessageForTextInput(message, sdlgui::MessageDialog::Type::Information);
    wait();
    return inputDialog->getInputText();
}

void SdlGameInputInterface::confirmAlert(std::runtime_error t) {
    showMessage(t.what(), sdlgui::MessageDialog::Type::Warning);
    wait();
}

void SdlGameInputInterface::showMessageForTextInput(const std::string& message, InputDialogWindow::Type type) {
    showMessage(message, type);
    inputDialog->setInputFieldVisible(true);
}

void SdlGameInputInterface::showMessage(const std::string& message, InputDialogWindow::Type type) {
    inputDialog = &screen->wdg<InputDialogWindow>(MessageDialog::Type::Information, "Message box", message);
    inputDialog->setCallback([&] {
        conditionVariable.notify_all();
    });
}

void SdlGameInputInterface::abort() {
    conditionVariable.notify_all();
}

}
