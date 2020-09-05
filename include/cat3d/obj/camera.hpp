#pragma once

#include <glm/glm.hpp>

#include "cat3d/scene.hpp"

namespace cat3d::obj {

class camera : public scene::node {
public:
	camera(glm::vec3 pos, glm::vec3 aim, float fov);

	void set_pos(glm::vec3 new_pos);
	glm::vec3 get_pos() const;

	void set_aim(glm::vec3 new_aim);
	glm::vec3 get_aim() const;

protected:
	void update_self(window& win);

private:
	glm::vec3 m_pos;
	glm::vec3 m_aim;

	float m_fov;

	glm::mat4 view_matrix() const;
	glm::mat4 proj_matrix(window& win) const;
};

}