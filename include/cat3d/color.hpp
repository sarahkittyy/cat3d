#pragma once

namespace cat3d {

/**
 * @brief Base color class.
 * 
 * @remarks Stored internally as an OpenGL color, from 0-1.
 * 
 */
class color {
public:
	/**
	 * @brief Generate a color from standard 0-255 RGBA values.
	 * 
	 * @param r 
	 * @param g 
	 * @param b 
	 * @param a 
	 */
	static color from_rgb(float r = 0, float g = 0, float b = 0, float a = 255);

	/**
	 * @brief Generate a color from clamped OpenGL 0-1 RGBA values
	 * 
	 * @param r 
	 * @param g 
	 * @param b 
	 * @param a 
	 * @return color 
	 */
	static color from_rgb_clamped(float r = 0, float g = 0, float b = 0, float a = 1);

	float r = 0;
	float g = 0;
	float b = 0;
	float a = 1;
};

}