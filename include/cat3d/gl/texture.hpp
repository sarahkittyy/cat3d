#pragma once

#include <GL/glew.h>
#include <stb/stb_image.h>
#include <string>

namespace cat3d::gl {

/**
 * @brief Internal opengl texture representation
 */
class texture {
public:
	texture();

	/**
	 * @brief Delete the internal opengl representation 
	 */
	void del();

	/**
     * @brief Load a file from the given path
     * 
     * @param path The path to the file
     */
	void load_file(const std::string& path);

	/**
     * @brief Bind the texture to the opengl context.
     */
	void bind();

private:
	/// internal texture id
	GLuint m_tex;
};

}
