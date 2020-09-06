#include "cat3d/gl/texture.hpp"

#include <iostream>
#include <stdexcept>

namespace cat3d::gl {

texture::texture() {
	glGenTextures(1, &m_tex);
}

void texture::del() {
	glDeleteTextures(1, &m_tex);
}

void texture::load_file(const std::string& path) {
	int w, h, nc;
	unsigned char* data = stbi_load(path.c_str(), &w, &h, &nc, 0);

	if (!data) {
		throw std::runtime_error("Could not load texture @ " + path + ".");
	}

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
}

void texture::bind() {
	glBindTexture(GL_TEXTURE_2D, m_tex);
}

}
