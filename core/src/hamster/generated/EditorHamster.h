/*
 * This file is generated. Do not change it manually.
 */

#ifndef DE_UNISTUTTGART_HAMSTER_EDITORHAMSTER_H
#define DE_UNISTUTTGART_HAMSTER_EDITORHAMSTER_H

#include <memory>
#include <string>
#include "ReadOnlyHamster.h"

namespace hamster {

class EditorHamster: public virtual hamster::ReadOnlyHamster {

public:

	virtual ~EditorHamster() = default;

	/// \brief returns a shared_ptr of type EditorHamster which shares ownership of *this
	std::shared_ptr<EditorHamster> shared_from_this() {
		return std::dynamic_pointer_cast < EditorHamster
				> (basetypes::Entity::shared_from_this());
	}
	/// \brief returns a shared_ptr of const type EditorHamster which shares ownership of *this
	std::shared_ptr<const EditorHamster> shared_from_this() const {
		return std::dynamic_pointer_cast<const EditorHamster>(
				basetypes::Entity::shared_from_this());
	}

};

}

#endif //DE_UNISTUTTGART_HAMSTER_EDITORHAMSTER_H

