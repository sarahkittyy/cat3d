#include "cat3d/obj/model.hpp"
#include "OBJ_Loader/OBJ_Loader.h"

namespace cat3d::obj {

model::model(const std::string& path) {
	m_arr.set_primitive(gl::Triangles);

	objl::Loader l;
	l.LoadFile(path);

	size_t pos_b = m_arr.gen_buffer(0, 3);
	m_arr.disable_attrib(1);
	size_t uv_b		 = m_arr.gen_buffer(2, 2);
	size_t normal_b	 = m_arr.gen_buffer(3, 3);
	size_t element_b = m_arr.gen_element_buffer();

	std::vector<GLfloat> positions;
	std::vector<GLfloat> uvs;
	std::vector<GLfloat> norms;
	std::vector<unsigned int> elements;

	for (auto& v : l.LoadedVertices) {
		positions.push_back(v.Position.X);
		positions.push_back(v.Position.Y);
		positions.push_back(v.Position.Z);

		uvs.push_back(v.TextureCoordinate.X);
		uvs.push_back(v.TextureCoordinate.Y);

		norms.push_back(v.Normal.X);
		norms.push_back(v.Normal.Y);
		norms.push_back(v.Normal.Z);
	}

	elements = l.LoadedIndices;

	m_arr.get_buffer(pos_b).set_data(positions);
	m_arr.get_buffer(uv_b).set_data(uvs);
	m_arr.get_buffer(normal_b).set_data(norms);
	m_arr.get_buffer(element_b).set_data(elements);

	m_arr.set_vertex_ct(elements.size());
}

void model::update_self(window& win) {
}

void model::render_self(window& win) {
	m_arr.render();
}

}
