#include <HamsterCore.h>
#include <HamsterView.h>

#include "SdlApplication.h"
#include "HamsterApplicationHandler.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

using namespace hamstersimulator;
using namespace hamster;

void hamsterProgram() {

}

int main() {
    auto game = HamsterGame::create();
    TerritoryLoader::initializeFor(*game)->loadFromResourceFile("resources/territories/example01.ter");
    
    HamsterApplicationHandler applicationHandler(game, [&]()
    {
        auto& paule = *game->getTerritory()->getDefaultHamster();

        Hamster paula(game->getTerritory(), paule.getLocation(), paule.getDirection(), 1);
        paula.move();
        paula.putGrain();
        paula.move();

        paule.move();
        paule.pickGrain();
        paule.turnLeft();
        paule.turnLeft();
        paule.move();
        paule.putGrain();
    });

    SdlApplication application("Example 02", applicationHandler);
    application.initialize(SCREEN_WIDTH, SCREEN_HEIGHT);

    application.runApplication();

    return 0;
}

