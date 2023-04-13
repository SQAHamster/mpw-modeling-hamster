#include "gtest/gtest.h"

#include "Hamster.h"
#include "Territory.h"
#include "Tile.h"
#include "Grain.h"
#include "ConcreteHamster.h"
#include "GameTerritory.h"
#include "Stage.h"
#include "GameLog.h"
#include "LogEntry.h"
#include "CommandConstraintException.h"

#include "util/GameStringifier.h"
#include "util/TestUtils.h"

#include <utility>
#include <vector>
#include <string>
#include <TerritoryBuilder.h>

using namespace mpw;
using namespace hamster;
using namespace framework;
using namespace util;

/**
 * Tests for game commands on the facade layer, which are using the {@link GameStringifier} to create
 * simple string based representations.
 * @note use 'NO-LINT' comment at tests to suppress a warning caused by TEST_F
 */
class HamsterCommandTest : public testing::Test {
private:
    std::shared_ptr<HamsterGame> game{};
    std::shared_ptr<Hamster> sut{};

public:

    void withTerritory(const std::string& map);
    std::shared_ptr<TerritoryBuilder> withTerritoryBuilder(const std::string& map);

    void initNewHamster(Location location, Direction direction);
    void removeFromStage();
    static Location locationOf(int x, int y);
    void andGrainsInMouth(int count);
    void start();
    void turnLeft();
    void move();
    void pickGrain();
    void putGrain();
    void write(std::string message);

    void assertTerritory(const std::string& expected);
    void assertFrontIsClear();
    void assertFrontIsNotClear();
    void assertGrainsInMouth(int expected);
    void assertGrainsOnTerritory(const std::string& expected);
    void assertGameLog(const std::vector<std::string>& expectedStrings);
};

//<editor-fold desc="Feature: move">

TEST_F(HamsterCommandTest, givenHamsterEast_whenMove_thenMovedToRight) { /* NOLINT */
    withTerritory(
            "  #;"
            "> #;"
            "  #;");

    move();

    assertTerritory(
            "  #;"
            " >#;"
            "  #;");
}


TEST_F(HamsterCommandTest, givenHamsterNorth_whenMove_thenMovedToNorth) { /* NOLINT */
    withTerritory(
            "  #;"
            "^ #;"
            "  #;");

    move();

    assertTerritory(
            "^ #;"
            "  #;"
            "  #;");
}


TEST_F(HamsterCommandTest, givenHamsterSouth_whenMove_thenMovedToSouth) { /* NOLINT */
    withTerritory(
            "  #;"
            "v #;"
            "  #;");

    move();

    assertTerritory(
            "  #;"
            "  #;"
            "v #;");
}


TEST_F(HamsterCommandTest, givenHamsterWest_whenMove_thenMovedToWest) { /* NOLINT */
    withTerritory(
            "  #;"
            " <#;"
            "  #;");

    move();

    assertTerritory(
            "  #;"
            "< #;"
            "  #;");
}
//</editor-fold>

//<editor-fold desc="Feature: pick/put grains">


static const int oneGrain = 1;

TEST_F(HamsterCommandTest, givenHamsterWithGrainAvailable_whenPickGrain_thenPickedGrain) { /* NOLINT */
    withTerritoryBuilder(">;")
            ->addGrainsToTile(locationOf(0, 0), oneGrain);
    start();

    pickGrain();

    assertGrainsInMouth(1);
    assertGrainsOnTerritory("0;");
}


TEST_F(HamsterCommandTest, givenHamsterWithGrainInMouth_whenPutGrain_thenPutGrainOnTile) { /* NOLINT */
    withTerritory(">;");
    andGrainsInMouth(1);

    putGrain();

    assertGrainsInMouth(0);
    assertGrainsOnTerritory("1;");
}


TEST_F(HamsterCommandTest, givenHamsterWithNoGrainAvailable_whenPickGrain_ThenExceptionIsThrown) { /* NOLINT */
    withTerritory(">;");

    TestUtils::assertThrows(typeid(CommandConstraintException), [&]() {
        pickGrain();
    });
}


TEST_F(HamsterCommandTest, givenHamsterWithEmptyMouth_whenPutGrain_ThenExceptionIsThrown) { /* NOLINT */
    withTerritory(">;");

    TestUtils::assertThrows(typeid(CommandConstraintException), [&]() {
        putGrain();
    });
}

//</editor-fold>

//<editor-fold desc="Feature: turnLeft">

TEST_F(HamsterCommandTest, givenHamsterEast_whenTurnLeft_thenDirectionIsNorth) { /* NOLINT */
    withTerritory(">;");
    turnLeft();
    assertTerritory("^;");
}

TEST_F(HamsterCommandTest, givenHamsterNorth_whenTurnLeft_thenDirectionIsWest) { /* NOLINT */
    withTerritory("^;");
    turnLeft();
    assertTerritory("<;");
}

TEST_F(HamsterCommandTest, givenHamsterWest_whenTurnLeft_thenDirectionIsSouth) { /* NOLINT */
    withTerritory("<;");
    turnLeft();
    assertTerritory("v;");
}

TEST_F(HamsterCommandTest, givenHamsterSouth_whenTurnLeft_thenDirectionIsEast) { /* NOLINT */
    withTerritory("v;");
    turnLeft();
    assertTerritory(">;");
}
//</editor-fold>

//<editor-fold desc="Feature: frontIsClear">

TEST_F(HamsterCommandTest, givenHamsterInAnyDirection_andFrontCellIsEmpty_whenCheckFrontIsClear_thenIsTrue) { /* NOLINT */
    withTerritory(" <;");
    assertFrontIsClear();

    withTerritory("> ;");
    assertFrontIsClear();

    withTerritory(" ;^;");
    assertFrontIsClear();

    withTerritory("v; ;");
    assertFrontIsClear();
}


TEST_F(HamsterCommandTest, givenHamsterInAnyDirection_andFrontCellIsWall_whenCheckFrontIsNotClear_thenIsTrue) { /* NOLINT */
    withTerritory("#<;");
    assertFrontIsNotClear();

    withTerritory(">#;");
    assertFrontIsNotClear();

    withTerritory("#;^;");
    assertFrontIsNotClear();

    withTerritory("v;#;");
    assertFrontIsNotClear();
}


TEST_F(HamsterCommandTest, givenHamsterInAnyDirection_andFrontCellIsGrain_whenCheckFrontIsClear_thenIsTrue) { /* NOLINT */
    withTerritory("*<;");
    assertFrontIsClear();

    withTerritory(">*;");
    assertFrontIsClear();

    withTerritory("*;^;");
    assertFrontIsClear();

    withTerritory("v;*;");
    assertFrontIsClear();
}


TEST_F(HamsterCommandTest, givenHamsterInAnyDirection_andFrontCellIsEndOfMap_whenCheckFrontIsNotClear_thenIsTrue) { /* NOLINT */
    withTerritory("<;");
    assertFrontIsNotClear();

    withTerritory(">;");
    assertFrontIsNotClear();

    withTerritory("^;");
    assertFrontIsNotClear();

    withTerritory("v;");
    assertFrontIsNotClear();
}


TEST_F(HamsterCommandTest, givenHamsterBeforeWall_whenMove_ThenExceptionIsThrown) { /* NOLINT */
    withTerritory("#<;");

    TestUtils::assertThrows(typeid(CommandConstraintException), [&]() {
        move();
    });
}

// test of invariant "isInitialized"
TEST_F(HamsterCommandTest, givenHamsterWithCurrentTileIsNull_whenMove_ThenExceptionIsThrown) { /* NOLINT */
    withTerritory(" <;");
    removeFromStage();

    TestUtils::assertThrows(typeid(CommandConstraintException), [&]() {
        move();
    });
}

//</editor-fold>

//<editor-fold desc="Feature: gameLog">

TEST_F(HamsterCommandTest, givenHamster_whenExecuteAndCommand_thenGameLogIsAdded) { /* NOLINT */
    withTerritory(" *;");

    initNewHamster(locationOf(0, 0), Direction::EAST);
    move();
    pickGrain();
    putGrain();
    turnLeft();
    write("Custom Message");

    assertGameLog( {
            "Init Hamster",
            "Move",
            "Pick Grain",
            "Put Grain",
            "Turn Left",
            "Custom Message" });
}

//</editor-fold>


//<editor-fold desc="helpers">

void HamsterCommandTest::withTerritory(const std::string& map) {
    game = GameStringifier::createFromStringStarted(map);
    sut = game->getTerritory()->getDefaultHamster();
}

std::shared_ptr<TerritoryBuilder> HamsterCommandTest::withTerritoryBuilder(const std::string& map) {
    game = GameStringifier::createFromString(map);
    sut = game->getTerritory()->getDefaultHamster();
    return std::make_shared<TerritoryBuilder>(game);
}

void HamsterCommandTest::initNewHamster(Location location, Direction direction) {
    sut = std::make_shared<Hamster>(game->getTerritory(), location, direction, 0);
}

void HamsterCommandTest::removeFromStage() {
    // use internal class to be able to set an "invalid state" where the stage is not set
    auto internalHamster = dynamic_cast<ConcreteHamster*>(sut->getInternalHamster().get());
    internalHamster->setStage(nullptr);
}

Location HamsterCommandTest::locationOf(int x, int y) {
    return Location::from(x, y);
}

void HamsterCommandTest::andGrainsInMouth(int count) {
    auto internalHamster = dynamic_cast<ConcreteHamster*>(sut->getInternalHamster().get());
    auto stage = internalHamster->getStage();
    for (int i = 0; i < count; i++) {
        auto grain = std::make_shared<Grain>();
        stage->addToTileContents(grain);
        internalHamster->addToGrains(grain);
    }
}

void HamsterCommandTest::turnLeft() {
    sut->turnLeft();
}

void HamsterCommandTest::start() {
    game->startGame();
}

void HamsterCommandTest::move() {
    sut->move();
}

void HamsterCommandTest::pickGrain() {
    sut->pickGrain();
}

void HamsterCommandTest::putGrain() {
    sut->putGrain();
}

void HamsterCommandTest::write(std::string message) {
    sut->write(std::move(message));
}

void HamsterCommandTest::assertTerritory(const std::string& expected) {
    std::string actual = GameStringifier::toString(*game);
    EXPECT_EQ(expected, actual);
}

void HamsterCommandTest::assertFrontIsClear() {
    EXPECT_TRUE(sut->frontIsClear());
}

void HamsterCommandTest::assertFrontIsNotClear() {
    EXPECT_FALSE(sut->frontIsClear());
}

void HamsterCommandTest::assertGrainsInMouth(int expected) {
    auto internalHamster = sut->getInternalHamster();
    auto actual = internalHamster->getGrains().size();
    EXPECT_EQ(expected, actual);
}

void HamsterCommandTest::assertGrainsOnTerritory(const std::string& expected) {
    std::string actual = GameStringifier::grainsOnTerritoryToString(*game);
    EXPECT_EQ(expected, actual);
}

static std::vector<std::string> toMessages(GameLog& log) {
    std::vector<std::string> result;
    for (auto& entry : log.getLogEntries()) {
        result.push_back(entry.getMessage());
    }
    return result;
}

void HamsterCommandTest::assertGameLog(const std::vector<std::string>& expectedStrings) {
    std::string actual = TestUtils::join("|", toMessages(*game->getGameLog()));
    std::string expected = TestUtils::join("|", expectedStrings);
    EXPECT_EQ(expected, actual);
}

//</editor-fold>
