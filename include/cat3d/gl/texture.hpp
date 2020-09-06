#pragma once

#include <GL/glew.h>
#include <stb/stb_image.h>
#include <string>

#include "cat3d/color.hpp"

namespace cat3d::gl {

/**
 * @brief Modes for how textures smaller than required are handled in the shader
 */
enum texture_wrap_mode {
	REPEAT			= GL_REPEAT,
	MIRRORED_REPEAT = GL_MIRRORED_REPEAT,
	CLAMP_TO_EDGE	= GL_CLAMP_TO_EDGE,
	CLAMP_TO_BORDER = GL_CLAMP_TO_BORDER
};

enum texture_filter_mode {
	NEAREST = GL_NEAREST,
	LINEAR	= GL_LINEAR
};

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
	 * @brief Load a 1x1 pixel texture of a given color.
	 *
	 * @remarks set_wrap_mode() should be set to REPEAT to copy the color throughout any model using this texture.
	 *
	 * @param col The color to use.
	 */
	void load_color(color col);

	/**
	 * @brief Set the texture's wrapping mode
	 *
	 * @param mode
	 */
	void set_wrap_mode(texture_wrap_mode mode);

	/**
	 * @brief When the texture's wrapping mode is set to CLAMP_TO_BORDER,
	 * there needs to be a configured border color.
	 *
	 * @param col The color to set the border to.
	 */
	void set_border_color(color col);

	/**
	 * @brief Sets the texture's filtering mode.
	 *
	 * @param mode The texture filtering mode
	 *
	 * @remarks NEAREST appears more pixellated, while LINEAR appears more interpolated.
	 */
	void set_filter_mode(texture_filter_mode mode);

	/**
     * @brief Bind the texture to the opengl context.
     */
	void bind();

	/**
	 * @brief Unbind the texture.
	 */
	void unbind();

private:
	/// internal texture id
	GLuint m_tex;

	/// has the texture been loaded already?
	bool m_loaded;

	/// internally used to make sure that the state of this texture being bound is preserved
	void push_bind_state();
	void pop_bind_state();
	bool m_bind_state;
};

}
