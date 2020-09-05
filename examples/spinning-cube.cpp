#include <cat3d.hpp>

int main() {
	namespace obj = cat3d::obj;

	cat3d::init(cat3d::opts(
		{ { cat3d::WIDTH, 800 },
		  { cat3d::HEIGHT, 600 },
		  { cat3d::TITLE, "spinning-cube" },
		  { cat3d::CLEAR_COLOR, cat3d::color::from_rgb(100, 242, 245) } }));

	cat3d::scene::node* root = cat3d::new_scene();

	obj::camera* cam = root->create<obj::camera>(glm::vec3(0, 2, -4), glm::vec3(0, 0, 0), 75.f);
	obj::model* cube = root->create<obj::model>("examples/cube.obj");

	cube->create<obj::timer>([cube](cat3d::util::time dt) {
		float dts = dt.to_seconds();
		cube->transform().rotate(glm::vec3(1.f * dts, 0.2f * dts, 0));
	});

	return cat3d::run();
}