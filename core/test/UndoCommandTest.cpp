#include "gtest/gtest.h"

#include "HamsterCore.h"

#include "util/GameStringifier.h"
#include "util/TestUtils.h"

#include <utility>
#include <vector>
#include <string>

using namespace mpw;
using namespace hamster;
using namespace framework;
using namespace util;

/// \note use 'NO-LINT' comment at tests to suppress a warning caused by TEST_F
class UndoCommandTest : public testing::Test {
public:
    static std::string logToString(HamsterGame& game);
};

//<editor-fold desc="Feature: undo">

TEST_F(UndoCommandTest, testUndo) {
    std::shared_ptr<HamsterGame> game = GameStringifier::createFromString(" >*;"
                                                                          "   ;");
    game->hardReset();
    game->startGame();

    auto hamster = game->getTerritory()->getDefaultHamster();
    hamster->move();

    std::string actual1 = GameStringifier::toString(*game);
    EXPECT_EQ("  >;"
              "   ;", actual1);

    auto commandStack = game->getGameCommandStack();
    commandStack->undo();

    std::string actual = GameStringifier::toString(*game);
    EXPECT_EQ(" >*;"
              "   ;", actual);
}

TEST_F(UndoCommandTest, testUndoAll) { /* NOLINT */
    std::shared_ptr<HamsterGame> game = GameStringifier::createFromString(" >*;"
                                                                          "   ;");
    game->hardReset();
    game->startGame();

    auto hamster = game->getTerritory()->getDefaultHamster();
    hamster->move();
    hamster->pickGrain();

    hamster->turnLeft();
    hamster->turnLeft();
    hamster->turnLeft();

    hamster->move();

    auto commandStack = game->getGameCommandStack();
    commandStack->undo();
    std::string actual = GameStringifier::toString(*game);
    EXPECT_EQ("  v;"
              "   ;", actual);

    commandStack->undoAll();

    actual = GameStringifier::toString(*game);
    EXPECT_EQ(" >*;"
              "   ;", actual);
}

TEST_F(UndoCommandTest, testUndoOfLogs) { /* NOLINT */
    std::shared_ptr<HamsterGame> game = GameStringifier::createFromString(" >*;"
                                                                          "   ;");
    auto commandStack = game->getGameCommandStack();

    game->hardReset();
    game->startGame();

    auto hamster = game->getTerritory()->getDefaultHamster();
    hamster->move();
    hamster->write("text");
    hamster->pickGrain();
    EXPECT_EQ("Move|text|Pick Grain", logToString(*game));

    commandStack->undo();
    EXPECT_EQ("Move|text", logToString(*game));

    commandStack->undo();
    EXPECT_EQ("Move", logToString(*game));
    EXPECT_EQ("  >;"
              "   ;", GameStringifier::toString(*game));

    commandStack->redo();
    EXPECT_EQ("Move|text", logToString(*game));

    commandStack->redo();
    EXPECT_EQ("Move|text|Pick Grain", logToString(*game));
}

std::string UndoCommandTest::logToString(HamsterGame& game) {
    std::string result;
    for (auto& logEntry : game.getGameLog()->getLogEntries()) {
        if (!result.empty()) {
            result += "|";
        }
        result += logEntry.getMessage();
    }
    return result;
}

//</editor-fold>
