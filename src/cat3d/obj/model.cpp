#include "cat3d/obj/model.hpp"
#include "cat3d/resource.hpp"

namespace cat3d::obj {

model::model(const std::string& path) {
	const auto& meshes = resource::get().mesh(path);

	for (auto& mesh : meshes) {
		m_arrs.push_back(gl::array());
		gl::array& arr = m_arrs.back();

		arr.set_primitive(gl::Triangles);

		size_t pos_b	 = arr.gen_buffer(0, 3);
		size_t uv_b		 = arr.gen_buffer(1, 2);
		size_t normal_b	 = arr.gen_buffer(2, 3);
		size_t element_b = arr.gen_element_buffer();

		arr.get_buffer(pos_b).set_data(mesh.positions());
		arr.get_buffer(uv_b).set_data(mesh.uvs());
		arr.get_buffer(normal_b).set_data(mesh.normals());
		arr.get_buffer(element_b).set_data(mesh.indices());

		arr.set_vertex_ct(mesh.indices().size());
	}
}

void model::update_self(window& win) {
}

void model::render_self(window& win) {
	for (auto& i : m_arrs) {
		i.render();
	}
}

}
