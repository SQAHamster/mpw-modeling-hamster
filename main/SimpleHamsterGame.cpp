#include "SimpleHamsterGame.h"

#include "HamsterApplicationHandler.h"

using namespace hamster;

namespace hamstersimulator {

SimpleHamsterGame::SimpleHamsterGame()
        : game(HamsterGame::create()), paule(*game->getTerritory()->getDefaultHamster()) {
    initializeGame();
    game->startGamePaused();
}

void SimpleHamsterGame::initializeGame() {
    try {
        loadTerritoryFromResourceFile("resources/" + DEFAULT_HAMSTER_TERRITORY);
    } catch (std::exception& e) {
        throw std::runtime_error("failed to load the default territory: " + std::string(e.what()));
    }
}

void SimpleHamsterGame::startGame() {
    game->startGame();
}

void SimpleHamsterGame::doRun() {
    displayInNewGameWindow();
}

void SimpleHamsterGame::loadTerritoryFromResourceFile(const std::string& resourceFilePath) {
    try {
        game->hardReset();
        TerritoryLoader::initializeFor(*game)->loadFromResourceFile(resourceFilePath);
    } catch (std::exception& e) {
        throw std::runtime_error("failed to load the territory '" + resourceFilePath + "' :" + std::string(e.what()));
    }
}

void SimpleHamsterGame::displayInNewGameWindow() {
    HamsterApplicationHandler applicationHandler(game, [&]() {
        try {
            run();
        } catch (framework::GameAbortedException& e) {
            // End this game
        } catch (std::exception& e) {
            this->game->confirmAlert(e);
            throw e;
        }
        this->game->stopGame();
    });

    SdlApplication application(getWindowTitle(), applicationHandler);
    application.initialize(SCREEN_WIDTH, SCREEN_HEIGHT);

    application.runApplication();
}

std::string SimpleHamsterGame::getWindowTitle() {
    return "Simple Hamster Game";
}

}
