# cat3d

![badge](https://github.com/sarahkittyy/cat3d/workflows/build/badge.svg)

A tiny OpenGL 3D engine library written in and for C++.

## Dependencies

- [glfw3](https://www.glfw.org/)
- [GLEW](http://glew.sourceforge.net/)

## Building from source

This project is built using CMake

```bash
cd build
cmake \
    -DBUILD_TESTS=ON \
    -DBUILD_EXAMPLES=ON \
    ..
make
```

To run the tests, use:

```bash
make test
```

## Docs

You can view the docs [here.](https://sarahkittyy.github.io/cat3d)

## Examples

More examples are located in the [`examples/`](examples/) directory.

```cpp
#include <cat3d.hpp>

int main() {
	namespace obj = cat3d::obj;

    /// initialize cat3d
	cat3d::init(cat3d::opts(
		{ { cat3d::WIDTH, 800 },
		  { cat3d::HEIGHT, 600 },
		  { cat3d::TITLE, "spinning-cube" },
		  { cat3d::CLEAR_COLOR, cat3d::color::from_rgb(100, 242, 245) } }));

    /// set up the scene
	cat3d::scene::node* root = cat3d::new_scene();

	obj::camera* cam = root->create<obj::camera>(glm::vec3(0, 2, -4), glm::vec3(0, 0, 0), 75.f);
	obj::model* cube = root->create<obj::model>("examples/cube.obj");

    /// attach a timer onto the cube to rotate it each frame
	cube->create<obj::timer>([cube](cat3d::util::time dt) {
		float dts = dt.as_seconds();
		cube->transform().rotate(glm::vec3(1.f * dts, 0.2f * dts, 0));
	});

    /// run the engine
	return cat3d::run();
}
```

![Gif of above example](https://raw.githubusercontent.com/sarahkittyy/cat3d/master/examples/spinning-cube.gif)
