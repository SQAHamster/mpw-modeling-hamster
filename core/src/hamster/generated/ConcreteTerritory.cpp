/*
 * This file is generated. Do not change it manually.
 */

#include "ConcreteTerritory.h"

#include <stdexcept>

#include "CollectionHelpers.hpp"
#include "CommandStack.h"
#include "ConcreteHamster.h"
#include "Tile.h"
#include "TileContent.h"
#include "Wall.h"
#include "Grain.h"
#include "Stage.h"

#include "AddGrainsToTileCommand.h"
#include "AddWallToTileCommand.h"
#include "ClearTileCommand.h"
#include "InitDefaultHamsterCommand.h"
#include "InitTerritoryCommand.h"

namespace hamster {

ConcreteTerritory::ConcreteTerritory() {

	this->defaultHamster = std::make_shared<hamster::ConcreteHamster>();
}

mpw::Size ConcreteTerritory::getTerritorySize() const noexcept {
	try {
		return this->getStageSize();
	} catch (...) {
		return {};
	}
}

bool ConcreteTerritory::isLocationInTerritory(
		mpw::Location location) const noexcept {
	try {
		return location.getColumn() >= 0
				&& location.getColumn() < this->getStageSize().getColumnCount()
				&& location.getRow() >= 0
				&& location.getRow() < this->getStageSize().getRowCount();
	} catch (...) {
		return false;
	}
}

std::shared_ptr<const mpw::Tile> ConcreteTerritory::getTileAt(
		mpw::Location location) const noexcept {
	try {
		return collectionhelpers::get_at(this->getTiles(),
				location.getRow() * this->getStageSize().getColumnCount()
						+ location.getColumn()).value();
	} catch (...) {
		return nullptr;
	}
}

void ConcreteTerritory::addGrainsToTile(
		commands::AddGrainsToTileCommandParameters &parameters) {
	parameters.self = this->shared_from_this();
	auto command = std::make_shared < commands::AddGrainsToTileCommand
			> (parameters);
	parameters.commandStack.execute(command);
}

void ConcreteTerritory::addWallToTile(
		commands::AddWallToTileCommandParameters &parameters) {
	parameters.self = this->shared_from_this();
	auto command = std::make_shared < commands::AddWallToTileCommand
			> (parameters);
	parameters.commandStack.execute(command);
}

void ConcreteTerritory::clearTile(
		commands::ClearTileCommandParameters &parameters) {
	parameters.self = this->shared_from_this();
	auto command = std::make_shared < commands::ClearTileCommand > (parameters);
	parameters.commandStack.execute(command);
}

void ConcreteTerritory::initDefaultHamster(
		commands::InitDefaultHamsterCommandParameters &parameters) {
	parameters.self = this->shared_from_this();
	auto command = std::make_shared < commands::InitDefaultHamsterCommand
			> (parameters);
	parameters.commandStack.execute(command);
}

void ConcreteTerritory::initTerritory(
		commands::InitTerritoryCommandParameters &parameters) {
	parameters.self = this->shared_from_this();
	auto command = std::make_shared < commands::InitTerritoryCommand
			> (parameters);
	parameters.commandStack.execute(command);
}

std::shared_ptr<hamster::ConcreteHamster> ConcreteTerritory::getDefaultHamster() noexcept {
	return this->defaultHamster;
}

std::shared_ptr<const hamster::ConcreteHamster> ConcreteTerritory::getDefaultHamster() const noexcept {
	return this->defaultHamster;
}

std::shared_ptr<hamster::ReadOnlyHamster> ConcreteTerritory::getReadOnlyDefaultHamster() noexcept {
	return this->defaultHamster;
}
std::shared_ptr<const hamster::ReadOnlyHamster> ConcreteTerritory::getReadOnlyDefaultHamster() const noexcept {
	return this->defaultHamster;
}

std::shared_ptr<hamster::GameHamster> ConcreteTerritory::getGameDefaultHamster() noexcept {
	return this->defaultHamster;
}
std::shared_ptr<const hamster::GameHamster> ConcreteTerritory::getGameDefaultHamster() const noexcept {
	return this->defaultHamster;
}

std::shared_ptr<hamster::EditorHamster> ConcreteTerritory::getEditorDefaultHamster() noexcept {
	return this->defaultHamster;
}
std::shared_ptr<const hamster::EditorHamster> ConcreteTerritory::getEditorDefaultHamster() const noexcept {
	return this->defaultHamster;
}

void ConcreteTerritory::setProperty(unsigned featureKey, Any value) {
	switch (featureKey) {
	}

	inherited::setProperty(featureKey, value);
}

void ConcreteTerritory::addToCollection(unsigned featureKey,
		EntityReference reference) {
	switch (featureKey) {
	}

	inherited::addToCollection(featureKey, reference);
}

void ConcreteTerritory::removeFromCollection(unsigned featureKey,
		EntityReference reference) {
	switch (featureKey) {
	}

	inherited::removeFromCollection(featureKey, reference);
}

}
