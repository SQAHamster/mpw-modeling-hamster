#include "HamsterViewModelStringifier.h"

#include "CollectionHelpers.hpp"

#include <algorithm>

namespace viewmodel {

HamsterViewModelStringifier::HamsterViewModelStringifier(
        const std::unordered_map<std::string, std::string>& imageCharsMapping, int maxCharsPerCell)
    : imageCharsMapping(imageCharsMapping)
    , maxCharsPerCell(maxCharsPerCell)
{
}

std::string HamsterViewModelStringifier::territoryToExpectationString(const GameViewModel& viewModel) {
    auto& nonConstViewModel = const_cast<GameViewModel&>(viewModel); // TODO const-correctness: adapt after migrate generator
    std::string actual;
    int height = nonConstViewModel.getSize().getRowCount();
    for (int y = 0; y < height; y++) {
        std::string rowString = rowToString(viewModel, y);
        actual.append(rowString);
        actual.append("\n");
    }
    return actual;
}

std::string HamsterViewModelStringifier::rowToString(const GameViewModel& viewModel, int y) const {
    auto& nonConstViewModel = const_cast<GameViewModel&>(viewModel); // TODO const-correctness: adapt after migrate generator
    std::string result = "|";
    int width = nonConstViewModel.getSize().getColumnCount();
    for (int x = 0; x < width; x++) {
        auto cell = nonConstViewModel.getCellAt(y, x);
        result.append(cellToString(*cell));
        result.append("|");
    }
    return result;
}

std::string HamsterViewModelStringifier::cellToString(const ViewModelCell& cell) const {
    auto& nonConstCell = const_cast<ViewModelCell&>(cell); // TODO const-correctness: adapt after migrate generator
    std::string result;
    for (const auto& layer : nonConstCell.getLayers()) {
        auto& nonConstLayer = const_cast<ViewModelCellLayer&>(layer);
        if (nonConstLayer.getVisible()) {
            std::string key = nonConstLayer.getImageName();
            key = trimHamsterColor(key);
            int rotation = nonConstLayer.getRotation();
            if (rotation != 0) {
                key.append("[");
                key.append(std::to_string(rotation));
                key.append("]");
            }
            result.append(getImageCharMapping(key));
        }
    }
    int length = static_cast<int>(result.length());
    int spaces = std::max(0, maxCharsPerCell - length);
    for (size_t i = 0; i < spaces; i++) {
        result.append(" ");
    }
    return result;
}

std::string HamsterViewModelStringifier::logToString(const GameViewModel& viewModel) {
    auto& nonConstViewModel = const_cast<GameViewModel&>(viewModel); // TODO const-correctness: adapt after migrate generator
    std::string actual;
    auto& logEntries = nonConstViewModel.getLogEntries();
    for (auto& entry : logEntries) {
        actual.append(entry.getMessage());
        actual.append("\n");
    }
    return actual;
}

const std::string& HamsterViewModelStringifier::getImageCharMapping(const std::string& key) const {
    auto iter = imageCharsMapping.find(key);
    return (*iter).second;
}

std::string HamsterViewModelStringifier::trimHamsterColor(const std::string& key) {
    if (key.find("Hamster32") == 0) {
        return "Hamster32";
    }
    return key;
}

std::string HamsterViewModelStringifier::buttonBarToExpectationString(const GameViewModel& viewModel) {
    auto& nonConstViewModel = const_cast<GameViewModel&>(viewModel); // TODO const-correctness: adapt after migrate generator
    std::string actual;
    actual.append(buttonToString("play", nonConstViewModel.getPlayButtonEnabled()));
    actual.append(" ");
    actual.append(buttonToString("pause", nonConstViewModel.getPauseButtonEnabled()));
    actual.append(" ");
    actual.append(buttonToString("undo", nonConstViewModel.getUndoButtonEnabled()));
    actual.append(" ");
    actual.append(buttonToString("redo", nonConstViewModel.getRedoButtonEnabled()));
    return actual;
}

std::string HamsterViewModelStringifier::buttonToString(const std::string& name, bool enabled) {
    if (enabled) {
        return "[" + name + "]";
    }
    return "/" + name + "/";
}

}