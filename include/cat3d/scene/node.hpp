#pragma once

#include <functional>
#include <glm/glm.hpp>
#include <vector>

#include "cat3d/util/clock.hpp"
#include "cat3d/util/transform.hpp"
#include "cat3d/window.hpp"

namespace cat3d::scene {

/**
 * @brief Basic, semi-abstract scene node class. Can have children which are other scene nodes, or derived types.
 * 
 */
class node {
public:
	node();

	/**
	 * @brief Create a new root scene node.
	 * 
	 * @return node* 
	 */
	static node* new_root();

	/// virtual destructor for polymorphism
	virtual ~node();

	/**
	 * @brief Remove the given child node.
	 * 
	 * @param child A child of this node
	 */
	void delete_child(node* child);

	/**
	 * @brief Get this node's transform relative to the world.
	 * 
	 */
	util::transform global_transform() const;

	/**
	 * @brief Get the node's transform relative to itself.
	 * 
	 */
	util::transform local_transform() const;

	/**
	 * @brief Access to the underlying transform.
	 * 
	 * @remarks Safe to modify
	 * 
	 * @return util::transform& Reference to this node's transform.
	 */
	util::transform& transform();

	/**
	 * @brief Called once per frame. Updates this node.
	 * 
	 */
	void update(window& win);

	/**
	 * @brief Called once per render. Renders this node and all children.
	 * 
	 */
	void render(window& win);

	/**
	 * @brief Get this node's parent
	 * 
	 * @return node* 
	 */
	node* parent() const;

	/**
	 * @brief Create a child node
	 * 
	 * @return node* The created node
	 */
	node* create_node();

	/**
	 * @brief Add a derived node class as a child
	 * 
	 * @remarks These are typically found in cat3d/obj
	 * 
	 * @tparam Obj The type of object to add
	 * @tparam Args The arguemnts passed to the constructor
	 * @return Obj* Pointer to the newly created node instance
	 */
	template <typename Obj, typename... Args>
	Obj* create(Args... args) {
		Obj* o		= new Obj(args...);
		o->m_root	= false;
		o->m_parent = this;
		m_children.push_back((node*)o);
		return o;
	}

protected:
	/**
	 * @brief Overridden by child classes to implement custom behavior
	 * 
	 * @param win The main cat3d window.
	 */
	virtual void update_self(window& win);

	/**
	 * @brief Overridden by child classes to implement custom rendering
	 * 
	 * @param win The main cat3d window.
	 */
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