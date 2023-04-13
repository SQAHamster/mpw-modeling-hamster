/*
 * This file is generated. Do not change it manually.
 */

#ifndef DE_UNISTUTTGART_HAMSTER_CONCRETETERRITORY_H
#define DE_UNISTUTTGART_HAMSTER_CONCRETETERRITORY_H

#include <memory>
#include <string>
#include "Stage.h"
#include "GameTerritory.h"
#include "EditorTerritory.h"
#include "Size.h"
#include "Location.h"
#include "Direction.h"

#include "AddGrainsToTileCommandParameters.h"
#include "AddWallToTileCommandParameters.h"
#include "ClearTileCommandParameters.h"
#include "InitDefaultHamsterCommandParameters.h"
#include "InitTerritoryCommandParameters.h"

namespace hamster {
class ConcreteHamster;
}
namespace mpw {
class Tile;
}
namespace mpw {
class TileContent;
}
namespace hamster {
class Grain;
}
namespace hamster {
class Wall;
}
namespace mpw {
class Stage;
}
namespace hamster {
class ReadOnlyHamster;
}
namespace hamster {
class GameHamster;
}
namespace hamster {
class EditorHamster;
}

namespace hamster {

/**
 * The territory is a Stage which represents territories for hamsters. Territories
 * are rectangular areas with width and height composed out of territory
 * tiles. Tiles again can contain hamster objects, grain objects, or walls.
 */
class ConcreteTerritory: public mpw::Stage,
		public virtual hamster::GameTerritory,
		public virtual hamster::EditorTerritory {

private:

	using inherited = Stage;

	/**
	 * Reference to the default hamster of this territory.
	 */
	std::shared_ptr<hamster::ConcreteHamster> defaultHamster;

public:

	ConcreteTerritory();

	/// \brief returns a shared_ptr of type ConcreteTerritory which shares ownership of *this
	std::shared_ptr<ConcreteTerritory> shared_from_this() {
		return std::dynamic_pointer_cast<ConcreteTerritory>(
				inherited::shared_from_this());
	}
	/// \brief returns a shared_ptr of const type ConcreteTerritory which shares ownership of *this
	std::shared_ptr<const ConcreteTerritory> shared_from_this() const {
		return std::dynamic_pointer_cast<const ConcreteTerritory>(
				inherited::shared_from_this());
	}

	mpw::Size getTerritorySize() const noexcept override;

	std::shared_ptr<const mpw::Tile> getTileAt(
			mpw::Location location) const noexcept override;

	bool isLocationInTerritory(mpw::Location location) const noexcept override;

	void addGrainsToTile(commands::AddGrainsToTileCommandParameters &parameters)
			override;

	void addWallToTile(commands::AddWallToTileCommandParameters &parameters)
			override;

	void clearTile(commands::ClearTileCommandParameters &parameters) override;

	void initDefaultHamster(
			commands::InitDefaultHamsterCommandParameters &parameters) override;

	void initTerritory(commands::InitTerritoryCommandParameters &parameters)
			override;

	virtual std::shared_ptr<hamster::ConcreteHamster> getDefaultHamster() noexcept;
	virtual std::shared_ptr<const hamster::ConcreteHamster> getDefaultHamster() const noexcept;

	framework::ObservableListProperty<mpw::Tile>& tilesProperty() noexcept
			override {
		return inherited::tilesProperty();
	}
	const framework::ObservableListProperty<mpw::Tile>& tilesProperty() const noexcept
			override {
		return inherited::tilesProperty();
	}

	framework::ObjectListView<mpw::Tile>& getTiles() noexcept override {
		return inherited::getTiles();
	}
	const framework::ObjectListView<mpw::Tile>& getTiles() const noexcept
			override {
		return inherited::getTiles();
	}

	framework::ObservableListProperty<mpw::TileContent>& tileContentsProperty() noexcept
			override {
		return inherited::tileContentsProperty();
	}
	const framework::ObservableListProperty<mpw::TileContent>& tileContentsProperty() const noexcept
			override {
		return inherited::tileContentsProperty();
	}

	framework::ObjectListView<mpw::TileContent>& getTileContents() noexcept
			override {
		return inherited::getTileContents();
	}
	const framework::ObjectListView<mpw::TileContent>& getTileContents() const noexcept
			override {
		return inherited::getTileContents();
	}

	framework::ObservablePrimitiveProperty<mpw::Size>& stageSizeProperty() noexcept
			override {
		return inherited::stageSizeProperty();
	}
	const framework::ObservablePrimitiveProperty<mpw::Size>& stageSizeProperty() const noexcept
			override {
		return inherited::stageSizeProperty();
	}

	mpw::Size getStageSize() noexcept override {
		return inherited::getStageSize();
	}
	mpw::Size getStageSize() const noexcept override {
		return inherited::getStageSize();
	}

public:

	virtual ~ConcreteTerritory() = default;

	std::shared_ptr<hamster::ReadOnlyHamster> getReadOnlyDefaultHamster() noexcept
			override;
	std::shared_ptr<const hamster::ReadOnlyHamster> getReadOnlyDefaultHamster() const noexcept
			override;
	std::shared_ptr<hamster::GameHamster> getGameDefaultHamster() noexcept
			override;
	std::shared_ptr<const hamster::GameHamster> getGameDefaultHamster() const noexcept
			override;
	std::shared_ptr<hamster::EditorHamster> getEditorDefaultHamster() noexcept
			override;
	std::shared_ptr<const hamster::EditorHamster> getEditorDefaultHamster() const noexcept
			override;

	static constexpr unsigned cFeatureKeyDefaultHamster = 4;
	using Stage::cFeatureKeyTiles;
	using Stage::cFeatureKeyTileContents;
	using Stage::cFeatureKeyStageSize;

	void setProperty(unsigned featureKey, Any value) override;
	void addToCollection(unsigned featureKey, EntityReference reference)
			override;
	void removeFromCollection(unsigned featureKey, EntityReference reference)
			override;

};

}

#endif //DE_UNISTUTTGART_HAMSTER_CONCRETETERRITORY_H

