/*
 * This file is generated. Do not change it manually.
 */

#ifndef DE_UNISTUTTGART_HAMSTER_COMMANDSCLEARTILE_H
#define DE_UNISTUTTGART_HAMSTER_COMMANDSCLEARTILE_H

#include "CompositeCommandBase.h"
#include "ClearTileCommandParameters.h"

#include "Location.h"
#include "TileContent.h"
#include "Tile.h"
#include "ConcreteTerritory.h"
#include "Size.h"

namespace commands {

/**
 * Clears all contents of the tile identified by the given location.<br/>
 * <br/>
 * <b>requires / ensures:</b> the territory tiles must not be empty<br/>
 * <b>requires:</b> location has to be on territory<br/>
 * <b>ensures:</b> the tile's contents have to be empty
 * 
 */

class ClearTileCommand final : public CompositeCommandBase {
private:
	std::shared_ptr<hamster::ConcreteTerritory> self;
	commands::CommandStack &commandStack;

	mpw::Location location;

public:

	ClearTileCommand(ClearTileCommandParameters parameters) : self(
			parameters.self), commandStack(parameters.commandStack), location(
			parameters.location)

	{
	}

	void execute() override;

private:

	bool internalMainUnit();

	std::shared_ptr<mpw::Tile> execute_findO0(hamster::EditorTerritory &source);

};

}

#endif //DE_UNISTUTTGART_HAMSTER_COMMANDSCLEARTILE_H

