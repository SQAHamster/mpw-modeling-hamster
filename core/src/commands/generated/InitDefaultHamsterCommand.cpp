/*
 * This file is generated. Do not change it manually.
 */

#include "InitDefaultHamsterCommand.h"

#include "FrameworkAssert.h"
#include "CommandConstraintException.h"
#include "ConcreteTerritory.h"
#include "GameLog.h"
#include <stdexcept>

using namespace framework;

namespace commands {

void InitDefaultHamsterCommand::execute() {

	/*
	 * grainCount has to be greater than or equal to zero
	 */

	if ((grainCount >= 0) == false) {
		throw CommandConstraintException(
				"Violation of Precondition: grainCount has to be greater than or equal to zero");
	}

	/*
	 * hamster must not be already initialized
	 */

	if ((self->getDefaultHamster()->getStage() == nullptr) == false) {
		throw CommandConstraintException(
				"Violation of Precondition: hamster must not be already initialized");
	}

	/*
	 * location has to be on territory
	 */

	if ((self->isLocationInTerritory(location)) == false) {
		throw CommandConstraintException(
				"Violation of Precondition: location has to be on territory");
	}

	/*
	 * the territory tiles must not be empty
	 */

	if ((self->getTiles().size() > 0) == false) {
		throw CommandConstraintException(
				"Violation of ClassInvariant: the territory tiles must not be empty");
	}

	if (!internalMainUnit()) {
		throw std::runtime_error(
				"Transformation was not successfully executed: initDefaultHamster");
	}

	/*
	 * the number of grains must equal the parameter grainCount
	 */

	if ((self->getDefaultHamster()->getGrains().size() == grainCount)
			== false) {
		throw CommandConstraintException(
				"Violation of Postcondition: the number of grains must equal the parameter grainCount");
	}

	/*
	 * the territory tiles must not be empty
	 */

	if ((self->getTiles().size() > 0) == false) {
		throw CommandConstraintException(
				"Violation of ClassInvariant: the territory tiles must not be empty");
	}

}
bool InitDefaultHamsterCommand::internalMainUnit() {

	if (!addToTerritory(location)) {
		return false;
	}
	if (!setProperties(direction)) {
		return false;
	}
	if (!addMultipleGrain(grainCount)) {
		return false;
	}
	return true;

}

bool InitDefaultHamsterCommand::setProperties(mpw::Direction initialDirection) {

	// new variable from reference: self:EditorTerritory -> defaultHamster -> defaultHamster:EditorHamster

	std::shared_ptr < hamster::EditorHamster > defaultHamster =
			std::dynamic_pointer_cast < hamster::EditorHamster
					> (self->getDefaultHamster());
	if (defaultHamster.get() == nullptr) {
		return false;
	}

	// set value type field defaultHamster.direction := initialDirection
	executeSetEnumProperty(defaultHamster,
			hamster::ConcreteHamster::cFeatureKeyDirection,
			defaultHamster->getDirection(), initialDirection);

	return true;

}

bool InitDefaultHamsterCommand::addMultipleGrain(int grainCount) {

	for (int i = 0; i < static_cast<int>(grainCount); i++) {
		if (!addGrain()) {
			return false;
		}
	}
	return true;

}

bool InitDefaultHamsterCommand::addGrain() {

	// new instance: newGrain:Grain
	std::shared_ptr < hamster::Grain > newGrain = std::make_shared<
			hamster::Grain>();

	// new variable from reference: self:EditorTerritory -> defaultHamster -> defaultHamster:EditorHamster

	std::shared_ptr < hamster::EditorHamster > defaultHamster =
			std::dynamic_pointer_cast < hamster::EditorHamster
					> (self->getDefaultHamster());
	if (defaultHamster.get() == nullptr) {
		return false;
	}

	// create reference: CREATE defaultHamster:EditorHamster -> grains -> newGrain:Grain
	executeAddReference(defaultHamster,
			hamster::ConcreteHamster::cFeatureKeyGrains, newGrain);

	// create reference: CREATE self:EditorTerritory -> tileContents -> newGrain:Grain
	executeAddReference(self,
			hamster::ConcreteTerritory::cFeatureKeyTileContents, newGrain);

	return true;

}

bool InitDefaultHamsterCommand::addToTerritory(mpw::Location location) {

	// new variable from reference: self:EditorTerritory -> defaultHamster -> defaultHamster:EditorHamster

	std::shared_ptr < hamster::EditorHamster > defaultHamster =
			std::dynamic_pointer_cast < hamster::EditorHamster
					> (self->getDefaultHamster());
	if (defaultHamster.get() == nullptr) {
		return false;
	}

	// find new variable from many-reference: self:EditorTerritory -> tiles -> o0:Tile

	std::shared_ptr < mpw::Tile > o0 = addToTerritory_findO0(*self);
	if (o0 == nullptr) {
		return false;
	}

	// new variable from reference: o0:Tile -> location -> o1:Location

	mpw::Location o1 = o0->getLocation();

	// assert condition: o1.row == location.row
	if (o1.getRow() != location.getRow()) {
		return false;
	}

	// assert condition: o1.column == location.column
	if (o1.getColumn() != location.getColumn()) {
		return false;
	}

	// create reference: CREATE self:EditorTerritory -> tileContents -> defaultHamster:EditorHamster
	executeAddReference(self,
			hamster::ConcreteTerritory::cFeatureKeyTileContents,
			defaultHamster);

	// create reference: CREATE defaultHamster:EditorHamster -> currentTile -> o0:Tile
	executeSetProperty(defaultHamster,
			hamster::ConcreteHamster::cFeatureKeyCurrentTile,
			defaultHamster->getCurrentTile(), o0);

	return true;

}

std::shared_ptr<mpw::Tile> InitDefaultHamsterCommand::addToTerritory_findO0(
		hamster::EditorTerritory &source) {
	std::shared_ptr < mpw::Tile > result = nullptr;

	for (auto &o0 : source.getTiles().sharedPointerView()) {

		// reference check: o0: location
		mpw::Location o1 = o0->getLocation();

		// attribute check: o1: row
		if (o1.getRow() != location.getRow()) {
			continue;
		}

		// attribute check: o1: column
		if (o1.getColumn() != location.getColumn()) {
			continue;
		}

		result = o0;
		break;
	}
	return result;
}

}

