#include "cat3d/gl/buffer.hpp"
#include "cat3d/gl/array.hpp"

namespace cat3d::gl {

buffer::buffer() {
	glGenBuffers(1, &m_vbo);
}

void buffer::del() {
	glDeleteBuffers(1, &m_vbo);
}

GLuint buffer::index() const {
	return m_vao_i;
}

void buffer::set_type(buffer_type t) {
	m_type = t;
}

buffer_type buffer::get_type() const {
	return m_type;
}

void buffer::bind() {
	glBindBuffer(m_type, m_vbo);
}

void buffer::set_data_impl(void* data, size_t data_size, size_t data_type_size) {
	bind();
	glBufferData(m_type, data_size * data_type_size, data, GL_STATIC_DRAW);
	if (m_type != buffer_type::Element) {
		m_parent->set_vertex_ct(data_size / m_vertex_size);
		glVertexAttribPointer(m_vao_i, m_vertex_size, GL_FLOAT, GL_FALSE, 0, 0);
	}
}

}
