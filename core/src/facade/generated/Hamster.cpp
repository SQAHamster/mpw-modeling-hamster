/*
 * This file is generated. Do not change it manually.
 */

#include "Hamster.h"

#include <stdexcept>

#include "CommandStack.h"
#include "GamePerformance.h"
#include "HamsterGame.h"
#include "ConcreteHamster.h"
#include "Territory.h"
#include "GameTerritory.h"
#include "UserInputInterface.h"

namespace hamster {

Hamster::Hamster() {
	this->internalHamster = std::make_shared<ConcreteHamster>();
}

Hamster::Hamster(std::shared_ptr<hamster::Territory> territory,
		mpw::Location location, mpw::Direction direction, int grainCount) {
	this->internalHamster = std::make_shared<ConcreteHamster>();
	this->init(territory, location, direction, grainCount);
}

Hamster::Hamster(std::shared_ptr<hamster::HamsterGame> game,
		std::shared_ptr<hamster::ConcreteHamster> internalHamster) {
	this->internalHamster = internalHamster;
	this->game = game;
}

void Hamster::init(std::shared_ptr<hamster::Territory> territory,
		mpw::Location location, mpw::Direction direction, int grainCount) {
	this->game = territory->getGame();
	auto gameTerritory = territory->getInternalTerritory();
	commands::InitHamsterCommandParameters parameters(
	/*self*/nullptr, *game.lock()->getGameCommandStack(),
			game.lock()->getGameLog(), gameTerritory, location, direction,
			grainCount);
	game.lock()->getPerformance()->preExecuteGameCommand();
	try {
		internalHamster->initHamster(parameters);
		game.lock()->getPerformance()->delayControlFlow();
	} catch (std::exception &e) {
		// Stop the game to prevent execution of further commands!
		game.lock()->getPerformance()->setMode(mpw::Mode::STOPPED);
		throw; // rethrow
	}
}

void Hamster::move() {
	commands::MoveCommandParameters parameters(
	/*self*/nullptr, *game.lock()->getGameCommandStack(),
			game.lock()->getGameLog());
	game.lock()->getPerformance()->preExecuteGameCommand();
	try {
		internalHamster->move(parameters);
		game.lock()->getPerformance()->delayControlFlow();
	} catch (std::exception &e) {
		// Stop the game to prevent execution of further commands!
		game.lock()->getPerformance()->setMode(mpw::Mode::STOPPED);
		throw; // rethrow
	}
}

void Hamster::pickGrain() {
	commands::PickGrainCommandParameters parameters(
	/*self*/nullptr, *game.lock()->getGameCommandStack(),
			game.lock()->getGameLog());
	game.lock()->getPerformance()->preExecuteGameCommand();
	try {
		internalHamster->pickGrain(parameters);
		game.lock()->getPerformance()->delayControlFlow();
	} catch (std::exception &e) {
		// Stop the game to prevent execution of further commands!
		game.lock()->getPerformance()->setMode(mpw::Mode::STOPPED);
		throw; // rethrow
	}
}

void Hamster::putGrain() {
	commands::PutGrainCommandParameters parameters(
	/*self*/nullptr, *game.lock()->getGameCommandStack(),
			game.lock()->getGameLog());
	game.lock()->getPerformance()->preExecuteGameCommand();
	try {
		internalHamster->putGrain(parameters);
		game.lock()->getPerformance()->delayControlFlow();
	} catch (std::exception &e) {
		// Stop the game to prevent execution of further commands!
		game.lock()->getPerformance()->setMode(mpw::Mode::STOPPED);
		throw; // rethrow
	}
}

void Hamster::turnLeft() {
	commands::TurnLeftCommandParameters parameters(
	/*self*/nullptr, *game.lock()->getGameCommandStack(),
			game.lock()->getGameLog());
	game.lock()->getPerformance()->preExecuteGameCommand();
	try {
		internalHamster->turnLeft(parameters);
		game.lock()->getPerformance()->delayControlFlow();
	} catch (std::exception &e) {
		// Stop the game to prevent execution of further commands!
		game.lock()->getPerformance()->setMode(mpw::Mode::STOPPED);
		throw; // rethrow
	}
}

void Hamster::write(std::string message) {
	commands::WriteCommandParameters parameters(
	/*self*/nullptr, *game.lock()->getGameCommandStack(),
			game.lock()->getGameLog(), message);
	game.lock()->getPerformance()->preExecuteGameCommand();
	try {
		internalHamster->write(parameters);
		game.lock()->getPerformance()->delayControlFlow();
	} catch (std::exception &e) {
		// Stop the game to prevent execution of further commands!
		game.lock()->getPerformance()->setMode(mpw::Mode::STOPPED);
		throw; // rethrow
	}
}

mpw::Direction Hamster::getDirection() const noexcept {
	return internalHamster->getDirection();
}

bool Hamster::frontIsClear() const noexcept {
	return internalHamster->frontIsClear();
}

bool Hamster::mouthEmpty() const noexcept {
	return internalHamster->mouthEmpty();
}

mpw::Location Hamster::getLocation() const noexcept {
	return internalHamster->getLocation();
}

bool Hamster::grainAvailable() const noexcept {
	return internalHamster->grainAvailable();
}

int Hamster::readNumber(std::string message) {
	auto gameInterface = game.lock()->getUserInputInterface();
	auto result = gameInterface->readInteger(message);
	return result;
}

std::string Hamster::readString(std::string message) {
	auto gameInterface = game.lock()->getUserInputInterface();
	auto result = gameInterface->readString(message);
	return result;
}

std::shared_ptr<hamster::GameHamster> Hamster::getInternalHamster() noexcept {
	return this->internalHamster;
}
std::shared_ptr<const hamster::GameHamster> Hamster::getInternalHamster() const noexcept {
	return this->internalHamster;
}

std::shared_ptr<hamster::EditorHamster> Hamster::getInternalEditorHamster() noexcept {
	return this->internalHamster;
}
std::shared_ptr<const hamster::EditorHamster> Hamster::getInternalEditorHamster() const noexcept {
	return this->internalHamster;
}

}

