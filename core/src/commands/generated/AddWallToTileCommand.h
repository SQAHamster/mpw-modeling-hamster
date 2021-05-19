/*
 * This file is generated. Do not change it manually.
 */

#ifndef DE_UNISTUTTGART_HAMSTER_COMMANDSADDWALLTOTILE_H
#define DE_UNISTUTTGART_HAMSTER_COMMANDSADDWALLTOTILE_H

#include "CompositeCommandBase.h"
#include "AddWallToTileCommandParameters.h"

#include "Location.h"
#include "Wall.h"
#include "Tile.h"
#include "ConcreteTerritory.h"
#include "TileContent.h"
#include "Size.h"

namespace commands {

/**
 * Place a wall at the given location. The location has to be empty before a wall can be placed.<br/>
 * <br/>
 * <b>requires / ensures:</b> the territory tiles must not be empty<br/>
 * <b>ensures:</b> a wall is placed on the tile on the tile location<br/>
 * <b>requires:</b> the tile at the given location has to be empty<br/>
 * <b>requires:</b> location has to be on territory
 * 
 */

class AddWallToTileCommand final : public CompositeCommandBase {
private:
	std::shared_ptr<hamster::ConcreteTerritory> self;
	commands::CommandStack &commandStack;

	mpw::Location location;

public:

	AddWallToTileCommand(AddWallToTileCommandParameters parameters) : self(
			parameters.self), commandStack(parameters.commandStack), location(
			parameters.location)

	{
	}

	void execute() override;

private:

	bool internalMainUnit();

	std::shared_ptr<mpw::Tile> execute_findO1(hamster::EditorTerritory &source);

};

}

#endif //DE_UNISTUTTGART_HAMSTER_COMMANDSADDWALLTOTILE_H

