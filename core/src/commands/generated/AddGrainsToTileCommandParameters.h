/*
 * This file is generated. Do not change it manually.
 */

#ifndef DE_UNISTUTTGART_HAMSTER_COMMANDSADDGRAINSTOTILEPARAMETERS_H
#define DE_UNISTUTTGART_HAMSTER_COMMANDSADDGRAINSTOTILEPARAMETERS_H

#include <memory>

#include "Location.h"

namespace hamster {
class ConcreteTerritory;
}
namespace commands {
class CommandStack;
}

namespace commands {

struct AddGrainsToTileCommandParameters final {
	std::shared_ptr<hamster::ConcreteTerritory> self;
	commands::CommandStack &commandStack;

	mpw::Location location;

	int amount;

	AddGrainsToTileCommandParameters(
			std::shared_ptr<hamster::ConcreteTerritory> self,
			commands::CommandStack &commandStack, mpw::Location location,
			int amount) : self(self), commandStack(commandStack), location(
			location), amount(amount) {
	}
};

}

#endif //DE_UNISTUTTGART_HAMSTER_COMMANDSADDGRAINSTOTILEPARAMETERS_H

