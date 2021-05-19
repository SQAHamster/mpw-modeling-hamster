#include "SdlGameInputInterface.h"

#include <mutex>

using namespace sdlgui;

namespace hamstersimulator {

SdlGameInputInterface::SdlGameInputInterface(Screen& screen)
        : screen(screen), semaphore(0) {
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
        int result = std::stoi(inputDialog->getInputText());
        inputDialog->dispose();
        return result;
    } catch (std::exception& e) {
        return 0;
    }
}

void SdlGameInputInterface::wait() {
    active = true;
    semaphore.acquire();
    active = false;
}

std::string SdlGameInputInterface::readString(std::string message) {
    showMessageForTextInput(message, sdlgui::MessageDialog::Type::Information);
    wait();
    std::string result = inputDialog->getInputText();
    inputDialog->dispose();
    return result;
}

void SdlGameInputInterface::confirmAlert(const std::exception& t) {
    showMessage(t.what(), sdlgui::MessageDialog::Type::Warning);
    wait();
    inputDialog->dispose();
}

void SdlGameInputInterface::showMessageForTextInput(const std::string& message, InputDialogWindow::Type type) {
    showMessage(message, type);
    inputDialog->setInputFieldVisible(true);
}

void SdlGameInputInterface::showMessage(const std::string& message, InputDialogWindow::Type type) {
    inputDialog = &screen.wdg<InputDialogWindow>(MessageDialog::Type::Information, "Message box", message);
    inputDialog->setCallback([&] {
        semaphore.release();
    });
    inputDialog->setInputFieldVisible(false);
}

void SdlGameInputInterface::abort() {
    semaphore.release();
}

}
