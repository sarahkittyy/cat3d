#include "cat3d/gl/shader.hpp"

#include <stdexcept>

namespace cat3d::gl {

shader::shader(const char* vs_source, const char* fs_source) {
	GLuint vert = 0;
	GLuint frag = 0;

	int success;
	char infolog[512];

	vert = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vert, 1, &vs_source, nullptr);
	glCompileShader(vert);

	glGetShaderiv(vert, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vert, 512, nullptr, infolog);
		throw std::runtime_error("Could not compile vertex shader: " + std::string(infolog));
	}

	frag = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(frag, 1, &fs_source, nullptr);
	glCompileShader(frag);

	glGetShaderiv(frag, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(frag, 512, nullptr, infolog);
		throw std::runtime_error("Could not compile fragment shader: " + std::string(infolog));
	}

	m_prog = glCreateProgram();
	glAttachShader(m_prog, vert);
	glAttachShader(m_prog, frag);
	glLinkProgram(m_prog);

	glGetProgramiv(m_prog, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(m_prog, 512, nullptr, infolog);
		throw std::runtime_error("Could not link shader: " + std::string(infolog));
	}
}

void shader::del() {
	if (loaded()) {
		glDeleteProgram(m_prog);
	}
}

void shader::bind() {
	if (!loaded()) {
		throw std::runtime_error("Shader was never initialized!");
	}
	glUseProgram(m_prog);
}

bool shader::loaded() const {
	return glIsProgram(m_prog);
}

const char* shader::m_default_vs = R"/shader(
#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 uv;
layout(location = 2) in vec3 normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

out vec2 UV;
out vec3 normV;

void main() {
	gl_Position = proj * view * model * vec4(pos, 1.0);

	UV = uv;
	normV = normal;
}

)/shader";

const char* shader::m_default_fs = R"/shader(
#version 330 core

in vec2 UV;
in vec3 normV;

out vec4 color;

uniform sampler2D texture0;

void main() {
	color = texture(texture0, UV);
}

)/shader";

shader::shader()
	: shader(m_default_vs, m_default_fs) {
}

}
