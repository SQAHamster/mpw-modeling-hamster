/*
 * This file is generated. Do not change it manually.
 */

#ifndef DE_UNISTUTTGART_HAMSTER_COMMANDSINITDEFAULTHAMSTERPARAMETERS_H
#define DE_UNISTUTTGART_HAMSTER_COMMANDSINITDEFAULTHAMSTERPARAMETERS_H

#include <memory>

#include "Location.h"
#include "Direction.h"

namespace hamster {
class ConcreteTerritory;
}
namespace commands {
class CommandStack;
}

namespace commands {

struct InitDefaultHamsterCommandParameters final {
	std::shared_ptr<hamster::ConcreteTerritory> self;
	commands::CommandStack &commandStack;

	mpw::Location location;

	mpw::Direction direction;

	int grainCount;

	InitDefaultHamsterCommandParameters(
			std::shared_ptr<hamster::ConcreteTerritory> self,
			commands::CommandStack &commandStack, mpw::Location location,
			mpw::Direction direction, int grainCount) : self(self), commandStack(
			commandStack), location(location), direction(direction), grainCount(
			grainCount) {
	}
};

}

#endif //DE_UNISTUTTGART_HAMSTER_COMMANDSINITDEFAULTHAMSTERPARAMETERS_H

