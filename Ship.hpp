#pragma once

#include <algorithm>
#include <iostream>
#include <list>
#include "functions.hpp"

class Ship
{
public:
	Ship(std::list<sf::Vector2u>& shipCells):
        m_cells(shipCells), m_name(int2string(getSize()) + " cells long")
	{
	}

	~Ship()
	{
	}

	void tellName() const
	{
		std::cout << m_name << std::endl;
	}

	const std::size_t getSize() const
	{
		return m_cells.size();
	}

	bool removeCell(std::size_t x, std::size_t y, bool& shipDestroyed)
	{
	    bool toReturn = false;
	    std::list<sf::Vector2u>::iterator found = std::find_if(m_cells.begin(), m_cells.end(), [&](const sf::Vector2u& cell) { return cell.x == x && cell.y == y; });
	    if (found != m_cells.end())
	    {
	    	m_cells.erase(found);
	    	toReturn = true;
	    }

		if (m_cells.empty())
		{
			std::cout << "ship [" << m_name << "] sunk" << std::endl;
			shipDestroyed = true;
		}

		return toReturn;
	}

private:
	std::list<sf::Vector2u> m_cells;
	std::string m_name;
};
