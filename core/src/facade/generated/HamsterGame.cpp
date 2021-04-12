/*
 * This file is generated. Do not change it manually.
 */

#include "HamsterGame.h"

#include <stdexcept>

#include "Territory.h"
#include "GamePerformance.h"
#include "UserInputInterface.h"
#include "CommandStack.h"

namespace hamster {

std::shared_ptr<HamsterGame> HamsterGame::create() {
	auto instance = std::shared_ptr < HamsterGame > (new HamsterGame);
	instance->init();
	return instance;
}

void HamsterGame::init() {

	this->territory = std::make_shared < hamster::Territory
			> (this->shared_from_this());
}

std::shared_ptr<hamster::Territory> HamsterGame::getTerritory() noexcept {
	return this->territory;
}

std::shared_ptr<const hamster::Territory> HamsterGame::getTerritory() const noexcept {
	return this->territory;
}

void HamsterGame::startGame() {
	auto performance = getPerformance();
	performance->startGame();
}

void HamsterGame::startGamePaused() {
	auto performance = getPerformance();
	performance->startGamePaused();
}

void HamsterGame::hardReset() {
	auto performance = getPerformance();
	performance->hardReset();
}

void HamsterGame::stopGame() {
	auto performance = getPerformance();
	performance->stopGame();
}

void HamsterGame::pauseGame() {
	auto performance = getPerformance();
	performance->pauseGame();
}

void HamsterGame::resumeGame() {
	auto performance = getPerformance();
	performance->resumeGame();
}

void HamsterGame::confirmAlert(const std::exception &t) {
	auto userInputInterface = getUserInputInterface();
	userInputInterface->confirmAlert(t);
}

std::shared_ptr<commands::CommandStack> HamsterGame::getGameCommandStack() {
	auto performance = getPerformance();
	return performance->getGameCommandStack();
}

}
