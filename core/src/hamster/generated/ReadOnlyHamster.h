/*
 * This file is generated. Do not change it manually.
 */

#ifndef DE_UNISTUTTGART_HAMSTER_READONLYHAMSTER_H
#define DE_UNISTUTTGART_HAMSTER_READONLYHAMSTER_H

#include <memory>
#include <string>
#include <list>
#include <unordered_set>
#include "ObservableProperties.h"
#include "ObservableListProperties.h"
#include "SimpleListProperties.h"
#include "Entity.h"
#include "Direction.h"
#include "Location.h"

namespace mpw {
class Tile;
}
namespace mpw {
class Stage;
}
namespace hamster {
class ConcreteHamster;
}
namespace hamster {
class Grain;
}
namespace hamster {
class Wall;
}
namespace mpw {
class TileContent;
}

namespace hamster {

class ReadOnlyHamster: public virtual basetypes::Entity {

public:

	virtual ~ReadOnlyHamster() = default;

	/// \brief returns a shared_ptr of type ReadOnlyHamster which shares ownership of *this
	std::shared_ptr<ReadOnlyHamster> shared_from_this() {
		return std::dynamic_pointer_cast < ReadOnlyHamster
				> (basetypes::Entity::shared_from_this());
	}
	/// \brief returns a shared_ptr of const type ReadOnlyHamster which shares ownership of *this
	std::shared_ptr<const ReadOnlyHamster> shared_from_this() const {
		return std::dynamic_pointer_cast<const ReadOnlyHamster>(
				basetypes::Entity::shared_from_this());
	}

	virtual std::shared_ptr<mpw::Tile> getCurrentTile() noexcept = 0;
	virtual std::shared_ptr<const mpw::Tile> getCurrentTile() const noexcept = 0;
	virtual framework::ObservableObjectProperty<mpw::Tile>& currentTileProperty() noexcept = 0;
	virtual const framework::ObservableObjectProperty<mpw::Tile>& currentTileProperty() const noexcept = 0;

	virtual std::shared_ptr<mpw::Stage> getStage() noexcept = 0;
	virtual std::shared_ptr<const mpw::Stage> getStage() const noexcept = 0;
	virtual framework::ObservableObjectProperty<mpw::Stage>& stageProperty() noexcept = 0;
	virtual const framework::ObservableObjectProperty<mpw::Stage>& stageProperty() const noexcept = 0;

	/**
	 * Get the current hamster looking direction.
	 */
	virtual mpw::Direction getDirection() noexcept = 0;
	/**
	 * Get the current hamster looking direction.
	 */
	virtual mpw::Direction getDirection() const noexcept = 0;
	virtual framework::ObservablePrimitiveProperty<mpw::Direction>& directionProperty() noexcept = 0;
	virtual const framework::ObservablePrimitiveProperty<mpw::Direction>& directionProperty() const noexcept = 0;

	virtual framework::ObjectListView<hamster::Grain>& getGrains() noexcept = 0;
	virtual const framework::ObjectListView<hamster::Grain>& getGrains() const noexcept = 0;
	virtual framework::ObservableListProperty<hamster::Grain>& grainsProperty() noexcept = 0;
	virtual const framework::ObservableListProperty<hamster::Grain>& grainsProperty() const noexcept = 0;

	/**
	 * Get the current hamster location.
	 */
	virtual mpw::Location getLocation() const noexcept = 0;

	/**
	 * Checks the front of the hamster.
	 */
	virtual bool frontIsClear() const noexcept = 0;

	/**
	 * Checks whether the hamster's mouth is empty or whether it has grains in its mouth.
	 */
	virtual bool mouthEmpty() const noexcept = 0;

	/**
	 * Checks the hamster's current tile for grain.
	 */
	virtual bool grainAvailable() const noexcept = 0;

};

}

#endif //DE_UNISTUTTGART_HAMSTER_READONLYHAMSTER_H

