/*
 * This file is generated. Do not change it manually.
 */

#include "PutGrainCommand.h"

#include "FrameworkAssert.h"
#include "CommandConstraintException.h"
#include "ConcreteHamster.h"
#include "GameLog.h"
#include <stdexcept>

using namespace framework;

namespace commands {

void PutGrainCommand::execute() {

	/*
	 * the hamster has to carry any grain
	 */

	if ((!(self->mouthEmpty())) == false) {
		throw CommandConstraintException(
				"Violation of Precondition: the hamster has to carry any grain");
	}

	/*
	 * the hamster is placed on a tile.
	 */

	if ((self->getStage() != nullptr && self->getCurrentTile() != nullptr)
			== false) {
		throw CommandConstraintException(
				"Violation of ClassInvariant: the hamster is placed on a tile.");
	}

	if (!internalMainUnit()) {
		throw std::runtime_error(
				"Transformation was not successfully executed: putGrain");
	}
	addGameLog();

	/*
	 * the hamster is placed on a tile.
	 */

	if ((self->getStage() != nullptr && self->getCurrentTile() != nullptr)
			== false) {
		throw CommandConstraintException(
				"Violation of ClassInvariant: the hamster is placed on a tile.");
	}

}
bool PutGrainCommand::internalMainUnit() {

	// new variable from reference: self:GameHamster -> currentTile -> position:Tile

	std::shared_ptr < mpw::Tile > position = self->getCurrentTile();
	if (position.get() == nullptr) {
		return false;
	}

	// find new variable from many-reference: self:GameHamster -> grains -> grain:Grain

	std::shared_ptr < hamster::Grain > grain = execute_findGrain(*self);
	if (grain == nullptr) {
		return false;
	}

	// remove reference: DELETE self:GameHamster -> grains -> grain:Grain

	executeRemoveReference(self, hamster::ConcreteHamster::cFeatureKeyGrains,
			grain);

	// create reference: CREATE position:Tile -> contents -> grain:Grain
	executeAddReference(position, mpw::Tile::cFeatureKeyContents, grain);

	return true;

}

std::shared_ptr<hamster::Grain> PutGrainCommand::execute_findGrain(
		hamster::GameHamster &source) {
	std::shared_ptr < hamster::Grain > result = nullptr;

	for (auto &grain : source.getGrains().sharedPointerView()) {

		result = grain;
		break;
	}
	return result;
}

bool PutGrainCommand::addGameLog() {

	// new instance: entry:LogEntry
	std::shared_ptr < mpw::LogEntry > entry = std::make_shared<mpw::LogEntry>();

	// set value type field entry.message := 
	executeSetStringProperty(entry, mpw::LogEntry::cFeatureKeyMessage,
			entry->getMessage(), "Put Grain");

	// create reference: CREATE entry:LogEntry -> actor -> self:GameHamster
	executeSetProperty(entry, mpw::LogEntry::cFeatureKeyActor,
			entry->getActor(), self);

	// create reference: CREATE gameLog:GameLog -> logEntries -> entry:LogEntry
	executeAddReference(gameLog, mpw::GameLog::cFeatureKeyLogEntries, entry);

	return true;

}

}

