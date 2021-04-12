/*
 * This file is generated. Do not change it manually.
 */

#ifndef DE_UNISTUTTGART_HAMSTER_COMMANDSCLEARTILEPARAMETERS_H
#define DE_UNISTUTTGART_HAMSTER_COMMANDSCLEARTILEPARAMETERS_H

#include <memory>

#include "Location.h"

namespace hamster {
class ConcreteTerritory;
}
namespace commands {
class CommandStack;
}

namespace commands {

struct ClearTileCommandParameters final {
	std::shared_ptr<hamster::ConcreteTerritory> self;
	commands::CommandStack &commandStack;

	mpw::Location location;

	ClearTileCommandParameters(std::shared_ptr<hamster::ConcreteTerritory> self,
			commands::CommandStack &commandStack, mpw::Location location) : self(
			self), commandStack(commandStack), location(location) {
	}
};

}

#endif //DE_UNISTUTTGART_HAMSTER_COMMANDSCLEARTILEPARAMETERS_H

