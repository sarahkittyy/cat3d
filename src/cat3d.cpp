#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdexcept>
#include <string>
#include <vector>

#include "cat3d.hpp"
#include "cat3d/color.hpp"
#include "cat3d/gl/shader.hpp"
#include "cat3d/window.hpp"

namespace cat3d {

/// app options
static opts* m_opt = nullptr;
/// app window
static window* m_win = nullptr;
/// initialized?
static bool m_initd = false;

/// allocated scenes
static std::vector<scene::node*> m_scenes;

/// default shader
static gl::shader* m_shader;

/**
 * @brief free all resources at program termination
 * 
 */
void deallocate() {
	delete m_opt;
	delete m_win;
	delete m_shader;

	for (auto& i : m_scenes) {
		delete i;
	}
	m_scenes.clear();
}

//----------------------------------------------

void init(opts opt) {
	m_opt = new opts(opt);

	glewExperimental = true;

	if (!glfwInit()) {
		throw std::runtime_error("Could not initialize glfw.");
	}

	int width		  = m_opt->get<int>(cat3d::WIDTH, 800);
	int height		  = m_opt->get<int>(cat3d::HEIGHT, 600);
	const char* title = m_opt->get<const char*>(cat3d::TITLE, "untitled");

	m_win = new window(width, height, title);

	if (glewInit() != GLEW_OK) {
		glfwTerminate();
		throw std::runtime_error("Could not initialize glew.");
	}

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_shader = new gl::shader();
	m_shader->bind();

	m_initd = true;
}

//-----------------------------------------------------

int run() {
	if (!m_initd) {
		throw std::runtime_error("Engine not initialized!");
	}

	color clear_color = m_opt->get<color>(cat3d::CLEAR_COLOR, color());

	// app loop
	while (m_win->is_open()) {
		for (auto& i : m_scenes) {
			i->update(*m_win);
		}

		m_win->clear(clear_color);

		for (auto& i : m_scenes) {
			i->render(*m_win);
		}

		m_win->flip();
	}

	deallocate();

	return 0;
}

//--------------------------------------------------------------

scene::node* new_scene() {
	scene::node* n = scene::node::new_root();
	m_scenes.push_back(n);
	return n;
}

//--------------------------------------------------------------

}
