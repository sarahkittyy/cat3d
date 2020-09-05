#pragma once

#include "cat3d/gl.hpp"
#include "cat3d/scene.hpp"

namespace cat3d::obj {

class model : public scene::node {
public:
	model(const std::string& path);

protected:
	void update_self(window& win);

	void render_self(window& win);

private:
	gl::array m_arr;
};

}