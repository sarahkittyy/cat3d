#include "cat3d/gl/array.hpp"

#include <stdexcept>

namespace cat3d::gl {

array::array() {
	glGenVertexArrays(1, &m_vao);
}

void array::del() {
	glDeleteVertexArrays(1, &m_vao);
}

void array::bind() {
	glBindVertexArray(m_vao);
}

void array::unbind() {
	glBindVertexArray(0);
}

void array::render() {
	if (m_buffers.size() == 0) {
		throw std::runtime_error("No buffers available to draw.");
	}

	bind();
	if (m_element_present) {
		glDrawElements(m_prim, m_vertex_ct, GL_UNSIGNED_INT, (void*)0);
	} else {
		glDrawArrays(m_prim, 0, m_vertex_ct);
	}
}

void array::set_primitive(primitive p) {
	m_prim = p;
}

primitive array::get_primitive() const {
	return m_prim;
}

void array::set_vertex_ct(GLuint ct) {
	m_vertex_ct = ct;
}

size_t array::gen_buffer(GLuint index, GLuint size) {
	bind();
	glEnableVertexAttribArray(index);

	m_buffers.push_back(buffer());
	buffer& nb = m_buffers.back();

	nb.set_type(buffer_type::Vertex);
	nb.m_parent		 = this;
	nb.m_vao_i		 = index;
	nb.m_vertex_size = size;

	return m_buffers.size() - 1;
}

size_t array::gen_element_buffer() {
	bind();
	if (m_element_present) {
		throw std::runtime_error("Cannot have more than one element buffer per array!");
	}
	m_element_present = true;

	m_buffers.push_back(buffer());
	buffer& nb = m_buffers.back();

	nb.set_type(buffer_type::Element);
	nb.m_parent = this;
	nb.m_vao_i	= -1;

	return m_buffers.size() - 1;
}

buffer& array::get_buffer(size_t id) {
	return m_buffers[id];
}

void array::disable_attrib(GLuint index) {
	bind();
	glDisableVertexAttribArray(index);
}

void array::enable_attrib(GLuint index) {
	bind();
	glEnableVertexAttribArray(index);
}
}
