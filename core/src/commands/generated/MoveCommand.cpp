/*
 * This file is generated. Do not change it manually.
 */

#include "MoveCommand.h"

#include "FrameworkAssert.h"
#include "CommandConstraintException.h"
#include "ConcreteHamster.h"
#include "GameLog.h"
#include "CollectionHelpers.hpp"
#include <stdexcept>

using namespace framework;

namespace commands {

void MoveCommand::execute() {

	/*
	 * Hamster front must not be blocked or outside territory
	 */

	if ((self->frontIsClear()) == false) {
		throw CommandConstraintException(
				"Violation of Precondition: Hamster front must not be blocked or outside territory");
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
				"Transformation was not successfully executed: move");
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
bool MoveCommand::internalMainUnit() {

	if (moveNorth()) {
		return true;
	} else if (moveSouth()) {
		return true;
	} else if (moveWest()) {
		return true;
	} else if (moveEast()) {
		return true;
	}

	return false;

}

bool MoveCommand::moveNorth() {

	// new variable from reference: self:GameHamster -> currentTile -> current:Tile

	std::shared_ptr < mpw::Tile > current = self->getCurrentTile();
	if (current.get() == nullptr) {
		return false;
	}

	// new variable from reference: current:Tile -> north -> front:Tile

	std::shared_ptr < mpw::Tile > front = current->getNorth();
	if (front.get() == nullptr) {
		return false;
	}

	// assert condition: self.direction == NORTH
	if (self->getDirection() != mpw::Direction::NORTH) {
		return false;
	}

	// remove reference: DELETE self:GameHamster -> currentTile -> current:Tile

	executeSetProperty(self, hamster::ConcreteHamster::cFeatureKeyCurrentTile,
			self->getCurrentTile(), nullptr);

	// create reference: CREATE self:GameHamster -> currentTile -> front:Tile
	executeSetProperty(self, hamster::ConcreteHamster::cFeatureKeyCurrentTile,
			self->getCurrentTile(), front);

	return true;

}

bool MoveCommand::moveSouth() {

	// new variable from reference: self:GameHamster -> currentTile -> current:Tile

	std::shared_ptr < mpw::Tile > current = self->getCurrentTile();
	if (current.get() == nullptr) {
		return false;
	}

	// new variable from reference: current:Tile -> south -> front:Tile

	std::shared_ptr < mpw::Tile > front = current->getSouth();
	if (front.get() == nullptr) {
		return false;
	}

	// assert condition: self.direction == SOUTH
	if (self->getDirection() != mpw::Direction::SOUTH) {
		return false;
	}

	// remove reference: DELETE self:GameHamster -> currentTile -> current:Tile

	executeSetProperty(self, hamster::ConcreteHamster::cFeatureKeyCurrentTile,
			self->getCurrentTile(), nullptr);

	// create reference: CREATE self:GameHamster -> currentTile -> front:Tile
	executeSetProperty(self, hamster::ConcreteHamster::cFeatureKeyCurrentTile,
			self->getCurrentTile(), front);

	return true;

}

bool MoveCommand::moveWest() {

	// new variable from reference: self:GameHamster -> currentTile -> current:Tile

	std::shared_ptr < mpw::Tile > current = self->getCurrentTile();
	if (current.get() == nullptr) {
		return false;
	}

	// new variable from reference: current:Tile -> west -> front:Tile

	std::shared_ptr < mpw::Tile > front = current->getWest();
	if (front.get() == nullptr) {
		return false;
	}

	// assert condition: self.direction == WEST
	if (self->getDirection() != mpw::Direction::WEST) {
		return false;
	}

	// remove reference: DELETE self:GameHamster -> currentTile -> current:Tile

	executeSetProperty(self, hamster::ConcreteHamster::cFeatureKeyCurrentTile,
			self->getCurrentTile(), nullptr);

	// create reference: CREATE self:GameHamster -> currentTile -> front:Tile
	executeSetProperty(self, hamster::ConcreteHamster::cFeatureKeyCurrentTile,
			self->getCurrentTile(), front);

	return true;

}

bool MoveCommand::moveEast() {

	// new variable from reference: self:GameHamster -> currentTile -> current:Tile

	std::shared_ptr < mpw::Tile > current = self->getCurrentTile();
	if (current.get() == nullptr) {
		return false;
	}

	// new variable from reference: current:Tile -> east -> front:Tile

	std::shared_ptr < mpw::Tile > front = current->getEast();
	if (front.get() == nullptr) {
		return false;
	}

	// assert condition: self.direction == EAST
	if (self->getDirection() != mpw::Direction::EAST) {
		return false;
	}

	// remove reference: DELETE self:GameHamster -> currentTile -> current:Tile

	executeSetProperty(self, hamster::ConcreteHamster::cFeatureKeyCurrentTile,
			self->getCurrentTile(), nullptr);

	// create reference: CREATE self:GameHamster -> currentTile -> front:Tile
	executeSetProperty(self, hamster::ConcreteHamster::cFeatureKeyCurrentTile,
			self->getCurrentTile(), front);

	return true;

}

bool MoveCommand::addGameLog() {

	// new instance: entry:LogEntry
	std::shared_ptr < mpw::LogEntry > entry = std::make_shared<mpw::LogEntry>();

	// set value type field entry.message := 
	executeSetStringProperty(entry, mpw::LogEntry::cFeatureKeyMessage,
			entry->getMessage(), "Move");

	// create reference: CREATE entry:LogEntry -> actor -> self:GameHamster
	executeSetProperty(entry, mpw::LogEntry::cFeatureKeyActor,
			entry->getActor(), self);

	// create reference: CREATE gameLog:GameLog -> logEntries -> entry:LogEntry
	executeAddReference(gameLog, mpw::GameLog::cFeatureKeyLogEntries, entry);

	return true;

}

}

