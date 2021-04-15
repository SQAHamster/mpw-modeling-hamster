/*
 * This file is generated. Do not change it manually.
 */

#include "AddWallToTileCommand.h"

#include "FrameworkAssert.h"
#include "CommandConstraintException.h"
#include "ConcreteTerritory.h"
#include "GameLog.h"
#include "CollectionHelpers.hpp"
#include <stdexcept>

using namespace framework;

namespace commands {

void AddWallToTileCommand::execute() {

	/*
	 * the tile at the given location has to be empty
	 */

	if ((self->getTileAt(location)->getContents().empty()) == false) {
		throw CommandConstraintException(
				"Violation of Precondition: the tile at the given location has to be empty");
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
				"Transformation was not successfully executed: addWallToTile");
	}

	/*
	 * a wall is placed on the tile on the tile location
	 */

	if ((collectionhelpers::type_select < hamster::Wall
			> (self->getTileAt(location)->getContents()).size() == 1)
			== false) {
		throw CommandConstraintException(
				"Violation of Postcondition: a wall is placed on the tile on the tile location");
	}

	/*
	 * the territory tiles must not be empty
	 */

	if ((self->getTiles().size() > 0) == false) {
		throw CommandConstraintException(
				"Violation of ClassInvariant: the territory tiles must not be empty");
	}

}
bool AddWallToTileCommand::internalMainUnit() {

	// new instance: o2:Wall
	std::shared_ptr < hamster::Wall > o2 = std::make_shared<hamster::Wall>();

	// find new variable from many-reference: self:EditorTerritory -> tiles -> o1:Tile

	std::shared_ptr < mpw::Tile > o1 = execute_findO1(*self);
	if (o1 == nullptr) {
		return false;
	}

	// new variable from reference: o1:Tile -> location -> o0:Location

	mpw::Location o0 = o1->getLocation();

	// assert condition: o0.column == location.column
	if (o0.getColumn() != location.getColumn()) {
		return false;
	}

	// assert condition: o0.row == location.row
	if (o0.getRow() != location.getRow()) {
		return false;
	}

	// create reference: CREATE o1:Tile -> contents -> o2:Wall
	executeAddReference(o1, mpw::Tile::cFeatureKeyContents, o2);

	// create reference: CREATE self:EditorTerritory -> tileContents -> o2:Wall
	executeAddReference(self,
			hamster::ConcreteTerritory::cFeatureKeyTileContents, o2);

	return true;

}

std::shared_ptr<mpw::Tile> AddWallToTileCommand::execute_findO1(
		hamster::EditorTerritory &source) {
	std::shared_ptr < mpw::Tile > result = nullptr;

	for (auto &o1 : source.getTiles().sharedPointerView()) {

		// reference check: o1: location
		mpw::Location o0 = o1->getLocation();

		// attribute check: o0: column
		if (o0.getColumn() != location.getColumn()) {
			continue;
		}

		// attribute check: o0: row
		if (o0.getRow() != location.getRow()) {
			continue;
		}

		result = o1;
		break;
	}
	return result;
}

}

