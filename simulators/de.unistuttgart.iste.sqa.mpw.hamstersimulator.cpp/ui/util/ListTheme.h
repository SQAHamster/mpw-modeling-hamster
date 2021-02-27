#ifndef DE_UNISTUTTGART_ISTE_SQA_MPW_HAMSTERSIMULATOR_CPP_LISTTHEME_H
#define DE_UNISTUTTGART_ISTE_SQA_MPW_HAMSTERSIMULATOR_CPP_LISTTHEME_H

#include "LightTheme.h"

namespace hamstersimulator {

class ListTheme : public LightTheme {
public:

    explicit ListTheme(SDL_Renderer* context) : LightTheme(context) {
        mWindowHeaderHeight = 0;
        mWindowDropShadowSize = 0;
        mWindowFillFocused = { 255, 255 };
        mWindowFillUnfocused = { 255, 255 };
    }
};

}

#endif //DE_UNISTUTTGART_ISTE_SQA_MPW_HAMSTERSIMULATOR_CPP_LISTTHEME_H
