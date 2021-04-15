/*
 * This file is generated. Do not change it manually.
 */

#ifndef DE_UNISTUTTGART_HAMSTER_COMMANDSPICKGRAIN_H
#define DE_UNISTUTTGART_HAMSTER_COMMANDSPICKGRAIN_H

#include "CompositeCommandBase.h"
#include "PickGrainCommandParameters.h"

#include "Grain.h"
#include "ConcreteHamster.h"
#include "GameLog.h"
#include "Tile.h"
#include "LogEntry.h"
#include "TileContent.h"
#include "Stage.h"

namespace commands {

/**
 * Pick up a random grain from the tile on which the hamster is currently.<br/>
 * <br/>
 * <b>requires / ensures:</b> the hamster is placed on a tile.<br/>
 * <b>ensures:</b> the number of grains has to be increased by one<br/>
 * <b>requires:</b> there have to be grains available on the hamster's tile
 * 
 */

class PickGrainCommand final : public CompositeCommandBase {
private:
	std::shared_ptr<hamster::ConcreteHamster> self;
	commands::CommandStack &commandStack;
	std::shared_ptr<mpw::GameLog> gameLog;

public:

	PickGrainCommand(PickGrainCommandParameters parameters) : self(
			parameters.self), commandStack(parameters.commandStack), gameLog(
			parameters.gameLog)

	{
	}

	void execute() override;

private:

	bool internalMainUnit();

	std::shared_ptr<hamster::Grain> execute_findGrain(mpw::Tile &source);

	bool addGameLog();

};

}

#endif //DE_UNISTUTTGART_HAMSTER_COMMANDSPICKGRAIN_H

