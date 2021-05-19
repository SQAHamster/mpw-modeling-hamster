#include "SimpleHamsterGame.h"

using namespace hamster;

class Example01 : public hamstersimulator::SimpleHamsterGame {
protected:
    void run() override;
};

void Example01::run() {
    paule.move();
    paule.move();
    paule.pickGrain();
    paule.turnLeft();
    paule.turnLeft();
    paule.move();
    paule.move();
    paule.putGrain();
    paule.turnLeft();
    paule.turnLeft();
    paule.move();
}

int main() {
    hamstersimulator::SimpleHamsterGame::createInstance<Example01>();
    return 0;
}

