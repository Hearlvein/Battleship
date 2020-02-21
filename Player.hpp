#pragma once

#include "Grid.hpp"
#include "Ship.hpp"
#include "declarations.hpp"
#include "functions.hpp"
#include "ResourceLibrary.hpp"

class Player
{
public:
	Player(sf::RenderWindow* window, ResourceLibrary* resourceLibrary):
		m_window(window), m_resourceLibrary(resourceLibrary)
	{
		/*sf::Vector2u a(0, 0);
		sf::Vector2u b(1, 0);
		sf::Vector2u c(0, 1);
		sf::Vector2u d(2, 1);
		sf::Vector2u e(0, 2);
		sf::Vector2u f(3, 2);
		sf::Vector2u g(0, 3);
		sf::Vector2u h(4, 3);

		addShip(a, b);
		addShip(c, d);
		addShip(e, f);
		addShip(g, h);*/
	}

	~Player()
	{

	}

	void addShip(sf::Vector2u& beginning, sf::Vector2u& end)
	{
		// Mustnt exceed limit of allowed ships
		if (everyShipsReady())
        {
            debugMsg("Enough ships for this player");
            return;
        }

        std::cout << "beginning(" << beginning.x << ";" << beginning.y << ") & end(" << end.x << ";" << end.y << ")" << std::endl;

		// ship cant be diag
		if (beginning.x != end.x && beginning.y != end.y)
		{
			debugMsg("diag ship");
			return;
		}

		// Getting size
		std::size_t size = 0;

		if (beginning.x == end.x)	// Vertical ship
		{
			if (beginning.y > end.y)	// Swap
			{
				std::size_t temp = beginning.y;
				beginning.y = end.y;
				end.y = temp;
				debugMsg("Vertical swap");
			}

			size = end.y - beginning.y + 1;	// Retrieving ship size
		}
		else if (beginning.y == end.y)	// Horizontal ship
		{
			if (beginning.x > end.x)	// Swap
			{
				std::size_t temp = beginning.x;
				beginning.x = end.x;
				end.x = temp;
				debugMsg("Horizontal swap");
			}

			size = end.x - beginning.x + 1;	// Retrieving ship size
		}

        std::cout << "ship size: " << size << std::endl;

		// Size-based restrictions
		if (size < 2 || size > 5)	// Out-of-range ship size
		{
			debugMsg("size too short or too long");
			return;
		}

		// Uniqueless of size
		for (const Ship& ship : m_ships)
			if (ship.getSize() == size)	// Another ship has already the same size
			{
				std::cout << "ship not allowed: same size (" << size << ") already exists" << std::endl;
				return;
			}

		// Construct array of cells
		std::list<sf::Vector2u> shipCells;

		if (beginning.x == end.x)	// Vertical ship
			for (std::size_t i = 0; i < size; ++i)
				shipCells.push_back(sf::Vector2u(beginning.x, beginning.y + i));

		else if (beginning.y == end.y) 	// Horizontal ship
			for (std::size_t i = 0; i < size; ++i)
				shipCells.push_back(sf::Vector2u(beginning.x + i, beginning.y));

		// Ships mustnt overlap
		for (const sf::Vector2u& newShipCell : shipCells)
			if (m_shipsGrid.get(newShipCell.x, newShipCell.y) == ShipTile)
			{
				std::cout << "overlapping at " << newShipCell.x << ";" << newShipCell.y << std::endl;
				return;
			}

		// Registering ship in ships list
		m_ships.push_back(Ship(shipCells));
		std::cout << "ship added. number of ships = " << m_ships.size() << std::endl;

		// Registering ship in ships grid
		for (const sf::Vector2u& cell : shipCells)
			m_shipsGrid.set(cell.x, cell.y, ShipTile);
	}

	bool everyShipsReady() const
	{
		return m_ships.size() == MAX_NUMBER_SHIPS;
	}

	void drawShipsGrid(float x, float y)
	{
		drawGrid(x, y, &m_shipsGrid);
	}

	void drawAttackGrid(float x, float y)
	{
		drawGrid(x, y, &m_attackGrid);
	}

	bool neverShotThere(std::size_t x, std::size_t y)
	{
		return m_attackGrid.get(x, y) == SeaTile;
	}

	bool isShipCell(std::size_t x, std::size_t y)
	{
		return m_shipsGrid.get(x, y) == ShipTile;
	}

	void registerShot(std::size_t x, std::size_t y, TileType newValue)
	{
		m_attackGrid.set(x, y, newValue);
	}

	void removeShipCell(std::size_t x, std::size_t y)
	{
		// Remove from ships collection
		for (std::vector<Ship>::iterator it = m_ships.begin(); it != m_ships.end(); ++it)
		{
			bool shipDestroyed = false;

			if (it->removeCell(x, y, shipDestroyed))
			{
				if (shipDestroyed)
				{
					m_ships.erase(it);
					std::cout << "A ship has been removed. " << m_ships.size() << " other ships remaining" << std::endl;
				}

				break;
			}
		}

		// Remove from ships grid
		m_shipsGrid.set(x, y, HitTile);
	}

	bool hasNoShip() const
	{
        return m_ships.empty();
	}

private:
	void drawGrid(float x, float y, Grid* grid)
	{
		for (std::size_t i = 0; i < GRID_WIDTH; ++i)
			for (std::size_t j = 0; j < GRID_HEIGHT; ++j)
			{
				sf::Sprite* cell(m_resourceLibrary->get(grid->get(i, j)));
				cell->setPosition(x + (i + 1) * TILE_SIZE, y + (j + 1) * TILE_SIZE);
				m_window->draw(*cell);
			}
	}

	sf::RenderWindow* m_window = nullptr;
	ResourceLibrary* m_resourceLibrary = nullptr;
	std::vector<Ship> m_ships;
	Grid m_shipsGrid;
	Grid m_attackGrid;
};
