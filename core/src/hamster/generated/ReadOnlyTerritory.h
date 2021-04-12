/*
 * This file is generated. Do not change it manually.
 */

#ifndef DE_UNISTUTTGART_HAMSTER_READONLYTERRITORY_H
#define DE_UNISTUTTGART_HAMSTER_READONLYTERRITORY_H

#include <memory>
#include <string>
#include <list>
#include <unordered_set>
#include "ObservableProperties.h"
#include "ObservableListProperties.h"
#include "SimpleListProperties.h"
#include "Entity.h"
#include "Size.h"
#include "Location.h"

namespace mpw {
class Tile;
}
namespace mpw {
class TileContent;
}
namespace hamster {
class ConcreteTerritory;
}
namespace hamster {
class ReadOnlyHamster;
}

namespace hamster {

class ReadOnlyTerritory: public virtual basetypes::Entity {

public:

	virtual ~ReadOnlyTerritory() = default;

	/// \brief returns a shared_ptr of type ReadOnlyTerritory which shares ownership of *this
	std::shared_ptr<ReadOnlyTerritory> shared_from_this() {
		return std::dynamic_pointer_cast < ReadOnlyTerritory
				> (basetypes::Entity::shared_from_this());
	}
	/// \brief returns a shared_ptr of const type ReadOnlyTerritory which shares ownership of *this
	std::shared_ptr<const ReadOnlyTerritory> shared_from_this() const {
		return std::dynamic_pointer_cast<const ReadOnlyTerritory>(
				basetypes::Entity::shared_from_this());
	}

	virtual framework::ObjectListView<mpw::Tile>& getTiles() noexcept = 0;
	virtual const framework::ObjectListView<mpw::Tile>& getTiles() const noexcept = 0;
	virtual framework::ObservableListProperty<mpw::Tile>& tilesProperty() noexcept = 0;
	virtual const framework::ObservableListProperty<mpw::Tile>& tilesProperty() const noexcept = 0;

	virtual framework::ObjectListView<mpw::TileContent>& getTileContents() noexcept = 0;
	virtual const framework::ObjectListView<mpw::TileContent>& getTileContents() const noexcept = 0;
	virtual framework::ObservableListProperty<mpw::TileContent>& tileContentsProperty() noexcept = 0;
	virtual const framework::ObservableListProperty<mpw::TileContent>& tileContentsProperty() const noexcept = 0;

	virtual mpw::Size getStageSize() noexcept = 0;
	virtual mpw::Size getStageSize() const noexcept = 0;
	virtual framework::ObservablePrimitiveProperty<mpw::Size>& stageSizeProperty() noexcept = 0;
	virtual const framework::ObservablePrimitiveProperty<mpw::Size>& stageSizeProperty() const noexcept = 0;

	/**
	 * For a given location, return the internal tile object.
	 */
	virtual std::shared_ptr<const mpw::Tile> getTileAt(
			mpw::Location location) const noexcept = 0;

	/**
	 * Return the size of the current territory. From the size you can retrieve the number of rows and colums.
	 */
	virtual mpw::Size getTerritorySize() const noexcept = 0;

	/**
	 * For a given location, tests whether the location is inside the bound of the territory.
	 */
	virtual bool isLocationInTerritory(mpw::Location location) const noexcept = 0;

	virtual std::shared_ptr<hamster::ReadOnlyHamster> getReadOnlyDefaultHamster() noexcept = 0;

};

}

#endif //DE_UNISTUTTGART_HAMSTER_READONLYTERRITORY_H

