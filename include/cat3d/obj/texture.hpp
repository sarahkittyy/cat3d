#pragma once

#include "cat3d/gl/texture.hpp"
#include "cat3d/scene.hpp"

namespace cat3d::obj {

/**
 * @brief Scene node to bind a texture to the parent object on render.
 */
class texture : public scene::node {
public:
	/**
	 * @brief Initialize the texture.
	 *
	 * @param path The path to the texture.
	 */
	texture(const std::string& path);
	
	/// disconnects from the bind hook
	~texture();

protected:
	/// self update
	void update_self(window& win);

private:
	/// internal texture
	gl::texture m_tex;
	/// texture bind hook id
	size_t m_hook_id;
	/// has the hook been applied yet?
	bool m_hooked;
};

}
