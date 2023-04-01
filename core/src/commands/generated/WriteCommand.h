/*
 * This file is generated. Do not change it manually.
 */

#ifndef DE_UNISTUTTGART_HAMSTER_COMMANDSWRITE_H
#define DE_UNISTUTTGART_HAMSTER_COMMANDSWRITE_H

#include "CompositeCommandBase.h"
#include "WriteCommandParameters.h"

#include "LogEntry.h"
#include "GameLog.h"
#include "ConcreteHamster.h"

namespace commands {

/**
 * Writes a new string for this actor to the game log. The message
 * will be displayed in a way that it can be associated to this object.
 */

class WriteCommand final : public CompositeCommandBase {
private:
	std::shared_ptr<hamster::ConcreteHamster> self;
	commands::CommandStack &commandStack;
	std::shared_ptr<mpw::GameLog> gameLog;

	std::string message;

public:

	WriteCommand(WriteCommandParameters parameters) : self(parameters.self), commandStack(
			parameters.commandStack), gameLog(parameters.gameLog), message(
			parameters.message)

	{
	}

	void execute() override;

private:

	bool internalMainUnit();

};

}

#endif //DE_UNISTUTTGART_HAMSTER_COMMANDSWRITE_H

