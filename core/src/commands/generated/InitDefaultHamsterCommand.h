/*
 * This file is generated. Do not change it manually.
 */

#ifndef DE_UNISTUTTGART_HAMSTER_COMMANDSINITDEFAULTHAMSTER_H
#define DE_UNISTUTTGART_HAMSTER_COMMANDSINITDEFAULTHAMSTER_H

#include "CompositeCommandBase.h"
#include "InitDefaultHamsterCommandParameters.h"

#include "Location.h"
#include "Direction.h"
#include "ConcreteTerritory.h"
#include "Tile.h"
#include "ConcreteHamster.h"
#include "Grain.h"
#include "Size.h"
#include "Stage.h"

namespace commands {

/**
 * Initialize a hamster object with the given parameters. Once a hamster is initialized, the method must not be called again.<br/>
 * <br/>
 * <b>requires / ensures:</b> the territory tiles must not be empty<br/>
 * <b>requires:</b> grainCount has to be greater than or equal to zero<br/>
 * <b>requires:</b> hamster must not be already initialized<br/>
 * <b>ensures:</b> the number of grains must equal the parameter grainCount<br/>
 * <b>requires:</b> location has to be on territory
 * 
 */

class InitDefaultHamsterCommand final : public CompositeCommandBase {
private:
	std::shared_ptr<hamster::ConcreteTerritory> self;
	commands::CommandStack &commandStack;

	mpw::Location location;

	mpw::Direction direction;

	int grainCount;

public:

	InitDefaultHamsterCommand(InitDefaultHamsterCommandParameters parameters) : self(
			parameters.self), commandStack(parameters.commandStack), location(
			parameters.location), direction(parameters.direction), grainCount(
			parameters.grainCount)

	{
	}

	void execute() override;

private:

	bool internalMainUnit();

	bool setProperties(mpw::Direction initialDirection);

	bool addMultipleGrain(int grainCount);

	bool addGrain();

	bool addToTerritory(mpw::Location location);

	std::shared_ptr<mpw::Tile> addToTerritory_findO0(
			hamster::EditorTerritory &source);

};

}

#endif //DE_UNISTUTTGART_HAMSTER_COMMANDSINITDEFAULTHAMSTER_H

