#pragma once

#include <functional>

#include "cat3d/scene.hpp"
#include "cat3d/util/clock.hpp"

namespace cat3d::obj {

/**
 * @brief for running events on an interval / timer
 * 
 */
class timer : public scene::node {
public:
	/**
	 * @brief Run a function on a timer
	 * 
	 * @param fn The function to call
	 * @param interval The time between each call
	 * @param ct How many times to run the function before terminating, -1 = infinite.
	 */
	timer(std::function<void(util::time dt)> fn, util::time interval = util::time(), int ct = -1);

protected:
	void update_self(window& win);

private:
	/// internal clock for timing purposes
	util::clock m_clock;

	/// function to run on each interval
	std::function<void(util::time dt)> m_fn;

	/// the length of each interval
	util::time m_ivl;

	/// amount of times to run the function
	int m_ct;
};

}