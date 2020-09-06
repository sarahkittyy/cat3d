#pragma once

#include <GL/glew.h>

#include <string>
#include <vector>

namespace cat3d::gl {

/**
 * @brief A mesh object.
 */
class mesh {
public:
	mesh();

	/**
	 * @brief Load meshes from an object file.
	 *
	 * @param file The file to load from.
	 */
	static std::vector<mesh> load_file(const std::string& file);

	/**
	 * @brief Return the mesh vertex positions
	 *
	 * @returns const std::vector<GLfloat>&
	 */
	const std::vector<GLfloat>& positions() const;

	/**
	 * @brief Return the mesh vertex texture coords
	 *
	 * @returns const std::vector<GLfloat>&
	 */
	const std::vector<GLfloat>& uvs() const;

	/**
	 * @brief Return the mesh vertex normals
	 *
	 * @returns const std::vector<GLfloat>&
	 */
	const std::vector<GLfloat>& normals() const;

	/**
	 * @brief Return the mesh indices
	 *
	 * @returns const std::vector<unsigned int>&
	 */
	const std::vector<unsigned int>& indices() const;

private:
	/// private constructor for initializing in load_file
	mesh(std::vector<GLfloat> p,
		 std::vector<GLfloat> u,
		 std::vector<GLfloat> n,
		 std::vector<unsigned int> e);

	std::vector<GLfloat> m_positions;
	std::vector<GLfloat> m_uvs;
	std::vector<GLfloat> m_norms;
	std::vector<unsigned int> m_elems;
};

}
