/*
 * This file is generated. Do not change it manually.
 */

#ifndef DE_UNISTUTTGART_HAMSTER_COMMANDSINITTERRITORYPARAMETERS_H
#define DE_UNISTUTTGART_HAMSTER_COMMANDSINITTERRITORYPARAMETERS_H

#include <memory>

namespace hamster {
class ConcreteTerritory;
}
namespace commands {
class CommandStack;
}

namespace commands {

struct InitTerritoryCommandParameters final {
	std::shared_ptr<hamster::ConcreteTerritory> self;
	commands::CommandStack &commandStack;

	int columns;

	int rows;

	InitTerritoryCommandParameters(
			std::shared_ptr<hamster::ConcreteTerritory> self,
			commands::CommandStack &commandStack, int columns, int rows) : self(
			self), commandStack(commandStack), columns(columns), rows(rows) {
	}
};

}

#endif //DE_UNISTUTTGART_HAMSTER_COMMANDSINITTERRITORYPARAMETERS_H

