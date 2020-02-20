#pragma once

#include <iostream>
#include <sstream>

bool isCorrectGridPosition(const std::size_t x, const std::size_t y)
{
	if (x >= 0 && x < GRID_WIDTH && y >= 0 && y < GRID_HEIGHT)
		return true;

	return false;
}

void debugMsg(const char* msg)
{
	if (DEBUG)
		std::cout << msg << std::endl;
}

int abs_val(int x)
{
    if (x < 0)
        return -x;
    return x;
}

void swap_val(int a, int b)
{
    int temp = a;
    a = b;
    b = temp;
}

template <class T>
std::ostream& operator<<(std::ostream& out, const sf::Vector2<T>& vec)
{
    out << "(" << vec.x << ";" << vec.y << ")";
    return out;
}

std::string int2string(int n)
{
	std::ostringstream stream;
	stream << n;
	return stream.str();
}
