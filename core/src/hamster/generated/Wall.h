/*
 * This file is generated. Do not change it manually.
 */

#ifndef DE_UNISTUTTGART_HAMSTER_WALL_H
#define DE_UNISTUTTGART_HAMSTER_WALL_H

#include <memory>
#include <string>
#include "Prop.h"

namespace hamster {

/**
 * A prop which represents a blocking content on a tile. A hamster
 * cannot be moved on a tile, if a wall is contained.
 * 
 * By deriving from Prop, a Wall represents a TileContent which has a link to the parent Stage.
 */
class Wall: public mpw::Prop {

private:

	using inherited = Prop;

public:

	Wall();

	/// \brief returns a shared_ptr of type Wall which shares ownership of *this
	std::shared_ptr<Wall> shared_from_this() {
		return std::dynamic_pointer_cast < Wall
				> (inherited::shared_from_this());
	}
	/// \brief returns a shared_ptr of const type Wall which shares ownership of *this
	std::shared_ptr<const Wall> shared_from_this() const {
		return std::dynamic_pointer_cast<const Wall>(
				inherited::shared_from_this());
	}

public:

	virtual ~Wall() = default;

	using Prop::cFeatureKeyCurrentTile;
	using Prop::cFeatureKeyStage;

	void setProperty(unsigned featureKey, Any value) override;
	void addToCollection(unsigned featureKey, EntityReference reference)
			override;
	void removeFromCollection(unsigned featureKey, EntityReference reference)
			override;

};

}

#endif //DE_UNISTUTTGART_HAMSTER_WALL_H

