#include <iostream>
#include <memory>
#include <HamsterCore.h>

#include "SdlApplication.h"
#include "HamsterApplicationHandler.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

using namespace hamstersimulator;
using namespace hamster;
using namespace viewmodel;

int main() {
    auto game = HamsterGame::create();
    TerritoryLoader::initializeFor(*game)->loadFromResourceFile("resources/territories/example01.ter");

    HamsterApplicationHandler applicationHandler(game, []() {

    });

    SdlApplication application("Hamstersimulator", applicationHandler);
    application.initialize(SCREEN_WIDTH, SCREEN_HEIGHT);
    application.runApplication();

    return 0;
}

void initHamsterGame() {
    auto game = hamster::HamsterGame::create();
    std::make_shared<hamster::TerritoryBuilder>(game)->initTerritory(4, 4)
            .addGrainsToTile(1, 1, 3)
            .initDefaultHamster(1, 1, mpw::Direction::EAST, 0);
    std::cout << game->getTerritory()->getDefaultHamster()->frontIsClear() << std::endl;
}
