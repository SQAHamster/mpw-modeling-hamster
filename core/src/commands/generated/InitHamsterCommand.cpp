/*
 * This file is generated. Do not change it manually.
 */

#include "InitHamsterCommand.h"

#include "FrameworkAssert.h"
#include "CommandConstraintException.h"
#include "ConcreteHamster.h"
#include "GameLog.h"
#include <stdexcept>

using namespace framework;

namespace commands {

void InitHamsterCommand::execute() {

	/*
	 * the hamster must not be already initialized
	 */

	if ((self->getStage() == nullptr) == false) {
		throw CommandConstraintException(
				"Violation of Precondition: the hamster must not be already initialized");
	}

	/*
	 * grainCount has to be greater than or equal to zero
	 */

	if ((grainCount >= 0) == false) {
		throw CommandConstraintException(
				"Violation of Precondition: grainCount has to be greater than or equal to zero");
	}

	/*
	 * location has to be on territory
	 */

	if ((territory->isLocationInTerritory(location)) == false) {
		throw CommandConstraintException(
				"Violation of Precondition: location has to be on territory");
	}

	if (!internalMainUnit()) {
		throw std::runtime_error(
				"Transformation was not successfully executed: initHamster");
	}
	addGameLog();

	/*
	 * the number of grains must equal the parameter grainCount
	 */

	if ((self->getGrains().size() == grainCount) == false) {
		throw CommandConstraintException(
				"Violation of Postcondition: the number of grains must equal the parameter grainCount");
	}

	/*
	 * the hamster is placed on a tile.
	 */

	if ((self->getStage() != nullptr && self->getCurrentTile() != nullptr)
			== false) {
		throw CommandConstraintException(
				"Violation of ClassInvariant: the hamster is placed on a tile.");
	}

}
bool InitHamsterCommand::internalMainUnit() {

	if (!addToTerritory(territory, location)) {
		return false;
	}
	if (!setProperties(direction)) {
		return false;
	}
	if (!addMultipleGrain(territory, grainCount)) {
		return false;
	}
	return true;

}

bool InitHamsterCommand::setProperties(mpw::Direction initialDirection) {

	// set value type field self.direction := initialDirection
	executeSetEnumProperty(self, hamster::ConcreteHamster::cFeatureKeyDirection,
			self->getDirection(), initialDirection);

	return true;

}

bool InitHamsterCommand::addMultipleGrain(
		std::shared_ptr<hamster::GameTerritory> territory, int grainCount) {

	for (int i = 0; i < static_cast<int>(grainCount); i++) {
		if (!addGrain(territory)) {
			return false;
		}
	}
	return true;

}

bool InitHamsterCommand::addGrain(
		std::shared_ptr<hamster::GameTerritory> territory) {

	// new instance: newGrain:Grain
	std::shared_ptr < hamster::Grain > newGrain = std::make_shared<
			hamster::Grain>();

	// create reference: CREATE self:GameHamster -> grains -> newGrain:Grain
	executeAddReference(self, hamster::ConcreteHamster::cFeatureKeyGrains,
			newGrain);

	// create reference: CREATE territory:GameTerritory -> tileContents -> newGrain:Grain
	executeAddReference(territory,
			hamster::ConcreteTerritory::cFeatureKeyTileContents, newGrain);

	return true;

}

bool InitHamsterCommand::addToTerritory(
		std::shared_ptr<hamster::GameTerritory> territory,
		mpw::Location location) {

	// find new variable from many-reference: territory:GameTerritory -> tiles -> o0:Tile

	std::shared_ptr < mpw::Tile > o0 = addToTerritory_findO0(*territory);
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

	// create reference: CREATE territory:GameTerritory -> tileContents -> self:GameHamster
	executeAddReference(territory,
			hamster::ConcreteTerritory::cFeatureKeyTileContents, self);

	// create reference: CREATE self:GameHamster -> currentTile -> o0:Tile
	executeSetProperty(self, hamster::ConcreteHamster::cFeatureKeyCurrentTile,
			self->getCurrentTile(), o0);

	return true;

}

std::shared_ptr<mpw::Tile> InitHamsterCommand::addToTerritory_findO0(
		hamster::GameTerritory &source) {
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

bool InitHamsterCommand::addGameLog() {

	// new instance: entry:LogEntry
	std::shared_ptr < mpw::LogEntry > entry = std::make_shared<mpw::LogEntry>();

	// set value type field entry.message := 
	executeSetStringProperty(entry, mpw::LogEntry::cFeatureKeyMessage,
			entry->getMessage(), "Init Hamster");

	// create reference: CREATE entry:LogEntry -> actor -> self:GameHamster
	executeSetProperty(entry, mpw::LogEntry::cFeatureKeyActor,
			entry->getActor(), self);

	// create reference: CREATE gameLog:GameLog -> logEntries -> entry:LogEntry
	executeAddReference(gameLog, mpw::GameLog::cFeatureKeyLogEntries, entry);

	return true;

}

}

