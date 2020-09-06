#pragma once

#include <GL/glew.h>
#include <vector>

#include "cat3d/gl/buffer.hpp"
#include "cat3d/gl/primitives.hpp"

namespace cat3d::gl {
/**
 * @brief Abstraction of an OpenGL Vertex Array Object
 * 
 */
class array {
public:
	array();

	/**
	 * @brief Delete the internal opengl representation
	 */
	void del();

	/**
	 * @brief Attach a new buffer to the vertex array
	 * 
	 * @param index The index of the buffer in the shader's layout
	 * @param size 1,2,3, or 4
	 * @return size_t The id of the generated buffer.
	 */
	size_t gen_buffer(GLuint index, GLuint size);

	/**
	 * @brief Bind a new element buffer to the vertex array 
	 * 
	 * @return size_t The id of the element buffer
	 */
	size_t gen_element_buffer();

	/**
	 * @brief Get the buffer at the given id
	 *
	 * @param id The id of the buffer
	 * 
	 * @returns buffer& A reference to the buffer
	 */
	buffer& get_buffer(size_t id);

	/**
	 * @brief Disable an attribute in this array
	 * 
	 * @param index The attribute index
	 */
	void disable_attrib(GLuint index);

	/**
	 * @brief Enable an attribute in this array
	 * 
	 * @param index The attribute index
	 */
	void enable_attrib(GLuint index);

	/**
	 * @brief Set this array's primitive type
	 * 
	 * @param p 
	 */
	void set_primitive(primitive p);

	/**
	 * @brief Retrieve this array's primitive type.
	 * 
	 * @return primitive 
	 */
	primitive get_primitive() const;

	/**
	 * @brief Internally sets the amount of vertices to render.
	 * 
	 * @param ct 
	 */
	void set_vertex_ct(GLuint ct);

	/**
	 * @brief Render the vertex array
	 * 
	 */
	void render();

private:
	friend class buffer;

	/// internal vao
	GLuint m_vao = 0;

	/// vao primitive type
	primitive m_prim;

	/// vao vertex size
	GLuint m_vertex_ct = 0;

	/// is an element buffer present?
	bool m_element_present = false;

	/// all internally stored buffers
	std::vector<buffer> m_buffers;

	/// bind the vertex array for editing
	void bind();
	/// unbind the vertex array
	void unbind();
};

}
