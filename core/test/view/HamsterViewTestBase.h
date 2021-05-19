#ifndef DE_UNISTUTTGART_ISTE_SQA_MPW_HAMSTERSIMULATOR_CPP_HAMSTERVIEWTESTBASE_H
#define DE_UNISTUTTGART_ISTE_SQA_MPW_HAMSTERSIMULATOR_CPP_HAMSTERVIEWTESTBASE_H

#include <gtest/gtest.h>
#include "HamsterCore.h"

#include "GameViewModel.h"

#include <unordered_map>
#include <GameViewPresenter.h>

class HamsterViewTestBase : public testing::Test {
private:

    int maxCharsPerCell = 4;
    static std::unordered_map<std::string, std::string> characterMap;
    std::shared_ptr<hamster::HamsterGame> game;
    std::shared_ptr<viewmodel::GameViewPresenter> presenter;

protected:

    void SetUp() override;
    void TearDown() override;

    void withTerritory(const std::string& path);
    void initializeOtherTerritory(const std::string& path);
    void createFurtherHamsterAt(mpw::Location location);

    void clickPlay();
    void clickPause();
    void clickUndo();
    void clickRedo();

    void assertTerritory(const std::string& expected);
    void assertLog(const std::string& expected);
    void assertLayersAt(mpw::Location location, const std::vector<std::string>& expectedLayerImageNames);
    void assertButtons(const std::string& expected);

    std::shared_ptr<hamster::Hamster> paule;
    std::shared_ptr<viewmodel::GameViewInput> viewInput;
    std::shared_ptr<viewmodel::GameViewModel> viewModel;

private:

    static void initCharMapping();

    void assertLocationsAreSet();
    void assertSizeIsConsistent();

};


#endif //DE_UNISTUTTGART_ISTE_SQA_MPW_HAMSTERSIMULATOR_CPP_HAMSTERVIEWTESTBASE_H
