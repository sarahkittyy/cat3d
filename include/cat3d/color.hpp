#pragma once

namespace cat3d {

/**
 * @brief Base color class.
 * 
 */
class color {
public:
	static color from_rgb(float r = 0, float g = 0, float b = 0, float a = 255);
	static color from_rgb_clamped(float r = 0, float g = 0, float b = 0, float a = 1);

	float r = 0;
	float g = 0;
	float b = 0;
	float a = 1;
};

}