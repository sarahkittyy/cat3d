#pragma once

#include <chrono>

namespace cat3d::util {

/**
 * @brief data type for a length of time
 * 
 */
class time {
public:
	time();

	static time seconds(float s);
	static time milliseconds(unsigned long ms);
	static time minutes(float m);

	float to_seconds() const;
	unsigned long to_milliseconds() const;
	float to_minutes() const;

	time operator+(const time& other);
	time operator-(const time& other);
	time& operator+=(const time& other);
	time& operator-=(const time& other);

	bool operator>(const time& other);
	bool operator<(const time& other);
	bool operator>=(const time& other);
	bool operator<=(const time& other);

	bool operator==(const time& other);
	bool operator!=(const time& other);

private:
	time(unsigned long ms);

	/// internally store duration as milliseconds
	unsigned long m_ms;
};

/**
 * @brief internal class for timing purposes
 * 
 */
class clock {
public:
	clock();

	time restart();
	time elapsed() const;

private:
	/// start point of the clock
	std::chrono::time_point<std::chrono::steady_clock> m_start;
};

}