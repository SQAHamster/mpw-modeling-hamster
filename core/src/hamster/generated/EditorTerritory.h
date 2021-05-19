/*
 * This file is generated. Do not change it manually.
 */

#ifndef DE_UNISTUTTGART_HAMSTER_EDITORTERRITORY_H
#define DE_UNISTUTTGART_HAMSTER_EDITORTERRITORY_H

#include <memory>
#include <string>
#include "ReadOnlyTerritory.h"
#include "Size.h"
#include "Location.h"
#include "Direction.h"

#include "AddGrainsToTileCommandParameters.h"
#include "AddWallToTileCommandParameters.h"
#include "ClearTileCommandParameters.h"
#include "InitDefaultHamsterCommandParameters.h"
#include "InitTerritoryCommandParameters.h"

namespace mpw {
class Tile;
}
namespace hamster {
class ConcreteTerritory;
}
namespace mpw {
class TileContent;
}
namespace hamster {
class Wall;
}
namespace hamster {
class Grain;
}
namespace hamster {
class ConcreteHamster;
}
namespace mpw {
class Stage;
}
namespace hamster {
class EditorHamster;
}

namespace hamster {

class EditorTerritory: public virtual hamster::ReadOnlyTerritory {

public:

	virtual ~EditorTerritory() = default;

	/// \brief returns a shared_ptr of type EditorTerritory which shares ownership of *this
	std::shared_ptr<EditorTerritory> shared_from_this() {
		return std::dynamic_pointer_cast < EditorTerritory
				> (basetypes::Entity::shared_from_this());
	}
	/// \brief returns a shared_ptr of const type EditorTerritory which shares ownership of *this
	std::shared_ptr<const EditorTerritory> shared_from_this() const {
		return std::dynamic_pointer_cast<const EditorTerritory>(
				basetypes::Entity::shared_from_this());
	}

	virtual void addGrainsToTile(
			commands::AddGrainsToTileCommandParameters &parameters) = 0;

	virtual void addWallToTile(
			commands::AddWallToTileCommandParameters &parameters) = 0;

	virtual void clearTile(
			commands::ClearTileCommandParameters &parameters) = 0;

	virtual void initDefaultHamster(
			commands::InitDefaultHamsterCommandParameters &parameters) = 0;

	virtual void initTerritory(
			commands::InitTerritoryCommandParameters &parameters) = 0;

	virtual std::shared_ptr<hamster::EditorHamster> getEditorDefaultHamster() noexcept = 0;
	virtual std::shared_ptr<const hamster::EditorHamster> getEditorDefaultHamster() const noexcept = 0;

};

}

#endif //DE_UNISTUTTGART_HAMSTER_EDITORTERRITORY_H

