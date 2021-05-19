/*
 * This file is generated. Do not change it manually.
 */

#ifndef DE_UNISTUTTGART_HAMSTER_GRAIN_H
#define DE_UNISTUTTGART_HAMSTER_GRAIN_H

#include <memory>
#include <string>
#include "Prop.h"

namespace hamster {

/**
 * A prop which represents grain to be picked or put by a hamster.
 * 
 * By deriving from Prop, a Grain represents a TileContent which has a link to the parent Stage.
 */
class Grain: public mpw::Prop {

private:

	using inherited = Prop;

public:

	Grain();

	/// \brief returns a shared_ptr of type Grain which shares ownership of *this
	std::shared_ptr<Grain> shared_from_this() {
		return std::dynamic_pointer_cast < Grain
				> (inherited::shared_from_this());
	}
	/// \brief returns a shared_ptr of const type Grain which shares ownership of *this
	std::shared_ptr<const Grain> shared_from_this() const {
		return std::dynamic_pointer_cast<const Grain>(
				inherited::shared_from_this());
	}

public:

	virtual ~Grain() = default;

	using Prop::cFeatureKeyCurrentTile;
	using Prop::cFeatureKeyStage;

	void setProperty(unsigned featureKey, Any value) override;
	void addToCollection(unsigned featureKey, EntityReference reference)
			override;
	void removeFromCollection(unsigned featureKey, EntityReference reference)
			override;

};

}

#endif //DE_UNISTUTTGART_HAMSTER_GRAIN_H

