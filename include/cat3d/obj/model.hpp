#pragma once

#include "cat3d/gl.hpp"
#include "cat3d/scene.hpp"

namespace cat3d::obj {

/**
 * @brief Node for rendering models onto the scene
 * 
 */
class model : public scene::node {
public:
	/**
	 * @brief Constructor
	 * 
	 * @param path Path to the .obj file.
	 */
	model(const std::string& path);

protected:
	void update_self(window& win);

	void render_self(window& win);

private:
	/// internal vertex array
	gl::array m_arr;
};

}