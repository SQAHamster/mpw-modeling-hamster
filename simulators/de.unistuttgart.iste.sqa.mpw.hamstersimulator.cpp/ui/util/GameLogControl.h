#ifndef DE_UNISTUTTGART_ISTE_SQA_MPW_HAMSTERSIMULATOR_CPP_GAMELOGCONTROL_H
#define DE_UNISTUTTGART_ISTE_SQA_MPW_HAMSTERSIMULATOR_CPP_GAMELOGCONTROL_H

#include <sdlgui/screen.h>
#include <sdlgui/window.h>
#include <sdlgui/vscrollpanel.h>
#include "HamsterView.h"

#include <unordered_map>

namespace hamstersimulator {

class GameLogControl : public sdlgui::Window {
public:

    explicit GameLogControl(sdlgui::Screen& screen);

    void bindToGameLog(const viewmodel::GameViewModel& viewModel);

    void draw(SDL_Renderer* surface) override;

    void performLayout(SDL_Renderer* ctx) override;

private:

    sdlgui::Screen& screen;
    sdlgui::Widget* listPanel;
    sdlgui::VScrollPanel* scrollPanel;

    std::unordered_map<const viewmodel::ViewModelLogEntry*, sdlgui::Widget*> logEntryWidgets;
};

}

#endif //DE_UNISTUTTGART_ISTE_SQA_MPW_HAMSTERSIMULATOR_CPP_GAMELOGCONTROL_H
