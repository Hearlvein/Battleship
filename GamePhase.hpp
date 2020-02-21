#pragma once

#include "ResourceLibrary.hpp"

class GamePhase
{
public:
	GamePhase(sf::RenderWindow* window, Player* players, ResourceLibrary* resourceLibrary):
		m_window(window), m_players(players), m_resourceLibrary(resourceLibrary)
	{
	}

	virtual ~GamePhase()
	{
	}

	virtual void handleEvent(const sf::Event& event) = 0;
	virtual void update() = 0;
	virtual void draw() = 0;

	// Common method for drawing a grid at a given position
	void drawGridIndexes(float x, float y, sf::Sprite* filler = nullptr)
	{
		// Draw x-axis
		for (std::size_t i = 0; i < 10; ++i)
		{
			m_resourceLibrary->get(GridIndexTile, i)->setPosition(x + TILE_SIZE + (i * TILE_SIZE), y);
			m_window->draw(*m_resourceLibrary->get(GridIndexTile, i));
		}

		// Draw y-axis
		for (std::size_t i = 0; i < 10; ++i)
		{
			m_resourceLibrary->get(GridIndexTile, 10 + i)->setPosition(x, y + TILE_SIZE + (i * TILE_SIZE));
			m_window->draw(*m_resourceLibrary->get(GridIndexTile, 10 + i));
		}

		if (filler)	// Draw fill the grid
			for (std::size_t i = 0; i < 10; ++i)
				for (std::size_t j = 0; j < 10; ++j)
				{
					filler->setPosition(x + (i + 1) * TILE_SIZE, y + (j + 1) * TILE_SIZE);
					m_window->draw(*filler);
				}
	}

	virtual bool phaseEnded() const = 0;

	Player* getCurrentPlayer() const
	{
		return &m_players[m_currentPlayerTurn];
	}

	Player* getOtherPlayer() const
	{
		return m_currentPlayerTurn == 0 ? &m_players[1] : &m_players[0];
	}

protected:
	bool m_phaseEnded = false;
	sf::RenderWindow* m_window;
	Player* m_players;
	std::size_t m_currentPlayerTurn = 0;
	ResourceLibrary* m_resourceLibrary = nullptr;
};
