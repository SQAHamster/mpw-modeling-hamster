/*
 * This file is generated. Do not change it manually.
 */

#include "PickGrainCommand.h"

#include "FrameworkAssert.h"
#include "CommandConstraintException.h"
#include "ConcreteHamster.h"
#include "GameLog.h"
#include "CollectionHelpers.hpp"
#include <stdexcept>

using namespace framework;

namespace commands {

void PickGrainCommand::execute() {

	/*
	 * there have to be grains available on the hamster's tile
	 */

	if ((self->grainAvailable()) == false) {
		throw CommandConstraintException(
				"Violation of Precondition: there have to be grains available on the hamster's tile");
	}

	/*
	 * the hamster is placed on a tile.
	 */

	if ((self->getStage() != nullptr && self->getCurrentTile() != nullptr)
			== false) {
		throw CommandConstraintException(
				"Violation of ClassInvariant: the hamster is placed on a tile.");
	}

	int oldValue0 = self->getGrains().size();

	if (!internalMainUnit()) {
		throw std::runtime_error(
				"Transformation was not successfully executed: pickGrain");
	}
	addGameLog();

	/*
	 * the number of grains has to be increased by one
	 */

	if ((self->getGrains().size() == oldValue0 + 1) == false) {
		throw CommandConstraintException(
				"Violation of Postcondition: the number of grains has to be increased by one");
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
bool PickGrainCommand::internalMainUnit() {

	// new variable from reference: self:GameHamster -> currentTile -> position:Tile

	std::shared_ptr < mpw::Tile > position = self->getCurrentTile();
	if (position.get() == nullptr) {
		return false;
	}

	// find new variable from many-reference: position:Tile -> contents -> grain:Grain

	std::shared_ptr < hamster::Grain > grain = execute_findGrain(*position);
	if (grain == nullptr) {
		return false;
	}

	// remove reference: DELETE position:Tile -> contents -> grain:Grain

	executeRemoveReference(position, mpw::Tile::cFeatureKeyContents, grain);

	// create reference: CREATE self:GameHamster -> grains -> grain:Grain
	executeAddReference(self, hamster::ConcreteHamster::cFeatureKeyGrains,
			grain);

	return true;

}

std::shared_ptr<hamster::Grain> PickGrainCommand::execute_findGrain(
		mpw::Tile &source) {
	std::shared_ptr < hamster::Grain > result = nullptr;

	for (auto &grainTileContent : source.getContents().sharedPointerView()) {

		std::shared_ptr < hamster::Grain > grain = std::dynamic_pointer_cast
				< hamster::Grain > (grainTileContent);
		if (grain == nullptr) {
			continue;
		}

		result = grain;
		break;
	}
	return result;
}

bool PickGrainCommand::addGameLog() {

	// new instance: entry:LogEntry
	std::shared_ptr < mpw::LogEntry > entry = std::make_shared<mpw::LogEntry>();

	// set value type field entry.message := 
	executeSetStringProperty(entry, mpw::LogEntry::cFeatureKeyMessage,
			entry->getMessage(), "Pick Grain");

	// create reference: CREATE entry:LogEntry -> actor -> self:GameHamster
	executeSetProperty(entry, mpw::LogEntry::cFeatureKeyActor,
			entry->getActor(), self);

	// create reference: CREATE gameLog:GameLog -> logEntries -> entry:LogEntry
	executeAddReference(gameLog, mpw::GameLog::cFeatureKeyLogEntries, entry);

	return true;

}

}

