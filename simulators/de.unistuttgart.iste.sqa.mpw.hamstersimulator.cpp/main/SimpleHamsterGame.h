#ifndef DE_UNISTUTTGART_ISTE_SQA_MPW_HAMSTERSIMULATOR_CPP_SIMPLEHAMSTERGAME_H
#define DE_UNISTUTTGART_ISTE_SQA_MPW_HAMSTERSIMULATOR_CPP_SIMPLEHAMSTERGAME_H

#include "Hamster.h"
#include "Territory.h"
#include "HamsterGame.h"

#include <string>
#include <exception>
#include <stdexcept>
#include <utility>

namespace hamstersimulator {

const int SCREEN_WIDTH = 700;
const int SCREEN_HEIGHT = 400;

class SimpleHamsterGame {

private:

    const std::string DEFAULT_HAMSTER_TERRITORY = "/territories/example01.ter";

public:
    template<typename T>
    static void createInstance() {
        T program;
        program.doRun();
    }

protected:

    /**
     * The game object of this simple game. Can be used to start, stop, reset,
     * or display the game.
     */
    const std::shared_ptr<hamster::HamsterGame> game;

    /**
     * Variable inherited to child classes containing the default hamster
     * which is named hamster here. Intentionally, no getter or setter is used
     * as they are introduced only after lecture 2.
     */
    hamster::Hamster& paule;

public:
    /**
     * Initialized a simple hamster game by loading a default territory
     * and setting protected references to contain hamster and
     * the game.
     */
    SimpleHamsterGame();

protected:
    void initializeGame();

public:
    /**
     * Method to start the execution of a hamster game and handle any exceptions happening
     * while running.
     */
    void doRun();

protected:

    /**
     * Predefined hamster method designed to be overridden in subclass.
     * Put the hamster code into this method. This parent class version
     * is empty, so that the hamster does not do anything by default.
     */
    virtual void run() = 0;


    /**
     * Displays the hamster game in a new game window
     */
    void displayInNewGameWindow();
};

}

#endif //DE_UNISTUTTGART_ISTE_SQA_MPW_HAMSTERSIMULATOR_CPP_SIMPLEHAMSTERGAME_H
