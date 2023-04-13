/*
 * This file is generated. Do not change it manually.
 */

#ifndef DE_UNISTUTTGART_HAMSTER_COMMANDSMOVEPARAMETERS_H
#define DE_UNISTUTTGART_HAMSTER_COMMANDSMOVEPARAMETERS_H

#include <memory>

namespace hamster {
class ConcreteHamster;
}
namespace commands {
class CommandStack;
}
namespace mpw {
class GameLog;
}

namespace commands {

struct MoveCommandParameters final {
	std::shared_ptr<hamster::ConcreteHamster> self;
	commands::CommandStack &commandStack;
	std::shared_ptr<mpw::GameLog> gameLog;

	MoveCommandParameters(std::shared_ptr<hamster::ConcreteHamster> self,
			commands::CommandStack &commandStack,
			std::shared_ptr<mpw::GameLog> gameLog) : self(self), commandStack(
			commandStack), gameLog(gameLog) {
	}
};

}

#endif //DE_UNISTUTTGART_HAMSTER_COMMANDSMOVEPARAMETERS_H
