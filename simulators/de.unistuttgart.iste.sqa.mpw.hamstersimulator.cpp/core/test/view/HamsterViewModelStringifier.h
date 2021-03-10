#ifndef DE_UNISTUTTGART_ISTE_SQA_MPW_HAMSTERSIMULATOR_CPP_HAMSTERVIEWMODELSTRINGIFIER_H
#define DE_UNISTUTTGART_ISTE_SQA_MPW_HAMSTERSIMULATOR_CPP_HAMSTERVIEWMODELSTRINGIFIER_H

#include "GameViewModel.h"
#include "ViewModelRow.h"
#include "ViewModelCell.h"
#include "ViewModelCellLayer.h"
#include "ViewModelLogEntry.h"

#include <unordered_map>

namespace viewmodel {

/**
 * Helper class to represent the view-model in a string representation.
 *
 * With {@link HamsterViewModelStringifier::maxCharsPerCell} the width of a cell in characters is specified.
 * Also, {@link HamsterViewModelStringifier::imageCharsMapping} defines a mapping from a symbolic image name to
 * a character sequence, e.g. "4Grain" -> " 4*". Cells are further separated by '|'.
 */
class HamsterViewModelStringifier {
public:

    HamsterViewModelStringifier(const std::unordered_map<std::string, std::string>& imageCharsMapping,
                                int maxCharsPerCell);

    std::string territoryToExpectationString(const GameViewModel& viewModel);

    static std::string logToString(const GameViewModel& viewModel);

    static std::string buttonBarToExpectationString(const GameViewModel& viewModel);

private:

    static std::string trimHamsterColor(const std::string& key);
    const std::string& getImageCharMapping(const std::string& key) const;

    std::string rowToString(const GameViewModel& viewModel, int y) const;
    std::string cellToString(const ViewModelCell& cell) const;
    static std::string buttonToString(const std::string& name, bool enabled);

    const std::unordered_map<std::string, std::string>& imageCharsMapping;
    const int maxCharsPerCell;
};

}

#endif //DE_UNISTUTTGART_ISTE_SQA_MPW_HAMSTERSIMULATOR_CPP_HAMSTERVIEWMODELSTRINGIFIER_H
