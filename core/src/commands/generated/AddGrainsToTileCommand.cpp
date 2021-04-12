/*
 * This file is generated. Do not change it manually.
 */

#include "AddGrainsToTileCommand.h"

#include "FrameworkAssert.h"
#include "CommandConstraintException.h"
#include "ConcreteTerritory.h"
#include "GameLog.h"
#include "CollectionHelpers.hpp"
#include <stdexcept>

using namespace framework;

namespace commands {

void AddGrainsToTileCommand::execute() {

	/*
	 * the amount of grains to add has to be equal or greater than zero
	 */

	if ((amount >= 0) == false) {
		throw CommandConstraintException(
				"Violation of Precondition: the amount of grains to add has to be equal or greater than zero");
	}

	/*
	 * the tile on the location has to be empty
	 */

	if ((collectionhelpers::type_select < hamster::Wall
			> (self->getTileAt(location)->getContents()).empty()) == false) {
		throw CommandConstraintException(
				"Violation of Precondition: the tile on the location has to be empty");
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
				"Transformation was not successfully executed: addGrainsToTile");
	}

	/*
	 * the given amount of grains has to be equal to the grains on the tile location
	 */

	if ((collectionhelpers::type_select < hamster::Grain
			> (self->getTileAt(location)->getContents()).size() == amount)
			== false) {
		throw CommandConstraintException(
				"Violation of Postcondition: the given amount of grains has to be equal to the grains on the tile location");
	}

	/*
	 * the territory tiles must not be empty
	 */

	if ((self->getTiles().size() > 0) == false) {
		throw CommandConstraintException(
				"Violation of ClassInvariant: the territory tiles must not be empty");
	}

}
bool AddGrainsToTileCommand::internalMainUnit() {

	for (int i = 0; i < static_cast<int>(amount); i++) {
		if (!addGrainToTile(location)) {
			return false;
		}
	}
	return true;

}

bool AddGrainsToTileCommand::addGrainToTile(mpw::Location location) {

	// new instance: o2:Grain
	std::shared_ptr < hamster::Grain > o2 = std::make_shared<hamster::Grain>();

	// find new variable from many-reference: self:EditorTerritory -> tiles -> o1:Tile

	std::shared_ptr < mpw::Tile > o1 = addGrainToTile_findO1(*self);
	if (o1 == nullptr) {
		return false;
	}

	// new variable from reference: o1:Tile -> location -> o0:Location

	mpw::Location o0 = o1->getLocation();

	// assert condition: o0.row == location.row
	if (o0.getRow() != location.getRow()) {
		return false;
	}

	// assert condition: o0.column == location.column
	if (o0.getColumn() != location.getColumn()) {
		return false;
	}

	// create reference: CREATE o1:Tile -> contents -> o2:Grain
	executeAddReference(o1, mpw::Tile::cFeatureKeyContents, o2);

	// create reference: CREATE self:EditorTerritory -> tileContents -> o2:Grain
	executeAddReference(self,
			hamster::ConcreteTerritory::cFeatureKeyTileContents, o2);

	return true;

}

std::shared_ptr<mpw::Tile> AddGrainsToTileCommand::addGrainToTile_findO1(
		hamster::EditorTerritory &source) {
	std::shared_ptr < mpw::Tile > result = nullptr;

	for (auto &o1 : source.getTiles().sharedPointerView()) {

		// reference check: o1: location
		mpw::Location o0 = o1->getLocation();

		// attribute check: o0: row
		if (o0.getRow() != location.getRow()) {
			continue;
		}

		// attribute check: o0: column
		if (o0.getColumn() != location.getColumn()) {
			continue;
		}

		result = o1;
		break;
	}
	return result;
}

}

