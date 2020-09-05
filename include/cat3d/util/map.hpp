#pragma once

namespace cat3d::util {

/**
 * @brief Map an integer from one range to another
 * 
 * @tparam Number 
 * @param v The value
 * @param lo The old minumum
 * @param hi The old maximum
 * @param newlo The new minimum
 * @param newhi The new maximum
 * @return Number 
 */
template <typename Number>
Number map(Number v, Number lo, Number hi, Number newlo, Number newhi);

}