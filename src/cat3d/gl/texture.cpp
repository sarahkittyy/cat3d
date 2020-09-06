#include "cat3d/gl/texture.hpp"
#include "cat3d/util/map.hpp"

#include <stdexcept>

namespace cat3d::gl {

texture::texture()
	: m_loaded(false),
	  m_bind_state(false) {
	glGenTextures(1, &m_tex);
}

void texture::del() {
	glDeleteTextures(1, &m_tex);
}

void texture::load_file(const std::string& path) {
	if (m_loaded) {
		throw std::runtime_error("Texture is already loaded!");
	}
	m_loaded = true;

	int w, h, nc;
	unsigned char* data = stbi_load(path.c_str(), &w, &h, &nc, 0);

	if (!data) {
		throw std::runtime_error("Could not load texture @ " + path + ".");
	}

	push_bind_state();
	bind();

	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		nc == 4 ? GL_RGBA : GL_RGB,
		w,
		h,
		0,
		nc == 4 ? GL_RGBA : GL_RGB,
		GL_UNSIGNED_BYTE,
		data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);

	pop_bind_state();
}

void texture::load_color(color col) {
	if (m_loaded) {
		throw std::runtime_error("Texture is already loaded!");
	}
	m_loaded = true;

	unsigned char* data = new unsigned char[4];
	data[0]				= (unsigned char)util::map<float>(col.r, 0, 1, 0, 255);
	data[1]				= (unsigned char)util::map<float>(col.g, 0, 1, 0, 255);
	data[2]				= (unsigned char)util::map<float>(col.b, 0, 1, 0, 255);
	data[3]				= (unsigned char)util::map<float>(col.a, 0, 1, 0, 255);

	push_bind_state();
	bind();

	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RGBA,
		1,
		1,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		data);

	pop_bind_state();

	delete[] data;
}

void texture::set_wrap_mode(texture_wrap_mode mode) {
	push_bind_state();
	bind();

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, mode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, mode);

	pop_bind_state();
}

void texture::set_border_color(color col) {
	push_bind_state();
	bind();

	float c[] = { col.r, col.g, col.b, col.a };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, c);

	pop_bind_state();
}

void texture::set_filter_mode(texture_filter_mode mode) {
	push_bind_state();
	bind();

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mode);

	pop_bind_state();
}

void texture::bind() {
	glBindTexture(GL_TEXTURE_2D, m_tex);
}

void texture::unbind() {
	glBindTexture(GL_TEXTURE_2D, 0);
}

void texture::push_bind_state() {
	GLint v;
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &v);
	m_bind_state = v == m_tex;
}

void texture::pop_bind_state() {
	if (m_bind_state) {
		bind();
	} else {
		unbind();
	}
}

}
