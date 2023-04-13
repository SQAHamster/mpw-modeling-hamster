#include "SimpleHamsterGame.h"

using namespace hamster;

class Example03 : public hamstersimulator::SimpleHamsterGame {
protected:
    void run() override;
    void turnRight();
};

void Example03::run() {
    loadTerritoryFromResourceFile("resources/territories/example03.ter");
    startGame();

    turnRight();
    paule.move();
}

void Example03::turnRight() {
    paule.turnLeft();
    paule.turnLeft();
    paule.turnLeft();
}

int main() {
    hamstersimulator::SimpleHamsterGame::createInstance<Example03>();
    return 0;
}
