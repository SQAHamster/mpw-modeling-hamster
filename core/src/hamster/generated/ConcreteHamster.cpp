/*
 * This file is generated. Do not change it manually.
 */

#include "ConcreteHamster.h"

#include <stdexcept>

#include "CollectionHelpers.hpp"
#include "CommandStack.h"
#include "Tile.h"
#include "Stage.h"
#include "Wall.h"
#include "TileContent.h"
#include "GameTerritory.h"
#include "ConcreteTerritory.h"

#include "InitHamsterCommand.h"
#include "MoveCommand.h"
#include "PickGrainCommand.h"
#include "PutGrainCommand.h"
#include "TurnLeftCommand.h"
#include "WriteCommand.h"

namespace hamster {

ConcreteHamster::ConcreteHamster() {

}

bool ConcreteHamster::mouthEmpty() const noexcept {
	try {
		return this->getGrains().empty();
	} catch (...) {
		return false;
	}
}

mpw::Location ConcreteHamster::getLocation() const noexcept {
	try {
		return helper_GetLocation_currentTile_result0_location();
	} catch (...) {
		return {};
	}
}

mpw::Location ConcreteHamster::helper_GetLocation_currentTile_result0_location() const noexcept {
	std::shared_ptr<const mpw::Tile> result0 = this->getCurrentTile();
	if (result0 == nullptr) {
		return {};
	}
	mpw::Location result1 = result0->getLocation();
	return result1;
}

bool ConcreteHamster::frontIsClear() const noexcept {
	try {
		return (this->getDirection() == mpw::Direction::WEST) ? (helper_FrontIsClear_currentTile_result0_west_result1_contents_type_selectWall_is_empty()) :
				true && (this->getDirection() == mpw::Direction::EAST) ? (helper_FrontIsClear_currentTile_result0_east_result1_contents_type_selectWall_is_empty()) :
				true && (this->getDirection() == mpw::Direction::NORTH) ? (helper_FrontIsClear_currentTile_result0_north_result1_contents_type_selectWall_is_empty()) :
				true && (this->getDirection() == mpw::Direction::SOUTH) ? (helper_FrontIsClear_currentTile_result0_south_result1_contents_type_selectWall_is_empty()) :
						true;
	} catch (...) {
		return false;
	}
}

bool ConcreteHamster::helper_FrontIsClear_currentTile_result0_east_result1_contents_type_selectWall_is_empty() const noexcept {
	std::shared_ptr<const mpw::Tile> result0 = this->getCurrentTile();
	if (result0 == nullptr) {
		return false;
	}
	std::shared_ptr<const mpw::Tile> result1 = result0->getEast();
	if (result1 == nullptr) {
		return false;
	}
	bool result2 = collectionhelpers::type_select < hamster::Wall
			> (result1->getContents()).empty();
	return result2;
}

bool ConcreteHamster::helper_FrontIsClear_currentTile_result0_south_result1_contents_type_selectWall_is_empty() const noexcept {
	std::shared_ptr<const mpw::Tile> result0 = this->getCurrentTile();
	if (result0 == nullptr) {
		return false;
	}
	std::shared_ptr<const mpw::Tile> result1 = result0->getSouth();
	if (result1 == nullptr) {
		return false;
	}
	bool result2 = collectionhelpers::type_select < hamster::Wall
			> (result1->getContents()).empty();
	return result2;
}

bool ConcreteHamster::helper_FrontIsClear_currentTile_result0_north_result1_contents_type_selectWall_is_empty() const noexcept {
	std::shared_ptr<const mpw::Tile> result0 = this->getCurrentTile();
	if (result0 == nullptr) {
		return false;
	}
	std::shared_ptr<const mpw::Tile> result1 = result0->getNorth();
	if (result1 == nullptr) {
		return false;
	}
	bool result2 = collectionhelpers::type_select < hamster::Wall
			> (result1->getContents()).empty();
	return result2;
}

bool ConcreteHamster::helper_FrontIsClear_currentTile_result0_west_result1_contents_type_selectWall_is_empty() const noexcept {
	std::shared_ptr<const mpw::Tile> result0 = this->getCurrentTile();
	if (result0 == nullptr) {
		return false;
	}
	std::shared_ptr<const mpw::Tile> result1 = result0->getWest();
	if (result1 == nullptr) {
		return false;
	}
	bool result2 = collectionhelpers::type_select < hamster::Wall
			> (result1->getContents()).empty();
	return result2;
}

bool ConcreteHamster::grainAvailable() const noexcept {
	try {
		return helper_GrainAvailable_currentTile_result0_contents_type_selectGrain_not_empty();
	} catch (...) {
		return false;
	}
}

bool ConcreteHamster::helper_GrainAvailable_currentTile_result0_contents_type_selectGrain_not_empty() const noexcept {
	std::shared_ptr<const mpw::Tile> result0 = this->getCurrentTile();
	if (result0 == nullptr) {
		return false;
	}
	bool result1 = collectionhelpers::type_select < hamster::Grain
			> (result0->getContents()).size() > 0;
	return result1;
}

void ConcreteHamster::initHamster(
		commands::InitHamsterCommandParameters &parameters) {
	parameters.self = this->shared_from_this();
	auto command = std::make_shared < commands::InitHamsterCommand
			> (parameters);
	parameters.commandStack.execute(command);
}

void ConcreteHamster::move(commands::MoveCommandParameters &parameters) {
	parameters.self = this->shared_from_this();
	auto command = std::make_shared < commands::MoveCommand > (parameters);
	parameters.commandStack.execute(command);
}

void ConcreteHamster::pickGrain(
		commands::PickGrainCommandParameters &parameters) {
	parameters.self = this->shared_from_this();
	auto command = std::make_shared < commands::PickGrainCommand > (parameters);
	parameters.commandStack.execute(command);
}

void ConcreteHamster::putGrain(
		commands::PutGrainCommandParameters &parameters) {
	parameters.self = this->shared_from_this();
	auto command = std::make_shared < commands::PutGrainCommand > (parameters);
	parameters.commandStack.execute(command);
}

void ConcreteHamster::turnLeft(
		commands::TurnLeftCommandParameters &parameters) {
	parameters.self = this->shared_from_this();
	auto command = std::make_shared < commands::TurnLeftCommand > (parameters);
	parameters.commandStack.execute(command);
}

void ConcreteHamster::write(commands::WriteCommandParameters &parameters) {
	parameters.self = this->shared_from_this();
	auto command = std::make_shared < commands::WriteCommand > (parameters);
	parameters.commandStack.execute(command);
}

framework::ObservableListProperty<hamster::Grain>& ConcreteHamster::grainsProperty() noexcept {
	return this->grains;
}
const framework::ObservableListProperty<hamster::Grain>& ConcreteHamster::grainsProperty() const noexcept {
	return this->grains;
}

framework::ObjectListView<hamster::Grain>& ConcreteHamster::getGrains() noexcept {
	return this->grains;
}

const framework::ObjectListView<hamster::Grain>& ConcreteHamster::getGrains() const noexcept {
	return this->grains;
}

void ConcreteHamster::addToGrains(
		std::shared_ptr<hamster::Grain> grain) noexcept {
	if (this->grainsLookup.find(grain.get()) == this->grainsLookup.end()) {
		this->grains.add(grain);
		this->grainsLookup.insert(grain.get());
	}
}
void ConcreteHamster::removeFromGrains(
		std::shared_ptr<hamster::Grain> grain) noexcept {
	if (this->grainsLookup.find(grain.get()) != this->grainsLookup.end()) {
		this->grains.remove(grain);
		this->grainsLookup.erase(grain.get());
	}
}

void ConcreteHamster::clearGrains() noexcept {
	while (!this->grains.empty()) {
		removeFromGrains(this->grains.front());
	}
}

void ConcreteHamster::setProperty(unsigned featureKey, Any value) {
	switch (featureKey) {
	}

	inherited::setProperty(featureKey, value);
}

void ConcreteHamster::addToCollection(unsigned featureKey,
		EntityReference reference) {
	switch (featureKey) {
	case cFeatureKeyGrains: {

		auto typedElement =
				dynamic_cast<Grain*>(reinterpret_cast<basetypes::Entity*>(reference));
		auto sharedPtr = typedElement->shared_from_this();
		addToGrains(sharedPtr);

		return;
	}
	}

	inherited::addToCollection(featureKey, reference);
}

void ConcreteHamster::removeFromCollection(unsigned featureKey,
		EntityReference reference) {
	switch (featureKey) {
	case cFeatureKeyGrains: {

		auto typedElement =
				dynamic_cast<Grain*>(reinterpret_cast<basetypes::Entity*>(reference));
		auto sharedPtr = typedElement->shared_from_this();
		removeFromGrains(sharedPtr);

		return;
	}
	}

	inherited::removeFromCollection(featureKey, reference);
}

}
