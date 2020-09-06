#pragma once

#include <any>
#include <stdexcept>
#include <unordered_map>

namespace cat3d {

enum opt {
	WIDTH,
	HEIGHT,
	TITLE,
	CLEAR_COLOR,
	ANTIALIASING

};

/**
 * @brief cat3d main configuration options class
 * 
 */
class opts {
public:
	typedef std::unordered_map<opt, std::any> opt_map;

	/**
	 * @brief initialize the options object
	 * 
	 * @param opt the map of key-value pairs corresponding to the program
	 */
	opts(opt_map opt);

	/**
	 * @brief Retrieve the value at the given key
	 * 
	 * @tparam T The type of value expected at this key
	 * @param key The key
	 * @return const T& A const reference to that value
	 */
	template <typename T>
	T get(opt key) const {
		return std::any_cast<T>(m_config.at(key));
	}

	/**
	 * @brief Retrieve the value at the given key
	 * 
	 * @tparam T The type of value expected at this key
	 * @param key The key
	 * @param fallback Fallback option if the key does not exist.
	 * @return const T& A const reference to that value
	 */
	template <typename T>
	T get(opt key, T fallback) const {
		try {
			return std::any_cast<T>(m_config.at(key));
		} catch (const std::out_of_range& e) {
			return fallback;
		}
	}

private:
	/// internal opt map storage
	opt_map m_config;
};

}
