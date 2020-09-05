#pragma once

#include <GL/glew.h>
#include <vector>

#include "cat3d/gl/buffer.hpp"
#include "cat3d/gl/primitives.hpp"

namespace cat3d::gl {

/**
 * @brief vertex array abstraction
 * 
 */
class array {
public:
	array();
	~array();

	/**
	 * @brief attach a new buffer to the vertex array
	 * 
	 * @param index The index of the buffer in the shader's layout
	 * @param size 1,2,3, or 4
	 * @return buffer* the generated buffer.
	 */
	buffer* gen_buffer(GLuint index, GLuint size);

	/**
	 * @brief bind a new element buffer to the vertex array 
	 * 
	 * @return buffer* a pointer to the element buffer
	 */
	buffer* gen_element_buffer();

	/**
	 * @brief disable an attribute in this array
	 * 
	 * @param index The attribute index
	 */
	void disable_attrib(GLuint index);

	void set_primitive(primitive p);
	primitive get_primitive() const;

	/// sets the internal vertex count of the vao
	void set_vertex_ct(GLuint ct);

	/**
	 * @brief draw the vertex array
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

	std::vector<buffer*> m_buffers;

	/// bind the vertex array for editing
	void bind();
	/// unbind the vertex array
	void unbind();
};

}
