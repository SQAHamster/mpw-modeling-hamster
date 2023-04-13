/*
 * This file is generated. Do not change it manually.
 */

#ifndef DE_UNISTUTTGART_HAMSTER_GAMEHAMSTER_H
#define DE_UNISTUTTGART_HAMSTER_GAMEHAMSTER_H

#include <memory>
#include <string>
#include "ReadOnlyHamster.h"
#include "Location.h"
#include "Direction.h"
#include "Size.h"

#include "InitHamsterCommandParameters.h"
#include "MoveCommandParameters.h"
#include "PickGrainCommandParameters.h"
#include "PutGrainCommandParameters.h"
#include "TurnLeftCommandParameters.h"
#include "WriteCommandParameters.h"

namespace hamster {
class GameTerritory;
}
namespace mpw {
class Stage;
}
namespace hamster {
class ConcreteHamster;
}
namespace hamster {
class ConcreteTerritory;
}
namespace mpw {
class Tile;
}
namespace hamster {
class Grain;
}
namespace mpw {
class TileContent;
}
namespace hamster {
class Wall;
}

namespace hamster {

class GameHamster: public virtual hamster::ReadOnlyHamster {

public:

	virtual ~GameHamster() = default;

	/// \brief returns a shared_ptr of type GameHamster which shares ownership of *this
	std::shared_ptr<GameHamster> shared_from_this() {
		return std::dynamic_pointer_cast < GameHamster
				> (basetypes::Entity::shared_from_this());
	}
	/// \brief returns a shared_ptr of const type GameHamster which shares ownership of *this
	std::shared_ptr<const GameHamster> shared_from_this() const {
		return std::dynamic_pointer_cast<const GameHamster>(
				basetypes::Entity::shared_from_this());
	}

	virtual void initHamster(
			commands::InitHamsterCommandParameters &parameters) = 0;

	virtual void move(commands::MoveCommandParameters &parameters) = 0;

	virtual void pickGrain(
			commands::PickGrainCommandParameters &parameters) = 0;

	virtual void putGrain(commands::PutGrainCommandParameters &parameters) = 0;

	virtual void turnLeft(commands::TurnLeftCommandParameters &parameters) = 0;

	virtual void write(commands::WriteCommandParameters &parameters) = 0;

};

}

#endif //DE_UNISTUTTGART_HAMSTER_GAMEHAMSTER_H

