#pragma once

#include "cat3d/color.hpp"
#include "cat3d/obj.hpp"
#include "cat3d/opts.hpp"
#include "cat3d/scene.hpp"

namespace cat3d {

/**
 * @brief Initialize the cat3d engine.
 * 
 * @param opt Engine arguments
 * 
 */
void init(opts opt);

/**
 * @brief Run the engine
 * 
 * @return int the program's exit code 
 */
int run();

/**
 * @brief Create a new root scene node.
 * 
 * @return scene::node* A new blank scene node
 */
scene::node* new_scene();

}
