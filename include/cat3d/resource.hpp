#pragma once

#include "cat3d/gl/texture.hpp"

namespace cat3d {

/**
 * @brief Primary app resource manager. Handles the loading / unloading of assets to conserve memory.
 */
class resource {
public:
	resource();
	~resource();

	/**
	 * @brief Get the default app resource manager
	 *
	 * @returns resource&
	 */
	static resource& get();

private:
	/// the primary app manager
	static resource m_primary;
};

}
