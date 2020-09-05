#include "cat3d/scene/node.hpp"

#include <algorithm>
#include "cat3d/obj.hpp"

namespace cat3d::scene {

node* node::new_root() {
	node* n	  = new node();
	n->m_root = true;
	return n;
}

node::node() {
}

node::~node() {
	// deallocate all child nodes
	for (auto& i : m_children) {
		delete i;
	}
}

void node::delete_child(node* c) {
	std::remove(m_children.begin(), m_children.end(), c);
	delete c;
}

util::transform node::global_transform() const {
	if (m_root) {
		return m_transform;
	} else {
		return m_parent->global_transform() * m_transform;
	}
}

util::transform node::local_transform() const {
	return m_transform;
}

node* node::parent() const {
	return m_parent;
}

void node::update(window& win) {
	update_self(win);
	for (auto& i : m_children) {
		i->update(win);
	}
}

void node::render(window& win) {
	push_transform(win);
	render_self(win);
	for (auto& i : m_children) {
		i->render(win);
	}
}

void node::update_self(window& win) {
}

void node::render_self(window& win) {
}

util::transform& node::transform() {
	return m_transform;
}

void node::push_transform(window& win) {
	win.set_transform(global_transform().to_mat4());
}

CREATOR_IMPL_DEF(node) {
	node* n		= new node();
	n->m_root	= false;
	n->m_parent = this;
	m_children.push_back(n);
	return n;
}

CREATOR_IMPL_DEF(camera, glm::vec3 pos, glm::vec3 aim, float fov) {
	CREATOR_IMPL(camera, pos, aim, fov);
}

CREATOR_IMPL_DEF(model, const std::string& file) {
	CREATOR_IMPL(model, file);
}

CREATOR_IMPL_DEF(timer, std::function<void(util::time)> fn, util::time interval, int ct) {
	CREATOR_IMPL(timer, fn, interval, ct);
}

}