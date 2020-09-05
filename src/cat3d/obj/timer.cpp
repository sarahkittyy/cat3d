#include "cat3d/obj/timer.hpp"

namespace cat3d::obj {

timer::timer(std::function<void(util::time dt)> fn, util::time interval, int ct)
	: m_fn(fn), m_ivl(interval), m_ct(ct) {
}

void timer::update_self(window& win) {
	if (m_ct == 0) return;

	if (m_clock.elapsed() > m_ivl) {
		if (m_ct != -1) {
			m_ct--;
		}
		m_fn(m_clock.restart());
	}
}

}