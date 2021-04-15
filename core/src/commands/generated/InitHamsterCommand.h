/*
 * This file is generated. Do not change it manually.
 */

#ifndef DE_UNISTUTTGART_HAMSTER_COMMANDSINITHAMSTER_H
#define DE_UNISTUTTGART_HAMSTER_COMMANDSINITHAMSTER_H

#include "CompositeCommandBase.h"
#include "InitHamsterCommandParameters.h"

#include "ConcreteTerritory.h"
#include "Location.h"
#include "Direction.h"
#include "ConcreteHamster.h"
#include "LogEntry.h"
#include "Tile.h"
#include "Grain.h"
#include "GameLog.h"
#include "Stage.h"
#include "Size.h"

namespace commands {

/**
 * Initialize a hamster object with the given parameters. Once a hamster is initialized, the method must not be called again.<br/>
 * <br/>
 * <b>requires / ensures:</b> the hamster is placed on a tile.<br/>
 * <b>ensures:</b> the number of grains must equal the parameter grainCount<br/>
 * <b>requires:</b> grainCount has to be greater than or equal to zero<br/>
 * <b>requires:</b> the hamster must not be already initialized<br/>
 * <b>requires:</b> location has to be on territory
 * 
 */

class InitHamsterCommand final : public CompositeCommandBase {
private:
	std::shared_ptr<hamster::ConcreteHamster> self;
	commands::CommandStack &commandStack;
	std::shared_ptr<mpw::GameLog> gameLog;

	std::shared_ptr<hamster::GameTerritory> territory;

	mpw::Location location;

	mpw::Direction direction;

	int grainCount;

public:

	InitHamsterCommand(InitHamsterCommandParameters parameters) : self(
			parameters.self), commandStack(parameters.commandStack), gameLog(
			parameters.gameLog), territory(parameters.territory), location(
			parameters.location), direction(parameters.direction), grainCount(
			parameters.grainCount)

	{
	}

	void execute() override;

private:

	bool internalMainUnit();

	bool setProperties(mpw::Direction initialDirection);

	bool addMultipleGrain(std::shared_ptr<hamster::GameTerritory> territory,
			int grainCount);

	bool addGrain(std::shared_ptr<hamster::GameTerritory> territory);

	bool addToTerritory(std::shared_ptr<hamster::GameTerritory> territory,
			mpw::Location location);

	std::shared_ptr<mpw::Tile> addToTerritory_findO0(
			hamster::GameTerritory &source);

	bool addGameLog();

};

}

#endif //DE_UNISTUTTGART_HAMSTER_COMMANDSINITHAMSTER_H

