/*
 * This file is generated. Do not change it manually.
 */

#include "Territory.h"

#include <stdexcept>

#include "HamsterGame.h"
#include "ConcreteTerritory.h"
#include "Hamster.h"
#include "MiniProgrammingWorld.h"
#include "ConcreteHamster.h"

namespace hamster {

Territory::Territory(std::shared_ptr<hamster::HamsterGame> game) {
	this->internalTerritory = std::make_shared<ConcreteTerritory>();
	this->game = game;
	this->defaultHamster = std::make_shared < Hamster
			> (game, internalTerritory->getDefaultHamster());
}

mpw::Size Territory::getTerritorySize() const noexcept {
	return internalTerritory->getTerritorySize();
}

bool Territory::isLocationInTerritory(mpw::Location location) const noexcept {
	return internalTerritory->isLocationInTerritory(location);
}

std::shared_ptr<hamster::GameTerritory> Territory::getInternalTerritory() noexcept {
	return this->internalTerritory;
}
std::shared_ptr<const hamster::GameTerritory> Territory::getInternalTerritory() const noexcept {
	return this->internalTerritory;
}

std::shared_ptr<hamster::EditorTerritory> Territory::getInternalEditorTerritory() noexcept {
	return this->internalTerritory;
}
std::shared_ptr<const hamster::EditorTerritory> Territory::getInternalEditorTerritory() const noexcept {
	return this->internalTerritory;
}

std::shared_ptr<hamster::Hamster> Territory::getDefaultHamster() noexcept {
	return this->defaultHamster;
}
std::shared_ptr<const hamster::Hamster> Territory::getDefaultHamster() const noexcept {
	return this->defaultHamster;
}

std::shared_ptr<hamster::HamsterGame> Territory::getGame() noexcept {
	return this->game.lock();
}
std::shared_ptr<const hamster::HamsterGame> Territory::getGame() const noexcept {
	return this->game.lock();
}

}

