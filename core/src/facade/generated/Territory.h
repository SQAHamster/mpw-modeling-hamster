/*
 * This file is generated. Do not change it manually.
 */

#ifndef DE_UNISTUTTGART_HAMSTER_TERRITORY_H
#define DE_UNISTUTTGART_HAMSTER_TERRITORY_H

#include <memory>
#include <string>
#include "ObservableProperties.h"
#include "Size.h"
#include "Location.h"

namespace hamster {
class HamsterGame;
}
namespace hamster {
class ConcreteTerritory;
}
namespace hamster {
class Hamster;
}
namespace mpw {
class MiniProgrammingWorld;
}
namespace hamster {
class ConcreteHamster;
}
namespace hamster {
class GameTerritory;
}
namespace hamster {
class EditorTerritory;
}

namespace hamster {

/**
 * The territory is a Stage which represents territories for hamsters. Territories
 * are rectangular areas with width and height composed out of territory
 * tiles. Tiles again can contain hamster objects, grain objects, or walls.
 */
class Territory: public std::enable_shared_from_this<Territory> {
private:

	std::weak_ptr<hamster::HamsterGame> game;
	std::shared_ptr<hamster::ConcreteTerritory> internalTerritory;
	std::shared_ptr<hamster::Hamster> defaultHamster;

public:

	/**
	 * Initialize a new Territory and link it to its game object.
	 */
	Territory(std::shared_ptr<hamster::HamsterGame> game);
	/**
	 * Return the size of the current territory. From the size you can retrieve the number of rows and colums.
	 */
	mpw::Size getTerritorySize() const noexcept;
	/**
	 * For a given location, tests whether the location is inside the bound of the territory.
	 */
	bool isLocationInTerritory(mpw::Location location) const noexcept;

	/**
	 * Virtual desctructor to support inheritance.
	 */
	virtual ~Territory() = default;

	/**
	 * Get the internal game representation of the Territory.
	 */
	std::shared_ptr<hamster::GameTerritory> getInternalTerritory() noexcept;
	/**
	 * Get the internal game representation of the Territory.
	 */
	std::shared_ptr<const hamster::GameTerritory> getInternalTerritory() const noexcept;
	/**
	 * Get the internal editor representation of the Territory.
	 */
	std::shared_ptr<hamster::EditorTerritory> getInternalEditorTerritory() noexcept;
	/**
	 * Get the internal editor representation of the Territory.
	 */
	std::shared_ptr<const hamster::EditorTerritory> getInternalEditorTerritory() const noexcept;
	std::shared_ptr<hamster::Hamster> getDefaultHamster() noexcept;
	std::shared_ptr<const hamster::Hamster> getDefaultHamster() const noexcept;
	/**
	 * Gets the game associated to this Territory object.
	 */
	std::shared_ptr<hamster::HamsterGame> getGame() noexcept;
	/**
	 * Gets the game associated to this Territory object.
	 */
	std::shared_ptr<const hamster::HamsterGame> getGame() const noexcept;

};

}

#endif //DE_UNISTUTTGART_HAMSTER_TERRITORY_H
