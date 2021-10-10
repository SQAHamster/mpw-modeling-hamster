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
    /**
     * Initialized a simple hamster game by loading a default territory.
     * This resets the game if it was already started. After the territory was loaded, the game is
     * in mode INITIALIZING. To start the game, game.startGame() should be called.
     */
    void initializeGame();

    /**
     * Convenient method to start the current game.
     * The game has to be in mode INITIALIZING.
     */
    void startGame();

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
     * Loads the Territory from a resources file.
     * Only resource paths relative to the binary output are allowed. E.g. the fileName "/territory.ter" represents the
     * file territory.ter in the binary output directory
     * This resets the game if it was already started. After the territory was loaded, the game is
     * in mode INITIALIZING. To start the game, game.startGame() should be called
     *
     * @param fileName An absolute path to the resource file.
     * @throws std::runtime_error if fileName is no valid resource path
     *                            or if the file was not found
     */
    void loadTerritoryFromResourceFile(const std::string& resourceFilePath);


    /**
     * Displays the hamster game in a new game window
     */
    void displayInNewGameWindow();

    /**
     * @return the window title of the simulator.
     */
    virtual std::string getWindowTitle();
};

}

#endif //DE_UNISTUTTGART_ISTE_SQA_MPW_HAMSTERSIMULATOR_CPP_SIMPLEHAMSTERGAME_H
