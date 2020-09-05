#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>

#include "cat3d/color.hpp"
#include "cat3d/gl/shader.hpp"

namespace cat3d {

/**
 * @brief Manages internal window api / state
 * 
 */
class window {
public:
	window(unsigned int width, unsigned int height, const char* title);
	~window();

	/**
	 * @brief Returns false if the window should close.
	 * 
	 */
	bool is_open() const;

	/**
	 * @brief Clear the window
	 * 
	 */
	void clear(color clear_color);

	/**
	 * @brief Render drawn items to the screen
	 * 
	 */
	void flip();

	/**
	 * @brief set the model matrix when rendering
	 * 
	 */
	void set_transform(glm::mat4 m);

	/**
	 * @brief set the view matrix
	 * 
	 */
	void set_view(glm::mat4 v);

	/**
	 * @brief set the projection matrix
	 * 
	 */
	void set_proj(glm::mat4 p);

	/**
	 * @brief get the x/y size of the window, in pixels
	 * 
	 * @return glm::vec2 
	 */
	glm::vec2 size() const;

private:
	/// internal GLFW window
	GLFWwindow* m_win;

	/// get the active shader program
	GLuint program();

	/**
	 * @brief Set a uniform value in the shader program
	 * 
	 * @param name the name of the uniform
	 * @param value the value to use
	 */
	template <typename T>
	void set_uniform(const char* name, T& value);
};

}