/*
 * This file is generated. Do not change it manually.
 */

#ifndef DE_UNISTUTTGART_HAMSTER_GAMETERRITORY_H
#define DE_UNISTUTTGART_HAMSTER_GAMETERRITORY_H

#include <memory>
#include <string>
#include "ReadOnlyTerritory.h"

namespace hamster {
class GameHamster;
}

namespace hamster {

class GameTerritory: public virtual hamster::ReadOnlyTerritory {

public:

	virtual ~GameTerritory() = default;

	/// \brief returns a shared_ptr of type GameTerritory which shares ownership of *this
	std::shared_ptr<GameTerritory> shared_from_this() {
		return std::dynamic_pointer_cast < GameTerritory
				> (basetypes::Entity::shared_from_this());
	}
	/// \brief returns a shared_ptr of const type GameTerritory which shares ownership of *this
	std::shared_ptr<const GameTerritory> shared_from_this() const {
		return std::dynamic_pointer_cast<const GameTerritory>(
				basetypes::Entity::shared_from_this());
	}

	virtual std::shared_ptr<hamster::GameHamster> getGameDefaultHamster() noexcept = 0;
	virtual std::shared_ptr<const hamster::GameHamster> getGameDefaultHamster() const noexcept = 0;

};

}

#endif //DE_UNISTUTTGART_HAMSTER_GAMETERRITORY_H

