#ifndef DE_UNISTUTTGART_ISTE_SQA_MPW_HAMSTERSIMULATOR_CPP_HAMSTERCOLORS_H
#define DE_UNISTUTTGART_ISTE_SQA_MPW_HAMSTERSIMULATOR_CPP_HAMSTERCOLORS_H

#include "Color.h"
#include <vector>
#include <string>

namespace viewmodel {
class HamsterColors {
public:
    static Color getColorForNthHamster(int number);

    static std::string toColorName(viewmodel::Color color);

private:

    static std::vector<Color> hamsterColors;

};
}

#endif //DE_UNISTUTTGART_ISTE_SQA_MPW_HAMSTERSIMULATOR_CPP_HAMSTERCOLORS_H
