/*
 * This file is generated. Do not change it manually.
 */

#ifndef DE_UNISTUTTGART_HAMSTER_COMMANDSPUTGRAIN_H
#define DE_UNISTUTTGART_HAMSTER_COMMANDSPUTGRAIN_H

#include "CompositeCommandBase.h"
#include "PutGrainCommandParameters.h"

#include "Grain.h"
#include "ConcreteHamster.h"
#include "GameLog.h"
#include "Tile.h"
#include "LogEntry.h"
#include "Stage.h"

namespace commands {

/**
 * Drop a random grain object from the hamster's mouth.<br/>
 * <br/>
 * <b>requires / ensures:</b> the hamster is placed on a tile.<br/>
 * <b>requires:</b> the hamster has to carry any grain
 * 
 */

class PutGrainCommand final : public CompositeCommandBase {
private:
	std::shared_ptr<hamster::ConcreteHamster> self;
	commands::CommandStack &commandStack;
	std::shared_ptr<mpw::GameLog> gameLog;

public:

	PutGrainCommand(PutGrainCommandParameters parameters) : self(
			parameters.self), commandStack(parameters.commandStack), gameLog(
			parameters.gameLog)

	{
	}

	void execute() override;

private:

	bool internalMainUnit();

	std::shared_ptr<hamster::Grain> execute_findGrain(
			hamster::GameHamster &source);

	bool addGameLog();

};

}

#endif //DE_UNISTUTTGART_HAMSTER_COMMANDSPUTGRAIN_H

