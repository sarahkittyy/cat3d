#include "cat3d/resource.hpp"

namespace cat3d {

resource resource::m_primary;

resource::resource() {
}

resource::~resource() {
}

gl::texture& resource::texture(const std::string& path) {
	if (m_textures.find(path) == m_textures.end()) {
		m_textures[path].load_file(path);
	}
	return m_textures[path];
}

const std::vector<gl::mesh>& resource::mesh(const std::string& path) {
	if (m_meshes.find(path) == m_meshes.end()) {
		m_meshes[path] = gl::mesh::load_file(path);
	}
	return m_meshes[path];
}

resource& resource::get() {
	return m_primary;
}

}
