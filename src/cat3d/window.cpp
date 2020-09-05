#include "cat3d/window.hpp"

#include <stdexcept>

namespace cat3d {

template <>
void window::set_uniform(const char* name, glm::mat4& value) {
	GLuint loc = glGetUniformLocation(program(), name);
	glUniformMatrix4fv(loc, 1, GL_FALSE, &value[0][0]);
}

window::window(unsigned int width, unsigned int height, const char* title) {
	m_win = glfwCreateWindow(width, height, title, nullptr, nullptr);
	if (!m_win) {
		throw std::runtime_error("Could not open GLFW window!");
	}

	glfwMakeContextCurrent(m_win);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
}

window::~window() {
	glfwTerminate();
}

bool window::is_open() const {
	return !glfwWindowShouldClose(m_win);
}

void window::clear(color clear_color) {
	glClearColor(clear_color.r, clear_color.g, clear_color.b, clear_color.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void window::flip() {
	glfwSwapBuffers(m_win);
	glfwPollEvents();
}

glm::vec2 window::size() const {
	int w;
	int h;
	glfwGetWindowSize(m_win, &w, &h);
	return glm::vec2(w, h);
}

GLuint window::program() {
	GLint id;
	glGetIntegerv(GL_CURRENT_PROGRAM, &id);
	return GLuint(id);
}

void window::set_transform(glm::mat4 mat) {
	set_uniform("model", mat);
}

void window::set_view(glm::mat4 v) {
	set_uniform("view", v);
}

void window::set_proj(glm::mat4 p) {
	set_uniform("proj", p);
}

}