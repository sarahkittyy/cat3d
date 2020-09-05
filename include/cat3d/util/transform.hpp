#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

namespace cat3d::util {

/**
 * @brief for abstracting away matrix transformation logic
 * 
 */
class transform {
public:
	/// init to the identity matrix
	transform();

	/**
	 * @brief resets the transform to the identity matrix
	 * 
	 */
	void reset();

	/// the default identity matrix
	static transform identity;

	/**
	 * @brief convert the transform to a matrix
	 * 
	 * @return glm::mat4 
	 */
	glm::mat4 to_mat4() const;

	/// set the matrix translation
	void set_pos(glm::vec3 p);
	/// get the matrix translation
	glm::vec3 get_pos() const;
	/// update the matrix translation
	transform& move(glm::vec3 p);

	/// set the rotation in euler angles
	void set_rotation(glm::vec3 angles);
	/// get the rotation, in euler angles
	glm::vec3 get_rotation() const;
	/// rotate by the given euler angles
	transform& rotate(glm::vec3 angles);

	/// set the scale
	void set_scale(glm::vec3 s);
	/// get the scale
	glm::vec3 get_scale() const;
	/// scale the transform
	transform& scale(glm::vec3 s);

	/// combine another transform with this one and return the new transform
	transform operator*(const transform& other) const;
	/// combine another transform with this one
	transform& operator*=(const transform& other);

private:
	/// internal transformations to combine in to_mat4()
	glm::vec3 m_translation;
	glm::quat m_rotation;
	glm::vec3 m_scaling;
};

}