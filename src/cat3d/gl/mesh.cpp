#include "cat3d/gl/mesh.hpp"

#include <OBJ_Loader/OBJ_Loader.h>

namespace cat3d::gl {

mesh::mesh() {
}

mesh::mesh(std::vector<GLfloat> p,
		   std::vector<GLfloat> u,
		   std::vector<GLfloat> n,
		   std::vector<unsigned int> e)
	: m_positions(p),
	  m_uvs(u),
	  m_norms(n),
	  m_elems(e) {
}

const std::vector<GLfloat>& mesh::positions() const {
	return m_positions;
}

const std::vector<GLfloat>& mesh::uvs() const {
	return m_uvs;
}

const std::vector<GLfloat>& mesh::normals() const {
	return m_norms;
}

const std::vector<unsigned int>& mesh::indices() const {
	return m_elems;
}

std::vector<mesh> mesh::load_file(const std::string& file) {
	objl::Loader l;
	l.LoadFile(file);

	std::vector<mesh> meshes;

	for (auto& mesh : l.LoadedMeshes) {
		std::vector<GLfloat> positions;
		std::vector<GLfloat> uvs;
		std::vector<GLfloat> norms;
		std::vector<unsigned int> elems;

		for (auto& v : mesh.Vertices) {
			positions.push_back(v.Position.X);
			positions.push_back(v.Position.Y);
			positions.push_back(v.Position.Z);

			uvs.push_back(v.TextureCoordinate.X);
			uvs.push_back(1 - v.TextureCoordinate.Y);

			norms.push_back(v.Normal.X);
			norms.push_back(v.Normal.Y);
			norms.push_back(v.Normal.Z);
		}

		elems = mesh.Indices;

		meshes.push_back(gl::mesh(positions, uvs, norms, elems));
	}

	return meshes;
}
}
