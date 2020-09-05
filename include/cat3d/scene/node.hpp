#pragma once

#include <functional>
#include <glm/glm.hpp>
#include <vector>

#include "cat3d/util/clock.hpp"
#include "cat3d/util/transform.hpp"
#include "cat3d/window.hpp"

namespace cat3d::scene {

/**
 * @brief A scene node
 * 
 */
class node {
public:
	/// default constructor
	node();

	/**
	 * @brief Create a new root scene node.
	 * 
	 * @return node* 
	 */
	static node* new_root();

	/// virtual destructor for the node
	virtual ~node();

	/**
	 * @brief detach & deallocate the given child node
	 * 
	 * @param child 
	 */
	void delete_child(node* child);

	/**
	 * @brief get the node's model matrix relative to the world
	 * 
	 */
	util::transform global_transform() const;

	/**
	 * @brief get the node's model matrix relative to itself
	 * 
	 */
	util::transform local_transform() const;

	/// a modifiable, non-const version of local_transform
	util::transform& transform();

	/**
	 * @brief update this node and all children.
	 * 
	 */
	void update(window& win);

	/**
	 * @brief render this node and all children
	 * 
	 */
	void render(window& win);

	/**
	 * @brief Get this node's parent
	 * 
	 * @return node* 
	 */
	node* parent() const;

	node* create_node();

	template <typename Obj, typename... Args>
	Obj* create(Args... args) {
		Obj* o		= new Obj(args...);
		o->m_root	= false;
		o->m_parent = this;
		m_children.push_back((node*)o);
		return o;
	}

protected:
	/// update this node.
	virtual void update_self(window& win);

	/// render this node.
	virtual void render_self(window& win);

private:
	/// is this node a root node?
	bool m_root = false;

	/// this node's parent (nullptr if m_root)
	node* m_parent = nullptr;

	/// child nodes
	std::vector<node*> m_children;

	/// local transform
	util::transform m_transform;

	/// push the transform of this node to the window
	void push_transform(window& win);
};

}