#include "HamsterViewTestBase.h"

#include "HamsterGameViewPresenter.h"
#include "UserInputInterfaceFake.h"
#include "HamsterViewModelStringifier.h"

#include <memory>

using namespace hamster;
using namespace viewmodel;

std::unordered_map<std::string, std::string> HamsterViewTestBase::characterMap;

void HamsterViewTestBase::SetUp() {
    initCharMapping();
}

void HamsterViewTestBase::TearDown() {
    game->getPerformance()->abortOrStopGame();
}

void HamsterViewTestBase::withTerritory(const std::string& path) {
    game = HamsterGame::create();
    TerritoryLoader::initializeFor(*game)->loadFromResourceFile("resources" + path);

    game->getPerformance()->setDelayEnabled(false);
    game->startGame();

    auto territory = game->getTerritory();
    paule = territory->getDefaultHamster();

    presenter = std::make_shared<HamsterGameViewPresenter>(game);
    presenter->bind();
    viewInput = presenter;
    viewModel = presenter->getViewModel();

    game->setUserInputInterface(std::make_shared<UserInputInterfaceFake>());
}

void HamsterViewTestBase::initializeOtherTerritory(const std::string& path) {
    game->hardReset();
    TerritoryLoader::initializeFor(*game)->loadFromResourceFile("resources" + path);
}

void HamsterViewTestBase::clickPlay() {
    viewInput->playClicked();
}

void HamsterViewTestBase::clickPause() {
    viewInput->pauseClicked();
}

void HamsterViewTestBase::clickUndo() {
    viewInput->undoClicked();
}

void HamsterViewTestBase::clickRedo() {
    viewInput->redoClicked();
}

void HamsterViewTestBase::assertTerritory(const std::string& expected) {
    std::string actual = HamsterViewModelStringifier(characterMap, maxCharsPerCell).territoryToExpectationString(*viewModel);
    EXPECT_EQ(expected, actual);
    assertLocationsAreSet();
    assertSizeIsConsistent();
}

void HamsterViewTestBase::assertLocationsAreSet() {
    int rowIndex = 0;
    for (auto& row : viewModel->getRows()) {
        int columnIndex = 0;
        for (auto& cell : row.getCells()) {
            EXPECT_EQ(columnIndex, cell.getLocation().getColumn());
            EXPECT_EQ(rowIndex, cell.getLocation().getRow());
            columnIndex++;
        }
        rowIndex++;
    }
}

void HamsterViewTestBase::assertSizeIsConsistent() {
    auto& rows = viewModel->getRows();
    EXPECT_EQ(rows.size(), viewModel->getSize().getRowCount());
    for (auto& row : rows) {
        EXPECT_EQ(row.getCells().size(), viewModel->getSize().getColumnCount());
    }
}

void HamsterViewTestBase::assertLog(const std::string& expected) {
    std::string actual = HamsterViewModelStringifier::logToString(*viewModel);
    EXPECT_EQ(expected, actual);
}

void HamsterViewTestBase::initCharMapping() {
    characterMap["1Corn32"] = " 1*";
    characterMap["2Corn32"] = " 2*";
    characterMap["3Corn32"] = " 3*";
    characterMap["4Corn32"] = " 4*";
    characterMap["5Corn32"] = " 5*";
    characterMap["6Corn32"] = " 6*";
    characterMap["7Corn32"] = " 7*";
    characterMap["8Corn32"] = " 8*";
    characterMap["9Corn32"] = " 9*";
    characterMap["10Corn32"] = "10*";
    characterMap["11Corn32"] = "11*";
    characterMap["12Corn32"] = "12*";
    characterMap["12PlusCorn32"] = "12+";
    characterMap["Hamster32"] = ">";
    characterMap["Hamster32[90]"] = "v";
    characterMap["Hamster32[180]"] = "<";
    characterMap["Hamster32[270]"] = "^";
    characterMap["Wall32"] = "####";
}

void HamsterViewTestBase::createFurtherHamsterAt(mpw::Location location) {
    std::make_shared<Hamster>(game->getTerritory(), location, mpw::Direction::EAST, 0);
}

void HamsterViewTestBase::assertLayersAt(mpw::Location location, const std::vector<std::string>& expectedLayerImageNames) {
    std::string expected = "";
    for (auto& expectedName : expectedLayerImageNames) {
        expected += expectedName + "\n";
    }
    std::string actual = "";
    auto cell = viewModel->getCellAt(location.getRow(), location.getColumn());
    for (auto& layer : cell->getLayers()) {
        if (layer.getVisible()) {
            actual += layer.getImageName() + "\n";
        }
    }
    EXPECT_EQ(expected, actual);
}

void HamsterViewTestBase::assertButtons(const std::string& expected) {
    std::string actual = HamsterViewModelStringifier::buttonBarToExpectationString(*viewModel);
    EXPECT_EQ(expected, actual);
    assertLocationsAreSet();
    assertSizeIsConsistent();
}
