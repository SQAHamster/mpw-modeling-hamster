#ifndef DE_UNISTUTTGART_HAMSTER_HamsterGameViewPresenter_H
#define DE_UNISTUTTGART_HAMSTER_HamsterGameViewPresenter_H

#include "GameViewPresenterBase.h"

#include "HamsterGame.h"
#include "Tile.h"
#include "Wall.h"
#include "Grain.h"
#include "ReadOnlyHamster.h"

#include <unordered_map>

namespace viewmodel {

class HamsterGameViewPresenter : public GameViewPresenterBase {
private:
    using inherited = GameViewPresenterBase;

public:

    explicit HamsterGameViewPresenter(std::shared_ptr<hamster::HamsterGame> game);

protected:


    const framework::ObservablePrimitiveProperty<mpw::Size>& getStageSizeFromConcreteStage() override;

    const framework::ObservableListProperty<mpw::Tile>& getTilesPropertyFromConcreteStage() override;

    void onSetTileNodeAtForCell(ViewModelCell& cell, const mpw::Tile& tile) override;

    Color getColorForLogEntry(const mpw::LogEntry& entry) const override;

private:

    void configureGrainImageView(ViewModelCell& cell, const mpw::Tile& tile);
    void refreshGrainLayer(ViewModelCellLayer& layer, const mpw::Tile& tile);

    void configureWallImageView(ViewModelCell& cell, const mpw::Tile& tile);
    void refreshWallLayer(ViewModelCellLayer& layer, const mpw::Tile& tile);

    void configureHamsterImageView(ViewModelCell& cell, const hamster::ReadOnlyHamster& hamster);
    void refreshHamsterLayer(ViewModelCellLayer& layer, const hamster::ReadOnlyHamster& hamster);
    void addHamsterDirectionListener(std::shared_ptr<ViewModelCellLayer> hamsterLayer, const hamster::ReadOnlyHamster& hamster);

    void updateColorMap();

    static std::list<std::shared_ptr<const hamster::ReadOnlyHamster>> getHamstersOfTile(const mpw::Tile& tile);
    static std::list<std::shared_ptr<const hamster::Wall>> getWallsOfTile(const mpw::Tile& tile);
    static std::list<std::shared_ptr<const hamster::Grain>> getGrainOfTile(const mpw::Tile& tile);

    const std::shared_ptr<hamster::HamsterGame> game;
    std::unordered_map<const basetypes::Entity*, Color> hamsterToColorMap;

    std::unordered_map<const hamster::ReadOnlyHamster*, unsigned int> changedHamsterDirectionListenerIds;
};

}

#endif //DE_UNISTUTTGART_HAMSTER_HamsterGameViewPresenter_H
