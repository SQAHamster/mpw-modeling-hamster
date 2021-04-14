#include "HamsterGameViewPresenter.h"

#include "Territory.h"
#include "GameTerritory.h"
#include "GameLog.h"
#include "CommandStack.h"
#include "GamePerformance.h"
#include "ReadOnlyHamster.h"
#include "Actor.h"

#include "ViewModelCellLayer.h"
#include "HamsterColors.h"

#include "CollectionHelpers.hpp"
#include <utility>

using namespace mpw;
using namespace hamster;
using namespace collectionhelpers;
using namespace framework;

namespace viewmodel {

// TODO remove listeners on removement of relating objects

HamsterGameViewPresenter::HamsterGameViewPresenter(std::shared_ptr<hamster::HamsterGame> game)
        : inherited(game), game(std::move(game)) {
}

const ObservablePrimitiveProperty<mpw::Size>& HamsterGameViewPresenter::getStageSizeFromConcreteStage() {
    return this->game->getTerritory()->getInternalTerritory()->stageSizeProperty();
}

const framework::ObservableListProperty<mpw::Tile>& HamsterGameViewPresenter::getTilesPropertyFromConcreteStage() {
    return game->getTerritory()->getInternalTerritory()->tilesProperty();
}

void HamsterGameViewPresenter::onSetTileNodeAtForCell(ViewModelCell& cell, const mpw::Tile& tile) {
    configureWallImageView(cell, tile);
    configureGrainImageView(cell, tile);
    for (std::shared_ptr<const ReadOnlyHamster> hamster : getHamstersOfTile(tile)) {
        configureHamsterImageView(cell, *hamster);
    }
}

void HamsterGameViewPresenter::configureGrainImageView(ViewModelCell& cell, const Tile& tile) {
    auto grainLayer = std::make_shared<ViewModelCellLayer>();
    refreshGrainLayer(*grainLayer, tile);

    cell.addToLayers(grainLayer);
}

void HamsterGameViewPresenter::refreshGrainLayer(ViewModelCellLayer& layer, const mpw::Tile& tile) {
    size_t grainCount = getGrainOfTile(tile).size();
    layer.setVisible(grainCount > 0);
    if (grainCount <= 12) {
        layer.setImageName(std::to_string(grainCount) + "Corn32");
    } else {
        layer.setImageName("12PlusCorn32");
    }
}

void HamsterGameViewPresenter::configureWallImageView(ViewModelCell& cell, const Tile& tile) {
    auto wallLayer = std::make_shared<ViewModelCellLayer>();
    wallLayer->setImageName("Wall32");
    refreshWallLayer(*wallLayer, tile);

    cell.addToLayers(wallLayer);
}

void HamsterGameViewPresenter::refreshWallLayer(ViewModelCellLayer& layer, const Tile& tile) {
    layer.setVisible(!getWallsOfTile(tile).empty());
}

void HamsterGameViewPresenter::configureHamsterImageView(ViewModelCell& cell, const ReadOnlyHamster& hamster) {
    updateColorMap();

    std::shared_ptr<ViewModelCellLayer> hamsterLayer = std::make_shared<ViewModelCellLayer>();
    std::string colorName = HamsterColors::toColorName(hamsterToColorMap[&hamster]);
    hamsterLayer->setImageName("Hamster32" + colorName);

    addHamsterDirectionListener(hamsterLayer, hamster);
    refreshHamsterLayer(*hamsterLayer, hamster);

    cell.addToLayers(hamsterLayer);
}

/*
 * Adds a listener for the change of the direction, to also update the layers if the hamster turns left.
 * Note: Since onSetTileNodeAtForCell() is called every time the contents of a tile changes, a Hamster might
 * be configured multiple times. Avoid, that multiple direction listeners are attached.
 */
void HamsterGameViewPresenter::addHamsterDirectionListener(std::shared_ptr<ViewModelCellLayer> hamsterLayer, const ReadOnlyHamster& hamster) {
    auto directionChangeListenerIterator = changedHamsterDirectionListenerIds.find(&hamster);
    if (directionChangeListenerIterator != changedHamsterDirectionListenerIds.end()) {
        changedHamsterDirectionListenerIds.erase(directionChangeListenerIterator);
    }
    changedHamsterDirectionListenerIds[&hamster] = hamster.directionProperty().addListener(
            [this, &hamster, hamsterLayer](Direction oldValue, Direction newValue) {
                auto lock = getSemaphore().lock();
                refreshHamsterLayer(*hamsterLayer, hamster);
            });
}

void HamsterGameViewPresenter::refreshHamsterLayer(ViewModelCellLayer& layer, const hamster::ReadOnlyHamster& hamster) {
    layer.setVisible(hamster.getCurrentTile() != nullptr);
    if (hamster.getCurrentTile() == nullptr) {
        return;
    }
    layer.setRotation(getRotationForDirection(hamster.getDirection()));
}

std::list<std::shared_ptr<const hamster::ReadOnlyHamster>> HamsterGameViewPresenter::getHamstersOfTile(const Tile& tile) {
    return type_select<hamster::ReadOnlyHamster>(tile.getContents());
}

std::list<std::shared_ptr<const hamster::Wall>> HamsterGameViewPresenter::getWallsOfTile(const Tile& tile) {
    return type_select<hamster::Wall>(tile.getContents());
}

std::list<std::shared_ptr<const hamster::Grain>> HamsterGameViewPresenter::getGrainOfTile(const Tile& tile) {
    return type_select<hamster::Grain>(tile.getContents());
}

void HamsterGameViewPresenter::updateColorMap() {
    auto territory = game->getTerritory();
    auto& tileContents = territory->getInternalTerritory()->getTileContents();
    auto hamsters = collectionhelpers::type_select<ReadOnlyHamster>(tileContents);

    for (auto& hamster : hamsters) {
        if (hamsterToColorMap.find(hamster.get()) == hamsterToColorMap.end()) {
            Color color = HamsterColors::getColorForNthHamster(hamsterToColorMap.size());
            hamsterToColorMap[hamster.get()] = color;
        }
    }
}

Color HamsterGameViewPresenter::getColorForLogEntry(const LogEntry& entry) const {
    auto actor = entry.getActor();
    auto iter = hamsterToColorMap.find(actor.get());
    if (iter != hamsterToColorMap.end()) {
        return (*iter).second;
    }
    return inherited::getColorForLogEntry(entry);
}

}
