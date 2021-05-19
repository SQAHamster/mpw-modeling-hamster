/*
 * This file is generated. Do not change it manually.
 */

#ifndef DE_UNISTUTTGART_HAMSTER_COMMANDSADDWALLTOTILEPARAMETERS_H
#define DE_UNISTUTTGART_HAMSTER_COMMANDSADDWALLTOTILEPARAMETERS_H

#include <memory>

#include "Location.h"

namespace hamster {
class ConcreteTerritory;
}
namespace commands {
class CommandStack;
}

namespace commands {

struct AddWallToTileCommandParameters final {
	std::shared_ptr<hamster::ConcreteTerritory> self;
	commands::CommandStack &commandStack;

	mpw::Location location;

	AddWallToTileCommandParameters(
			std::shared_ptr<hamster::ConcreteTerritory> self,
			commands::CommandStack &commandStack, mpw::Location location) : self(
			self), commandStack(commandStack), location(location) {
	}
};

}

#endif //DE_UNISTUTTGART_HAMSTER_COMMANDSADDWALLTOTILEPARAMETERS_H

