#include "SpeedSliderControl.h"

#include "ControlWindowTheme.h"

using namespace sdlgui;

namespace hamstersimulator {

const double MIN_SPEED = 1.0;
const double MAX_SPEED = 10.0;

SpeedSliderControl::SpeedSliderControl(sdlgui::Screen& screen)
        : Window(&screen, "") {

    setTheme(new ControlWindowTheme(screen.sdlRenderer()));
    setPosition(250, 20);

    sliderControl = &slider();
    sliderControl->withFixedWidth(200);
    withFixedWidth(200);
}

void SpeedSliderControl::bindToSpeed(const viewmodel::GameViewModel& viewModel,
                                     viewmodel::GameViewInput& viewInput) {
    sliderControl->setValue(speedToSliderValue(viewModel.getSpeed()));

    sliderControl->setCallback([&viewInput](float value) {
        viewInput.speedChanged(sliderValueToSpeed(value));
    });

}

float SpeedSliderControl::speedToSliderValue(double speed) {
    return static_cast<float>((speed - MIN_SPEED) / (MAX_SPEED - MIN_SPEED));
}

double SpeedSliderControl::sliderValueToSpeed(float value) {
    return MIN_SPEED + (MAX_SPEED-MIN_SPEED)*value;
}

}
