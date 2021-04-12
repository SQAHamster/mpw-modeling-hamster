/*
 * This file is generated. Do not change it manually.
 */

#ifndef DE_UNISTUTTGART_HAMSTER_COMMANDSINITHAMSTERPARAMETERS_H
#define DE_UNISTUTTGART_HAMSTER_COMMANDSINITHAMSTERPARAMETERS_H

#include <memory>

#include "Location.h"
#include "Direction.h"

namespace hamster {
class ConcreteHamster;
}
namespace commands {
class CommandStack;
}
namespace mpw {
class GameLog;
}
namespace hamster {
class GameTerritory;
}

namespace commands {

struct InitHamsterCommandParameters final {
	std::shared_ptr<hamster::ConcreteHamster> self;
	commands::CommandStack &commandStack;
	std::shared_ptr<mpw::GameLog> gameLog;

	std::shared_ptr<hamster::GameTerritory> territory;

	mpw::Location location;

	mpw::Direction direction;

	int grainCount;

	InitHamsterCommandParameters(std::shared_ptr<hamster::ConcreteHamster> self,
			commands::CommandStack &commandStack,
			std::shared_ptr<mpw::GameLog> gameLog,
			std::shared_ptr<hamster::GameTerritory> territory,
			mpw::Location location, mpw::Direction direction, int grainCount) : self(
			self), commandStack(commandStack), gameLog(gameLog), territory(
			territory), location(location), direction(direction), grainCount(
			grainCount) {
	}
};

}

#endif //DE_UNISTUTTGART_HAMSTER_COMMANDSINITHAMSTERPARAMETERS_H

