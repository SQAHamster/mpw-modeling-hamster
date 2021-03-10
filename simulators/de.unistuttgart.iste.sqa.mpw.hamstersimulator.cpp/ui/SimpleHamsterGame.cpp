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
        TerritoryLoader::initializeFor(*game)->loadFromResourceFile("resources/" + DEFAULT_HAMSTER_TERRITORY);
        game->hardReset();
    } catch (std::exception& e) {
        throw std::runtime_error("failed to load the default territory: " + std::string(e.what()));
    }
}

void SimpleHamsterGame::doRun() {
    displayInNewGameWindow();
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

    SdlApplication application(typeid(this).name(), applicationHandler);
    application.initialize(SCREEN_WIDTH, SCREEN_HEIGHT);

    application.runApplication();
}

}
