/*
 * This file is generated. Do not change it manually.
 */

#ifndef DE_UNISTUTTGART_HAMSTER_TERRITORYBUILDER_H
#define DE_UNISTUTTGART_HAMSTER_TERRITORYBUILDER_H

#include <memory>
#include <string>
#include "ObservableProperties.h"
#include "Location.h"
#include "Direction.h"

namespace hamster {
class EditorTerritory;
}
namespace hamster {
class HamsterGame;
}
namespace hamster {
class Territory;
}

namespace hamster {

class TerritoryBuilder: public std::enable_shared_from_this<TerritoryBuilder> {
private:

	std::shared_ptr<hamster::EditorTerritory> territory;
	std::weak_ptr<hamster::HamsterGame> game;

public:

	/**
	 * Creates a new TerritoryBuilder object which then can be used to defined the given Territory.
	 */
	TerritoryBuilder(std::shared_ptr<hamster::HamsterGame> game);
	/**
	 * Puts a number of grains at the given location. The location must not be blocked by a wall.<br/>
	 * <br/>
	 * <b>requires / ensures:</b> the territory tiles must not be empty<br/>
	 * <b>requires:</b> the amount of grains to add has to be equal or greater than zero<br/>
	 * <b>ensures:</b> the given amount of grains has to be equal to the grains on the tile location<br/>
	 * <b>requires:</b> location has to be on territory<br/>
	 * <b>requires:</b> the tile on the location has to be empty
	 * 
	 */
	TerritoryBuilder& addGrainsToTile(mpw::Location location, int amount);
	/**
	 * Place a wall at the given location. The location has to be empty before a wall can be placed.<br/>
	 * <br/>
	 * <b>requires / ensures:</b> the territory tiles must not be empty<br/>
	 * <b>requires:</b> the tile at the given location has to be empty<br/>
	 * <b>ensures:</b> a wall is placed on the tile on the tile location<br/>
	 * <b>requires:</b> location has to be on territory
	 * 
	 */
	TerritoryBuilder& addWallToTile(mpw::Location location);
	/**
	 * Clears all contents of the tile identified by the given location.<br/>
	 * <br/>
	 * <b>requires / ensures:</b> the territory tiles must not be empty<br/>
	 * <b>requires:</b> location has to be on territory<br/>
	 * <b>ensures:</b> the tile's contents have to be empty
	 * 
	 */
	TerritoryBuilder& clearTile(mpw::Location location);
	/**
	 * Initialize a hamster object with the given parameters. Once a hamster is initialized, the method must not be called again.<br/>
	 * <br/>
	 * <b>requires / ensures:</b> the territory tiles must not be empty<br/>
	 * <b>requires:</b> hamster must not be already initialized<br/>
	 * <b>requires:</b> grainCount has to be greater than or equal to zero<br/>
	 * <b>ensures:</b> the number of grains must equal the parameter grainCount<br/>
	 * <b>requires:</b> location has to be on territory
	 * 
	 */
	TerritoryBuilder& initDefaultHamster(mpw::Location location,
			mpw::Direction direction, int grainCount);
	/**
	 * Defines a new territory by creating a new, empty territory of the given size.<br/>
	 * <br/>
	 * <b>requires / ensures:</b> the territory tiles must not be empty<br/>
	 * <b>requires:</b> size must be > 0<br/>
	 * <b>ensures:</b> size of territory is set
	 * 
	 */
	TerritoryBuilder& initTerritory(int columns, int rows);
	/**
	 * Puts a number of grains at the given location. The location must not be blocked by a wall.<br/>
	 * <br/>
	 * <b>requires / ensures:</b> the territory tiles must not be empty<br/>
	 * <b>requires:</b> the amount of grains to add has to be equal or greater than zero<br/>
	 * <b>ensures:</b> the given amount of grains has to be equal to the grains on the tile location<br/>
	 * <b>requires:</b> location has to be on territory<br/>
	 * <b>requires:</b> the tile on the location has to be empty
	 * 
	 */
	TerritoryBuilder& addGrainsToTile(int locationX, int locationY, int amount);
	/**
	 * Place a wall at the given location. The location has to be empty before a wall can be placed.<br/>
	 * <br/>
	 * <b>requires / ensures:</b> the territory tiles must not be empty<br/>
	 * <b>requires:</b> the tile at the given location has to be empty<br/>
	 * <b>ensures:</b> a wall is placed on the tile on the tile location<br/>
	 * <b>requires:</b> location has to be on territory
	 * 
	 */
	TerritoryBuilder& addWallToTile(int locationX, int locationY);
	/**
	 * Clears all contents of the tile identified by the given location.<br/>
	 * <br/>
	 * <b>requires / ensures:</b> the territory tiles must not be empty<br/>
	 * <b>requires:</b> location has to be on territory<br/>
	 * <b>ensures:</b> the tile's contents have to be empty
	 * 
	 */
	TerritoryBuilder& clearTile(int locationX, int locationY);
	/**
	 * Initialize a hamster object with the given parameters. Once a hamster is initialized, the method must not be called again.<br/>
	 * <br/>
	 * <b>requires / ensures:</b> the territory tiles must not be empty<br/>
	 * <b>requires:</b> hamster must not be already initialized<br/>
	 * <b>requires:</b> grainCount has to be greater than or equal to zero<br/>
	 * <b>ensures:</b> the number of grains must equal the parameter grainCount<br/>
	 * <b>requires:</b> location has to be on territory
	 * 
	 */
	TerritoryBuilder& initDefaultHamster(int locationX, int locationY,
			mpw::Direction direction, int grainCount);

	/**
	 * Virtual desctructor to support inheritance.
	 */
	virtual ~TerritoryBuilder() = default;

};

}

#endif //DE_UNISTUTTGART_HAMSTER_TERRITORYBUILDER_H
