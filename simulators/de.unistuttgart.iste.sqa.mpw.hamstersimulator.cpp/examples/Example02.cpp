#include "SimpleHamsterGame.h"

using namespace hamster;

class Example02 : public hamstersimulator::SimpleHamsterGame {
protected:
    void run() override;
};

void Example02::run() {
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
}

int main() {
    hamstersimulator::SimpleHamsterGame::createInstance<Example02>();
    return 0;
}
