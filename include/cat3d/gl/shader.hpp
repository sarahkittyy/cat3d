#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

namespace cat3d::gl {

/**
 * @brief OpenGL abstraction to handle shader setup & binding.
 * 
 */
class shader {
public:
	/**
	 * @brief Initialize the shader
	 * 
	 * @param vs The vertex shader source
	 * @param fs The fragment shader source
	 */
	shader(const char* vs, const char* fs);

	/**
	 * @brief Load the default shader
	 * 
	 */
	shader();

	/**
	 * @brief Delete the internal shader program 
	 */
	void del();

	/// bind the shader
	void bind();

private:
	/// internal gl program
	GLuint m_prog = -1;

	/// was the shader loaded?
	bool loaded() const;

	/// default shaders
	static const char* m_default_vs;
	static const char* m_default_fs;
};

}
