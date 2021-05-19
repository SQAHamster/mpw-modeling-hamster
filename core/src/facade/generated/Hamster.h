/*
 * This file is generated. Do not change it manually.
 */

#ifndef DE_UNISTUTTGART_HAMSTER_HAMSTER_H
#define DE_UNISTUTTGART_HAMSTER_HAMSTER_H

#include <memory>
#include <string>
#include "ObservableProperties.h"
#include "Location.h"
#include "Direction.h"

namespace hamster {
class HamsterGame;
}
namespace hamster {
class ConcreteHamster;
}
namespace hamster {
class Territory;
}
namespace hamster {
class GameTerritory;
}
namespace mpw {
class UserInputInterface;
}
namespace hamster {
class GameHamster;
}
namespace hamster {
class EditorHamster;
}

namespace hamster {

/**
 * Class for Hamster in the Hamster Simulator. This class allows to initialize
 * Hamsters, command Hamsters through their territory and query their state.
 * 
 * By deriving from Actor, a Hamster represents a TileContent which has a link to the parent Stage.
 */
class Hamster: public std::enable_shared_from_this<Hamster> {
private:

	std::weak_ptr<hamster::HamsterGame> game;
	std::shared_ptr<hamster::ConcreteHamster> internalHamster;

public:

	/**
	 * Create a new Hamster object without initializing it.
	 */
	Hamster();
	/**
	 * Create a new Hamster object by initializing it with the relating init() method.
	 */
	Hamster(std::shared_ptr<hamster::Territory> territory,
			mpw::Location location, mpw::Direction direction, int grainCount);
	/**
	 * Internal constructor.
	 */
	Hamster(std::shared_ptr<hamster::HamsterGame> game,
			std::shared_ptr<hamster::ConcreteHamster> internalHamster);
	/**
	 * Initialize a hamster object with the given parameters. Once a hamster is initialized, the method must not be called again.<br/>
	 * <br/>
	 * <b>requires / ensures:</b> the hamster is placed on a tile.<br/>
	 * <b>requires:</b> the hamster must not be already initialized<br/>
	 * <b>requires:</b> grainCount has to be greater than or equal to zero<br/>
	 * <b>ensures:</b> the number of grains must equal the parameter grainCount<br/>
	 * <b>requires:</b> location has to be on territory
	 * 
	 */
	void init(std::shared_ptr<hamster::Territory> territory,
			mpw::Location location, mpw::Direction direction, int grainCount);
	/**
	 * Move the hamster one step towards its looking direction.<br/>
	 * <br/>
	 * <b>requires / ensures:</b> the hamster is placed on a tile.<br/>
	 * <b>requires:</b> Hamster front must not be blocked or outside territory
	 * 
	 */
	void move();
	/**
	 * Pick up a random grain from the tile on which the hamster is currently.<br/>
	 * <br/>
	 * <b>requires / ensures:</b> the hamster is placed on a tile.<br/>
	 * <b>ensures:</b> the number of grains has to be increased by one<br/>
	 * <b>requires:</b> there have to be grains available on the hamster's tile
	 * 
	 */
	void pickGrain();
	/**
	 * Drop a random grain object from the hamster's mouth.<br/>
	 * <br/>
	 * <b>requires / ensures:</b> the hamster is placed on a tile.<br/>
	 * <b>requires:</b> the hamster has to carry any grain
	 * 
	 */
	void putGrain();
	/**
	 * Changes the looking direction 90 degrees to the left, e.g., when looking north the hamster will look towards west afterwards.<br/>
	 * <br/>
	 * <b>requires / ensures:</b> the hamster is placed on a tile.
	 * 
	 */
	void turnLeft();
	/**
	 * Writes a new string for this actor to the game log. The message
	 * will be displayed in a way that it can be associated to this object.
	 */
	void write(std::string message);
	/**
	 * Get the current hamster looking direction.
	 */
	mpw::Direction getDirection() const noexcept;
	/**
	 * Checks whether the hamster's mouth is empty or whether it has grains in its mouth.
	 */
	bool mouthEmpty() const noexcept;
	/**
	 * Get the current hamster location.
	 */
	mpw::Location getLocation() const noexcept;
	/**
	 * Checks the hamster's current tile for grain.
	 */
	bool grainAvailable() const noexcept;
	/**
	 * Checks the front of the hamster.
	 */
	bool frontIsClear() const noexcept;
	/**
	 * Read a number from the simulator UI for further use.
	 */
	int readNumber(std::string message);
	/**
	 * Read a string from the simulator UI for further use.
	 */
	std::string readString(std::string message);

	/**
	 * Virtual desctructor to support inheritance.
	 */
	virtual ~Hamster() = default;

	/**
	 * Get the internal game representation of the Hamster.
	 */
	std::shared_ptr<hamster::GameHamster> getInternalHamster() noexcept;
	/**
	 * Get the internal game representation of the Hamster.
	 */
	std::shared_ptr<const hamster::GameHamster> getInternalHamster() const noexcept;
	/**
	 * Get the internal editor representation of the Hamster.
	 */
	std::shared_ptr<hamster::EditorHamster> getInternalEditorHamster() noexcept;
	/**
	 * Get the internal editor representation of the Hamster.
	 */
	std::shared_ptr<const hamster::EditorHamster> getInternalEditorHamster() const noexcept;

};

}

#endif //DE_UNISTUTTGART_HAMSTER_HAMSTER_H
