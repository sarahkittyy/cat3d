#pragma once

#include <glm/glm.hpp>

#include "cat3d/scene.hpp"

namespace cat3d::obj {

/**
 * @brief Node for managing the camera's perspective on the scene.
 * 
 * @remarks Typically you only ever want one of these.
 * 
 */
class camera : public scene::node {
public:
	/**
	 * @brief Constructor
	 * 
	 * @param pos The position of the camera
	 * @param aim Where the camera should aim
	 * @param fov The FOV of the camera.
	 */
	camera(glm::vec3 pos, glm::vec3 aim, float fov = 75.f);

	/**
	 * @brief Set the camera's center
	 * 
	 * @param new_pos 
	 */
	void set_pos(glm::vec3 new_pos);
	/**
	 * @brief Retrieve the camera's center
	 * 
	 * @return glm::vec3 
	 */
	glm::vec3 get_pos() const;

	/**
	 * @brief Set the location that the camera points towards.
	 * 
	 * @param new_aim
	 */
	void set_aim(glm::vec3 new_aim);
	/**
	 * @brief Get the camera's currently focused point.
	 * 
	 * @return glm::vec3 
	 */
	glm::vec3 get_aim() const;

protected:
	void update_self(window& win);

private:
	/// where the camera is positioned
	glm::vec3 m_pos;
	/// where the camera is aiming
	glm::vec3 m_aim;
	/// the camera's fov
	float m_fov;

	/// convert this camera data into a view matrix
	glm::mat4 view_matrix() const;
	/// convert this camera data into a projection matrix
	glm::mat4 proj_matrix(window& win) const;
};

}
