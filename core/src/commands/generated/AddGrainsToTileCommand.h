/*
 * This file is generated. Do not change it manually.
 */

#ifndef DE_UNISTUTTGART_HAMSTER_COMMANDSADDGRAINSTOTILE_H
#define DE_UNISTUTTGART_HAMSTER_COMMANDSADDGRAINSTOTILE_H

#include "CompositeCommandBase.h"
#include "AddGrainsToTileCommandParameters.h"

#include "Location.h"
#include "Grain.h"
#include "Tile.h"
#include "ConcreteTerritory.h"
#include "TileContent.h"
#include "Size.h"
#include "Wall.h"

namespace commands {

/**
 * Puts a number of grains at the given location. The location must not be blocked by a wall.<br/>
 * <br/>
 * <b>requires / ensures:</b> the territory tiles must not be empty<br/>
 * <b>requires:</b> the amount of grains to add has to be equal or greater than zero<br/>
 * <b>ensures:</b> the given amount of grains has to be equal to the grains on the tile location<br/>
 * <b>requires:</b> location has to be on territory<br/>
 * <b>requires:</b> the tile on the location has to be empty
 * 
 */

class AddGrainsToTileCommand final : public CompositeCommandBase {
private:
	std::shared_ptr<hamster::ConcreteTerritory> self;
	commands::CommandStack &commandStack;

	mpw::Location location;

	int amount;

public:

	AddGrainsToTileCommand(AddGrainsToTileCommandParameters parameters) : self(
			parameters.self), commandStack(parameters.commandStack), location(
			parameters.location), amount(parameters.amount)

	{
	}

	void execute() override;

private:

	bool internalMainUnit();

	bool addGrainToTile(mpw::Location location);

	std::shared_ptr<mpw::Tile> addGrainToTile_findO1(
			hamster::EditorTerritory &source);

};

}

#endif //DE_UNISTUTTGART_HAMSTER_COMMANDSADDGRAINSTOTILE_H

