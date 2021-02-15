#include <HamsterCore.h>
#include <HamsterView.h>

#include "SdlApplication.h"
#include "HamsterApplicationHandler.h"
#include <string>

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
        auto paule = game->getTerritory()->getDefaultHamster();

        int a = paule->readNumber("Hallo nummer");
        auto text = paule->readString("Hallo string");
        paule->write("Hallo! " + std::to_string(a) + ", " + text);

        paule->move();
        paule->move();
        paule->pickGrain();
        paule->turnLeft();
        paule->turnLeft();
        paule->move();
        paule->move();
        paule->putGrain();
        paule->turnLeft();
        paule->turnLeft();
        paule->move();
    });

    SdlApplication application("Example 01", applicationHandler);
    application.initialize(SCREEN_WIDTH, SCREEN_HEIGHT);

    application.runApplication();

    return 0;
}

