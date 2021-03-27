#ifndef DE_UNISTUTTGART_ISTE_SQA_MPW_HAMSTERSIMULATOR_CPP_SPEEDSLIDERCONTROL_H
#define DE_UNISTUTTGART_ISTE_SQA_MPW_HAMSTERSIMULATOR_CPP_SPEEDSLIDERCONTROL_H

#include <sdlgui/screen.h>
#include <sdlgui/window.h>
#include <sdlgui/slider.h>

#include "HamsterView.h"

namespace hamstersimulator {

class SpeedSliderControl : public sdlgui::Window {
private:

    sdlgui::Slider* sliderControl;

public:

    explicit SpeedSliderControl(sdlgui::Screen& screen);

    void bindToSpeed(const viewmodel::GameViewModel& viewModel, viewmodel::GameViewInput& viewInput);

private:

    static float speedToSliderValue(double speed);
    static double sliderValueToSpeed(float value);
};

}

#endif //DE_UNISTUTTGART_ISTE_SQA_MPW_HAMSTERSIMULATOR_CPP_SPEEDSLIDERCONTROL_H
