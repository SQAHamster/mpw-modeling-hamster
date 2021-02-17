#include "SdlGameInputInterface.h"

#include <mutex>

using namespace sdlgui;

namespace hamstersimulator {

SdlGameInputInterface::SdlGameInputInterface(Screen& screen)
        : screen(screen) {
}

void SdlGameInputInterface::onRender(SDL_Renderer& renderer) {
    screen.drawAll();
}

void SdlGameInputInterface::onEvent(SDL_Event& event) {
    screen.onEvent(event);
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
    std::unique_lock<std::mutex> lock(mutex);
    active = true;
    conditionVariable.wait(lock);
    active = false;
}

std::string SdlGameInputInterface::readString(std::string message) {
    showMessageForTextInput(message, sdlgui::MessageDialog::Type::Information);
    wait();
    return inputDialog->getInputText();
}

void SdlGameInputInterface::confirmAlert(const std::exception& t) {
    showMessage(t.what(), sdlgui::MessageDialog::Type::Warning);
    wait();
}

void SdlGameInputInterface::showMessageForTextInput(const std::string& message, InputDialogWindow::Type type) {
    showMessage(message, type);
    inputDialog->setInputFieldVisible(true);
}

void SdlGameInputInterface::showMessage(const std::string& message, InputDialogWindow::Type type) {
    inputDialog = &screen.wdg<InputDialogWindow>(MessageDialog::Type::Information, "Message box", message);
    inputDialog->setCallback([&] {
        conditionVariable.notify_all();
    });
    inputDialog->setInputFieldVisible(false);
}

void SdlGameInputInterface::abort() {
    conditionVariable.notify_all();
}

}
