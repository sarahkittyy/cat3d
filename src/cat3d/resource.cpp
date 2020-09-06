#include "cat3d/resource.hpp"

namespace cat3d {

resource resource::m_primary;

resource::resource() {

}

resource::~resource() {

}

resource& resource::get() {
	return m_primary;
}

}
