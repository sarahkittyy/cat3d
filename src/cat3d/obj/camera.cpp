#include "cat3d/obj/camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace cat3d::obj {

camera::camera(glm::vec3 pos, glm::vec3 aim, float fov)
	: m_pos(pos), m_aim(aim), m_fov(fov) {
}

void camera::set_pos(glm::vec3 new_pos) {
	m_pos = new_pos;
}

glm::vec3 camera::get_pos() const {
	return m_pos;
}

void camera::set_aim(glm::vec3 new_aim) {
	m_aim = new_aim;
}

glm::vec3 camera::get_aim() const {
	return m_aim;
}

void camera::update_self(window& win) {
	win.set_view(view_matrix());
	win.set_proj(proj_matrix(win));
}

glm::mat4 camera::view_matrix() const {
	return glm::lookAt(m_pos, m_aim, glm::vec3(0, 1, 0));
}

glm::mat4 camera::proj_matrix(window& win) const {
	return glm::perspective(glm::radians(m_fov), float(win.size().x) / float(win.size().y), 0.1f, 1000.f);
}

}
