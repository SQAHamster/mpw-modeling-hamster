/*
 * This file is generated. Do not change it manually.
 */

#include "TerritoryBuilder.h"

#include <stdexcept>

#include "CommandStack.h"
#include "GamePerformance.h"
#include "EditorTerritory.h"
#include "HamsterGame.h"
#include "Territory.h"

namespace hamster {

TerritoryBuilder::TerritoryBuilder(std::shared_ptr<hamster::HamsterGame> game) {
	this->game = game;
	this->territory = game->getTerritory()->getInternalEditorTerritory();
}

TerritoryBuilder& TerritoryBuilder::addGrainsToTile(mpw::Location location,
		int amount) {
	commands::AddGrainsToTileCommandParameters parameters(
	/*self*/nullptr, *game.lock()->getEditorCommandStack(), location, amount);
	game.lock()->getPerformance()->preExecuteEditorCommand();
	territory->addGrainsToTile(parameters);
	return *this->shared_from_this();
}

TerritoryBuilder& TerritoryBuilder::addWallToTile(mpw::Location location) {
	commands::AddWallToTileCommandParameters parameters(
	/*self*/nullptr, *game.lock()->getEditorCommandStack(), location);
	game.lock()->getPerformance()->preExecuteEditorCommand();
	territory->addWallToTile(parameters);
	return *this->shared_from_this();
}

TerritoryBuilder& TerritoryBuilder::clearTile(mpw::Location location) {
	commands::ClearTileCommandParameters parameters(
	/*self*/nullptr, *game.lock()->getEditorCommandStack(), location);
	game.lock()->getPerformance()->preExecuteEditorCommand();
	territory->clearTile(parameters);
	return *this->shared_from_this();
}

TerritoryBuilder& TerritoryBuilder::initDefaultHamster(mpw::Location location,
		mpw::Direction direction, int grainCount) {
	commands::InitDefaultHamsterCommandParameters parameters(
	/*self*/nullptr, *game.lock()->getEditorCommandStack(), location, direction,
			grainCount);
	game.lock()->getPerformance()->preExecuteEditorCommand();
	territory->initDefaultHamster(parameters);
	return *this->shared_from_this();
}

TerritoryBuilder& TerritoryBuilder::initTerritory(int columns, int rows) {
	commands::InitTerritoryCommandParameters parameters(
	/*self*/nullptr, *game.lock()->getEditorCommandStack(), columns, rows);
	game.lock()->getPerformance()->preExecuteEditorCommand();
	territory->initTerritory(parameters);
	return *this->shared_from_this();
}

TerritoryBuilder& TerritoryBuilder::addGrainsToTile(int locationX,
		int locationY, int amount) {
	mpw::Location location(locationX, locationY);
	commands::AddGrainsToTileCommandParameters parameters(
	/*self*/nullptr, *game.lock()->getEditorCommandStack(), location, amount);
	game.lock()->getPerformance()->preExecuteEditorCommand();
	territory->addGrainsToTile(parameters);
	return *this->shared_from_this();
}

TerritoryBuilder& TerritoryBuilder::addWallToTile(int locationX,
		int locationY) {
	mpw::Location location(locationX, locationY);
	commands::AddWallToTileCommandParameters parameters(
	/*self*/nullptr, *game.lock()->getEditorCommandStack(), location);
	game.lock()->getPerformance()->preExecuteEditorCommand();
	territory->addWallToTile(parameters);
	return *this->shared_from_this();
}

TerritoryBuilder& TerritoryBuilder::clearTile(int locationX, int locationY) {
	mpw::Location location(locationX, locationY);
	commands::ClearTileCommandParameters parameters(
	/*self*/nullptr, *game.lock()->getEditorCommandStack(), location);
	game.lock()->getPerformance()->preExecuteEditorCommand();
	territory->clearTile(parameters);
	return *this->shared_from_this();
}

TerritoryBuilder& TerritoryBuilder::initDefaultHamster(int locationX,
		int locationY, mpw::Direction direction, int grainCount) {
	mpw::Location location(locationX, locationY);
	commands::InitDefaultHamsterCommandParameters parameters(
	/*self*/nullptr, *game.lock()->getEditorCommandStack(), location, direction,
			grainCount);
	game.lock()->getPerformance()->preExecuteEditorCommand();
	territory->initDefaultHamster(parameters);
	return *this->shared_from_this();
}

}

