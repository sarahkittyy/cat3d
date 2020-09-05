#include "cat3d/color.hpp"

#include "cat3d/util/map.hpp"

namespace cat3d {

color color::from_rgb(float r, float g, float b, float a) {
	color c;
	c.r = util::map<float>(r, 0, 255, 0, 1);
	c.g = util::map<float>(g, 0, 255, 0, 1);
	c.b = util::map<float>(b, 0, 255, 0, 1);
	c.a = util::map<float>(a, 0, 255, 0, 1);
	return c;
}

color color::from_rgb_clamped(float r, float g, float b, float a) {
	color c;
	c.r = r;
	c.g = g;
	c.b = b;
	c.a = a;
	return c;
}

}