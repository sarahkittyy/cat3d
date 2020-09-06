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
	if (m_root) {
		throw std::runtime_error("No parent of a root element!");
	}
	return m_parent;
}

void node::update(window& win) {
	run_hooks(PRE_UPDATE);
	update_self(win);
	for (auto& i : m_children) {
		i->update(win);
	}
	run_hooks(POST_UPDATE);
}

void node::render(window& win) {
	glBindTexture(GL_TEXTURE_2D, 0);
	run_hooks(PRE_RENDER);
	push_transform(win);
	render_self(win);
	for (auto& i : m_children) {
		i->render(win);
	}
	run_hooks(POST_RENDER);
}

void node::update_self(window& win) {
}

void node::render_self(window& win) {
}

size_t node::bind(node_bind_loc loc, std::function<void()> fn) {
	size_t id = m_next_hook_id++;
	m_hooks[id] = std::make_pair(loc, fn);
	return id;
}

void node::unbind(size_t id) {
	m_hooks.erase(id);
}

void node::run_hooks(node_bind_loc loc) {
	std::for_each(
		m_hooks.begin(), m_hooks.end(),
		[&loc](const auto& p) {
			if (p.second.first == loc) {
				p.second.second();
			}
		});
}

util::transform& node::transform() {
	return m_transform;
}

void node::push_transform(window& win) {
	win.set_transform(global_transform().to_mat4());
}

node* node::create_node() {
	node* n		= new node();
	n->m_root	= false;
	n->m_parent = this;
	m_children.push_back(n);
	return n;
}

}
