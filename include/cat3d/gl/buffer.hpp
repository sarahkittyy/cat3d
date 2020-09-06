#pragma once

#include <GL/glew.h>
#include <vector>

#include <iostream>

namespace cat3d::gl {

class array;

/**
 * @brief Types of Vertex Buffer Objects
 * 
 */
enum buffer_type {
	Vertex	= GL_ARRAY_BUFFER,
	Element = GL_ELEMENT_ARRAY_BUFFER,
};

/**
 * @brief OpenGL Vertex Buffer abstraction for rendering 3D objects onto the screen.
 * 
 */
class buffer {
public:
	/**
	 * @brief Delete the internal OpenGL buffer object.
	 */
	void del();

	/**
	 * @brief Get the index of this buffer in the parent VAO 
	 */
	GLuint index() const;

	/**
	 * @brief Get the internal type of this buffer
	 */
	buffer_type get_type() const;

	/**
	 * @brief Set the internal buffer data
	 * 
	 * @tparam T 
	 * @param data 
	 */
	template <typename T>
	void set_data(const std::vector<T>& data) {
		set_data_impl(
			(void*)data.data(),
			data.size(),
			sizeof(typename std::vector<T>::value_type));
	}

private:
	/**
	 * @brief Constructor is private as to only allow buffers to be generated through cat3d/gl/array.hpp
	 * 
	 */
	buffer();

	/// so array can manipulate the buffer as needed
	friend class array;

	/// set the internal type of this buffer
	void set_type(buffer_type t);

	/// internal vbo object
	GLuint m_vbo;

	/// parent vertex array
	array* m_parent;

	/// internal vao index of this buffer
	GLuint m_vao_i;

	/// internal per-vertex value count
	GLuint m_vertex_size;

	/// configure
	void* m_data;

	/// buffer type
	buffer_type m_type = Vertex;

	/// bind the buffer
	void bind();

	/// for set_data calls
	void set_data_impl(void* data, size_t data_size, size_t data_type_size);
};

}
