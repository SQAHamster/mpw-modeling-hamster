/*
 * This file is generated. Do not change it manually.
 */

#ifndef DE_UNISTUTTGART_HAMSTER_CONCRETEHAMSTER_H
#define DE_UNISTUTTGART_HAMSTER_CONCRETEHAMSTER_H

#include <memory>
#include <string>
#include <list>
#include <unordered_set>
#include "ObservableProperties.h"
#include "ObservableListProperties.h"
#include "ObjectListView.hpp"
#include "Actor.h"
#include "GameHamster.h"
#include "EditorHamster.h"
#include "Grain.h"
#include "Direction.h"
#include "Location.h"
#include "Size.h"

#include "InitHamsterCommandParameters.h"
#include "MoveCommandParameters.h"
#include "PickGrainCommandParameters.h"
#include "PutGrainCommandParameters.h"
#include "TurnLeftCommandParameters.h"
#include "WriteCommandParameters.h"

namespace mpw {
class Tile;
}
namespace mpw {
class Stage;
}
namespace mpw {
class TileContent;
}
namespace hamster {
class Wall;
}
namespace hamster {
class GameTerritory;
}
namespace hamster {
class ConcreteTerritory;
}

namespace hamster {

/**
 * Class for Hamster in the Hamster Simulator. This class allows to initialize
 * Hamsters, command Hamsters through their territory and query their state.
 * 
 * By deriving from Actor, a Hamster represents a TileContent which has a link to the parent Stage.
 */
class ConcreteHamster: public mpw::Actor,
		public virtual hamster::GameHamster,
		public virtual hamster::EditorHamster {

private:

	using inherited = Actor;

	framework::ObservableObjectReferenceListProperty<Grain> grains;
	/// \brief internal lookup for grains
	std::unordered_set<hamster::Grain*> grainsLookup;

public:

	ConcreteHamster();

	/// \brief returns a shared_ptr of type ConcreteHamster which shares ownership of *this
	std::shared_ptr<ConcreteHamster> shared_from_this() {
		return std::dynamic_pointer_cast < ConcreteHamster
				> (inherited::shared_from_this());
	}
	/// \brief returns a shared_ptr of const type ConcreteHamster which shares ownership of *this
	std::shared_ptr<const ConcreteHamster> shared_from_this() const {
		return std::dynamic_pointer_cast<const ConcreteHamster>(
				inherited::shared_from_this());
	}

	bool grainAvailable() const noexcept override;

private:

	bool helper_GrainAvailable_currentTile_result0_contents_type_selectGrain_not_empty() const noexcept;

public:

	bool frontIsClear() const noexcept override;

private:

	bool helper_FrontIsClear_currentTile_result0_east_result1_contents_type_selectWall_is_empty() const noexcept;

	bool helper_FrontIsClear_currentTile_result0_north_result1_contents_type_selectWall_is_empty() const noexcept;

	bool helper_FrontIsClear_currentTile_result0_west_result1_contents_type_selectWall_is_empty() const noexcept;

	bool helper_FrontIsClear_currentTile_result0_south_result1_contents_type_selectWall_is_empty() const noexcept;

public:

	mpw::Location getLocation() const noexcept override;

private:

	mpw::Location helper_GetLocation_currentTile_result0_location() const noexcept;

public:

	bool mouthEmpty() const noexcept override;

	void initHamster(commands::InitHamsterCommandParameters &parameters)
			override;

	void move(commands::MoveCommandParameters &parameters) override;

	void pickGrain(commands::PickGrainCommandParameters &parameters) override;

	void putGrain(commands::PutGrainCommandParameters &parameters) override;

	void turnLeft(commands::TurnLeftCommandParameters &parameters) override;

	void write(commands::WriteCommandParameters &parameters) override;

	framework::ObservableListProperty<hamster::Grain>& grainsProperty() noexcept
			override;
	const framework::ObservableListProperty<hamster::Grain>& grainsProperty() const noexcept
			override;

	framework::ObjectListView<hamster::Grain>& getGrains() noexcept override;
	const framework::ObjectListView<hamster::Grain>& getGrains() const noexcept
			override;

	virtual void addToGrains(std::shared_ptr<hamster::Grain> grain) noexcept;
	virtual void removeFromGrains(
			std::shared_ptr<hamster::Grain> grain) noexcept;
	virtual void clearGrains() noexcept;

	framework::ObservableObjectProperty<mpw::Tile>& currentTileProperty() noexcept
			override {
		return inherited::currentTileProperty();
	}
	const framework::ObservableObjectProperty<mpw::Tile>& currentTileProperty() const noexcept
			override {
		return inherited::currentTileProperty();
	}

	std::shared_ptr<mpw::Tile> getCurrentTile() noexcept override {
		return inherited::getCurrentTile();
	}
	std::shared_ptr<const mpw::Tile> getCurrentTile() const noexcept override {
		return inherited::getCurrentTile();
	}

	framework::ObservableObjectProperty<mpw::Stage>& stageProperty() noexcept
			override {
		return inherited::stageProperty();
	}
	const framework::ObservableObjectProperty<mpw::Stage>& stageProperty() const noexcept
			override {
		return inherited::stageProperty();
	}

	std::shared_ptr<mpw::Stage> getStage() noexcept override {
		return inherited::getStage();
	}
	std::shared_ptr<const mpw::Stage> getStage() const noexcept override {
		return inherited::getStage();
	}

	framework::ObservablePrimitiveProperty<mpw::Direction>& directionProperty() noexcept
			override {
		return inherited::directionProperty();
	}
	const framework::ObservablePrimitiveProperty<mpw::Direction>& directionProperty() const noexcept
			override {
		return inherited::directionProperty();
	}

	mpw::Direction getDirection() noexcept override {
		return inherited::getDirection();
	}
	mpw::Direction getDirection() const noexcept override {
		return inherited::getDirection();
	}

public:

	virtual ~ConcreteHamster() = default;

	static constexpr unsigned cFeatureKeyGrains = 4;
	using Actor::cFeatureKeyCurrentTile;
	using Actor::cFeatureKeyStage;
	using Actor::cFeatureKeyDirection;

	void setProperty(unsigned featureKey, Any value) override;
	void addToCollection(unsigned featureKey, EntityReference reference)
			override;
	void removeFromCollection(unsigned featureKey, EntityReference reference)
			override;

};

}

#endif //DE_UNISTUTTGART_HAMSTER_CONCRETEHAMSTER_H

