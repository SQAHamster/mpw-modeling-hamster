#include "gtest/gtest.h"

#include "HamsterCore.h"
#include "HamsterViewTestBase.h"

#include "view/HamsterViewModelStringifier.h"
#include "util/TestUtils.h"

#include <utility>
#include <vector>
#include <string>

using namespace mpw;
using namespace hamster;
using namespace framework;
using namespace util;

/**
 * Tests on the view-model layer, which are using the {@link viewmodel::HamsterViewModelStringifier} to create
 * string based representations.
 * @note use 'NO-LINT' comment at tests to suppress a warning caused by TEST_F
 */
class HamsterViewModelTest : public HamsterViewTestBase {
private:
public:
};

TEST_F(HamsterViewModelTest, testInit) { /* NOLINT */
    withTerritory("/territories/example01.ter");
    assertTerritory(
            "|####|####|####|####|####|\n"
            "|####|>   |    | 2* |####|\n"
            "|####|####|####|####|####|\n");
    EXPECT_EQ(true, paule->mouthEmpty());
    EXPECT_EQ(true, paule->frontIsClear());
    EXPECT_EQ(false, paule->grainAvailable());
    EXPECT_EQ(Direction::EAST, paule->getDirection());
    EXPECT_EQ(1, paule->getLocation().getRow());
    EXPECT_EQ(1, paule->getLocation().getColumn());
}


TEST_F(HamsterViewModelTest, testMove) { /* NOLINT */
    withTerritory("/territories/example01.ter");
    paule->move();
    assertTerritory(
            "|####|####|####|####|####|\n"
            "|####|    |>   | 2* |####|\n"
            "|####|####|####|####|####|\n");
    EXPECT_EQ(true, paule->mouthEmpty());
    EXPECT_EQ(true, paule->frontIsClear());
    EXPECT_EQ(false, paule->grainAvailable());
    EXPECT_EQ(Direction::EAST, paule->getDirection());
    EXPECT_EQ(1, paule->getLocation().getRow());
    EXPECT_EQ(2, paule->getLocation().getColumn());
}

TEST_F(HamsterViewModelTest, testPickGrain) { /* NOLINT */
    withTerritory("/territories/example01.ter");
    paule->move();
    paule->move();
    paule->pickGrain();
    assertTerritory(
            "|####|####|####|####|####|\n"
            "|####|    |    | 1*>|####|\n"
            "|####|####|####|####|####|\n");
    EXPECT_EQ(false, paule->mouthEmpty());
    EXPECT_EQ(false, paule->frontIsClear());
    EXPECT_EQ(true, paule->grainAvailable());
    EXPECT_EQ(Direction::EAST, paule->getDirection());
    EXPECT_EQ(1, paule->getLocation().getRow());
    EXPECT_EQ(3, paule->getLocation().getColumn());
}

TEST_F(HamsterViewModelTest, testPickGrainAndPutGrain) { /* NOLINT */
    withTerritory("/territories/example01.ter");
    paule->move();
    paule->move();
    paule->pickGrain();
    paule->putGrain();
    assertTerritory(
            "|####|####|####|####|####|\n"
            "|####|    |    | 2*>|####|\n"
            "|####|####|####|####|####|\n");
    EXPECT_EQ(true, paule->mouthEmpty());
    EXPECT_EQ(false, paule->frontIsClear());
    EXPECT_EQ(true, paule->grainAvailable());
    EXPECT_EQ(Direction::EAST, paule->getDirection());
    EXPECT_EQ(1, paule->getLocation().getRow());
    EXPECT_EQ(3, paule->getLocation().getColumn());
}

TEST_F(HamsterViewModelTest, testMoveAndRotateAndMove) { /* NOLINT */
    withTerritory("/territories/example01.ter");
    paule->move();
    paule->turnLeft();
    paule->turnLeft();
    paule->move();
    assertTerritory(
            "|####|####|####|####|####|\n"
            "|####|<   |    | 2* |####|\n"
            "|####|####|####|####|####|\n");
    EXPECT_EQ(true, paule->mouthEmpty());
    EXPECT_EQ(false, paule->frontIsClear());
    EXPECT_EQ(false, paule->grainAvailable());
    EXPECT_EQ(Direction::WEST, paule->getDirection());
    EXPECT_EQ(1, paule->getLocation().getRow());
    EXPECT_EQ(1, paule->getLocation().getColumn());
}

TEST_F(HamsterViewModelTest, testInitializeFurtherTerritory) { /* NOLINT */
    withTerritory("/territories/example01.ter");
    initializeOtherTerritory("/territories/example03.ter");
    assertTerritory(
            "|####|####|####|\n"
            "|####|>   |####|\n"
            "|####|    |####|\n"
            "|####| 2* |####|\n"
            "|####|####|####|\n");
    initializeOtherTerritory("/territories/example01.ter");
    assertTerritory(
            "|####|####|####|####|####|\n"
            "|####|>   |    | 2* |####|\n"
            "|####|####|####|####|####|\n");
}

TEST_F(HamsterViewModelTest, testMoveAgainstWall) { /* NOLINT */
    withTerritory("/territories/example01.ter");
    paule->move();
    paule->turnLeft();

    TestUtils::assertThrows(typeid(CommandConstraintException), [&] {
        paule->move();
    });
}

TEST_F(HamsterViewModelTest, testLog) { /* NOLINT */
    withTerritory("/territories/example01.ter");
    paule->move();
    paule->move();
    paule->pickGrain();
    paule->putGrain();
    paule->turnLeft();
    paule->write("Hello");
    assertLog(
            "Move\n"
            "Move\n"
            "Pick Grain\n"
            "Put Grain\n"
            "Turn Left\n"
            "Hello\n");
}

TEST_F(HamsterViewModelTest, testColors) { /* NOLINT */
    withTerritory("/territories/example01.ter");

    const Location& location = Location::from(1, 1);
    for (int i = 0; i < 6; i++) {
        createFurtherHamsterAt(location);
    }
    assertLayersAt(location, {
            "Hamster32Blue",
            "Hamster32Green",
            "Hamster32Yellow",
            "Hamster32Pink",
            "Hamster32Magenta",
            "Hamster32Red",
            "Hamster32Blue"
    });
}

/*
 * [button] means: button is enabled
 * /button/ means: button is disabled
 */
TEST_F(HamsterViewModelTest, testButtonsForModes) { /* NOLINT */
    withTerritory("/territories/example01.ter");
    assertButtons("/play/ [pause] /undo/ /redo/");
    paule->move();
    paule->turnLeft();
    assertButtons("/play/ [pause] /undo/ /redo/");
    clickPause();
    assertButtons("[play] /pause/ [undo] /redo/");
    clickUndo();
    assertButtons("[play] /pause/ [undo] [redo]");
    clickUndo();
    assertButtons("[play] /pause/ /undo/ [redo]");
    clickRedo();
    assertButtons("[play] /pause/ [undo] [redo]");
    clickPlay();
    assertButtons("/play/ [pause] /undo/ /redo/");
    clickPause();
    assertButtons("[play] /pause/ [undo] /redo/");
    assertTerritory(
            "|####|####|####|####|####|\n"
            "|####|    |^   | 2* |####|\n"
            "|####|####|####|####|####|\n");
}
