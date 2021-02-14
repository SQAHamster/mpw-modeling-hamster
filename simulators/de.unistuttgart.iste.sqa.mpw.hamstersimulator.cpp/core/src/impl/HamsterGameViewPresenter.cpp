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

namespace viewmodel
{

// TODO remove listeners on removement of relating objects

HamsterGameViewPresenter::HamsterGameViewPresenter(std::shared_ptr<hamster::HamsterGame> game)
    : inherited(game)
    , game(std::move(game))
{
    territorySize = this->game->getTerritory()->getTerritorySize();
}

const mpw::Size& HamsterGameViewPresenter::getStageSizeFromConcreteStage()
{
    return territorySize;
}

const framework::ObservableListProperty<mpw::Tile>& HamsterGameViewPresenter::getTilesPropertyFromConcreteStage()
{
    return game->getTerritory()->getInternalTerritory()->tilesProperty();
}

void HamsterGameViewPresenter::onSetTileNodeAtForCell(ViewModelCell& cell, const mpw::Tile& tile)
{
    configureWallImageView(cell, tile);
    configureGrainImageView(cell, tile);
    for (std::shared_ptr<ReadOnlyHamster> hamster : getHamstersOfTile(tile))
    {
        configureHamsterImageView(cell, *hamster);
    }
}

void HamsterGameViewPresenter::configureGrainImageView(ViewModelCell& cell, const Tile& tile)
{
    auto grainLayer = std::make_shared<ViewModelCellLayer>();
    refreshGrainLayer(*grainLayer, tile);

    cell.addToLayers(grainLayer);
}

void HamsterGameViewPresenter::refreshGrainLayer(ViewModelCellLayer& layer, const mpw::Tile& tile)
{
    size_t grainCount = getGrainOfTile(tile).size();
    layer.setVisible(grainCount > 0);
    if (grainCount <= 12)
    {
        layer.setImageName(std::to_string(grainCount) + "Corn32");
    }
    else
    {
        layer.setImageName("12PlusCorn32");
    }
}

void HamsterGameViewPresenter::configureWallImageView(ViewModelCell& cell, const Tile& tile)
{
    auto wallLayer = std::make_shared<ViewModelCellLayer>();
    wallLayer->setImageName("Wall32");
    refreshWallLayer(*wallLayer, tile);

    cell.addToLayers(wallLayer);
}

void HamsterGameViewPresenter::refreshWallLayer(ViewModelCellLayer& layer, const Tile& tile)
{
    layer.setVisible(!getWallsOfTile(tile).empty());
}

void HamsterGameViewPresenter::configureHamsterImageView(ViewModelCell& cell, const ReadOnlyHamster& hamster)
{
    updateColorMap();

    auto& nonConstHamster = const_cast<ReadOnlyHamster&>(hamster);
    // TODO const-correctness: adapt after migrate generator
    auto hamsterLayer = std::make_shared<ViewModelCellLayer>();
    std::string colorName = HamsterColors::toColorName(hamsterToColorMap[&hamster]);
    hamsterLayer->setImageName("Hamster32" + colorName);

    changedHamsterDirectionListenerIds[&hamster] = nonConstHamster.directionProperty().addListener(
        [this, &nonConstHamster, hamsterLayer](Direction oldValue, Direction newValue)
        {
            auto lock = getSemaphore().lock();
            refreshHamsterLayer(*hamsterLayer, nonConstHamster);
        });
    refreshHamsterLayer(*hamsterLayer, nonConstHamster);

    cell.addToLayers(hamsterLayer);
}

void HamsterGameViewPresenter::refreshHamsterLayer(ViewModelCellLayer& layer, hamster::ReadOnlyHamster& hamster)
{
    layer.setVisible(hamster.getCurrentTile() != nullptr);
    if (hamster.getCurrentTile() == nullptr)
    {
        return;
    }
    layer.setRotation(getRotationForDirection(hamster.getDirection()));
}

std::list<std::shared_ptr<hamster::ReadOnlyHamster>> HamsterGameViewPresenter::getHamstersOfTile(const Tile& tile)
{
    return type_select<hamster::ReadOnlyHamster>(const_cast<Tile&>(tile).getContents());
}

std::list<std::shared_ptr<hamster::Wall>> HamsterGameViewPresenter::getWallsOfTile(const Tile& tile)
{
    return type_select<hamster::Wall>(const_cast<Tile&>(tile).getContents());
}

std::list<std::shared_ptr<hamster::Grain>> HamsterGameViewPresenter::getGrainOfTile(const Tile& tile)
{
    return type_select<hamster::Grain>(const_cast<Tile&>(tile).getContents());
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
    // TODO const-correctness: adapt after migrate generator
    Actor* actor = const_cast<LogEntry&>(entry).getActor().get();
    auto iter = hamsterToColorMap.find(actor);
    if (iter != hamsterToColorMap.end()) {
        return (*iter).second;
    }
    return inherited::getColorForLogEntry(entry);
}

}