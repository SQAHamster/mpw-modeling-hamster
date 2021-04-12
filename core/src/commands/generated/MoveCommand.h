/*
 * This file is generated. Do not change it manually.
 */

#ifndef DE_UNISTUTTGART_HAMSTER_COMMANDSMOVE_H
#define DE_UNISTUTTGART_HAMSTER_COMMANDSMOVE_H

#include "CompositeCommandBase.h"
#include "MoveCommandParameters.h"

#include "Tile.h"
#include "GameLog.h"
#include "ConcreteHamster.h"
#include "LogEntry.h"
#include "Wall.h"
#include "TileContent.h"
#include "Direction.h"
#include "Stage.h"

namespace commands {

/**
 * Move the hamster one step towards its looking direction.<br/>
 * <br/>
 * <b>requires / ensures:</b> the hamster is placed on a tile.<br/>
 * <b>requires:</b> Hamster front must not be blocked or outside territory
 * 
 */

class MoveCommand final : public CompositeCommandBase {
private:
	std::shared_ptr<hamster::ConcreteHamster> self;
	commands::CommandStack &commandStack;
	std::shared_ptr<mpw::GameLog> gameLog;

public:

	MoveCommand(MoveCommandParameters parameters) : self(parameters.self), commandStack(
			parameters.commandStack), gameLog(parameters.gameLog)

	{
	}

	void execute() override;

private:

	bool internalMainUnit();

	bool moveNorth();

	bool moveSouth();

	bool moveWest();

	bool moveEast();

	bool addGameLog();

};

}

#endif //DE_UNISTUTTGART_HAMSTER_COMMANDSMOVE_H

