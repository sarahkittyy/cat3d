#include "cat3d/obj/texture.hpp"

namespace cat3d::obj {

texture::texture(const std::string& path)
	: m_tex(resource::get().texture(path)),
	  m_hooked(false) {
}

texture::texture(color col)
	: m_hooked(false) {
	m_tex.load_color(col);
}

texture::~texture() {
	if (m_hooked) {
		parent()->unbind(m_hook_id);
	}
}

void texture::update_self(window& win) {
	if (!m_hooked) {
		m_hooked  = true;
		m_hook_id = parent()->bind(scene::PRE_RENDER, [this]() {
			m_tex.bind();
		});
	}
}
}
