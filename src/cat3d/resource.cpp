#include "cat3d/resource.hpp"

namespace cat3d {

resource resource::m_primary;

resource::resource() {

}

resource::~resource() {

}

gl::texture& resource::texture(const std::string& path) {
	if(m_textures.find(path) == m_textures.end()) {
		m_textures[path].load_file(path);
	}
	return m_textures[path];
}

resource& resource::get() {
	return m_primary;
}

}
