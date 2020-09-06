#pragma once

#include <unordered_map>
#include <string>

#include "cat3d/gl.hpp"

namespace cat3d {

/**
 * @brief Primary app resource manager. Handles the loading / unloading of assets to conserve memory.
 */
class resource {
public:
	resource();
	~resource();
	
	/**
	 * @brief Get the texture at the given path
	 *
	 * @param path The path to the texture file
	 *
	 * @returns gl::texture& A reference to the loaded texture
	 */
	gl::texture& texture(const std::string& path);

	/**
	 * @brief Get the default app resource manager
	 *
	 * @returns resource&
	 */
	static resource& get();

private:
	/// the primary app manager
	static resource m_primary;

	/// all loaded textures
	std::unordered_map<std::string, gl::texture> m_textures;
};

}
