/*
 * This file is generated. Do not change it manually.
 */

#ifndef DE_UNISTUTTGART_HAMSTER_COMMANDSINITTERRITORY_H
#define DE_UNISTUTTGART_HAMSTER_COMMANDSINITTERRITORY_H

#include "CompositeCommandBase.h"
#include "InitTerritoryCommandParameters.h"

#include "Tile.h"
#include "Location.h"
#include "ConcreteTerritory.h"
#include "ConcreteHamster.h"
#include "Size.h"
#include "TileContent.h"

namespace commands {

/**
 * Defines a new territory by creating a new, empty territory of the given size.<br/>
 * <br/>
 * <b>requires / ensures:</b> the territory tiles must not be empty<br/>
 * <b>requires:</b> size must be > 0<br/>
 * <b>ensures:</b> size of territory is set
 * 
 */

class InitTerritoryCommand final : public CompositeCommandBase {
private:
	std::shared_ptr<hamster::ConcreteTerritory> self;
	commands::CommandStack &commandStack;

	int columns;

	int rows;

public:

	InitTerritoryCommand(InitTerritoryCommandParameters parameters) : self(
			parameters.self), commandStack(parameters.commandStack), columns(
			parameters.columns), rows(parameters.rows)

	{
	}

	void execute() override;

private:

	bool internalMainUnit();

	bool createFirstRowTile(std::shared_ptr<mpw::Tile> &next);

	bool createInitialTile(std::shared_ptr<mpw::Tile> &firstInRow);

	bool createFirstTileForNextRow(std::shared_ptr<mpw::Tile> &firstInRow);

	bool createFurtherRowTile(std::shared_ptr<mpw::Tile> &next);

	bool createFirstRow(int columns, std::shared_ptr<mpw::Tile> next);

	bool createFurtherRows(std::shared_ptr<mpw::Tile> &firstInRow, int columns,
			int rows);

	bool createFurtherRow(std::shared_ptr<mpw::Tile> &firstInRow, int columns);

	bool createFurtherRowTiles(int columns, std::shared_ptr<mpw::Tile> next);

	bool setSize(int columns, int rows);

	bool clearTiles();

	bool clearTerritory();

	bool hamsterIsOnTile();

	bool clearHamsterAndTiles();

	bool resetHamsterTile();

};

}

#endif //DE_UNISTUTTGART_HAMSTER_COMMANDSINITTERRITORY_H

