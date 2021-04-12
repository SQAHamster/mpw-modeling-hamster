#include "HamsterColors.h"

namespace viewmodel {
std::vector<Color> viewmodel::HamsterColors::hamsterColors = {
        Color::BLUE,
        Color::GREEN,
        Color::YELLOW,
        Color::PINK,
        Color::MAGENTA,
        Color::RED
};

viewmodel::Color viewmodel::HamsterColors::getColorForNthHamster(int number) {
    int index = number % hamsterColors.size();
    return hamsterColors[index];
}

std::string HamsterColors::toColorName(viewmodel::Color color) {
    switch (color) {
        case Color::BLACK:
            return "Black";
        case Color::BLUE:
            return "Blue";
        case Color::GREEN:
            return "Green";
        case Color::YELLOW:
            return "Yellow";
        case Color::PINK:
            return "Pink";
        case Color::MAGENTA:
            return "Magenta";
        case Color::RED:
            return "Red";
    }
    return "?";
}

}
