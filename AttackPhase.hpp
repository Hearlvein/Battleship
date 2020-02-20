#pragma once

#include "GamePhase.hpp"

class AttackPhase : public GamePhase
{
public:
	AttackPhase(sf::RenderWindow* window, Player* players, ResourceLibrary* resourceLibrary):
		GamePhase(window, players, resourceLibrary)
	{
	}

	virtual ~AttackPhase()
	{
	}

	virtual void handleEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left) && !m_endTurn)
		{
			sf::Vector2i mousePosition = sf::Mouse::getPosition(*m_window);

			// Attack grid is drawn in the right
			mousePosition.x -= GRID_SIZE;

			// Substract indexes row and column of the grid
			mousePosition.x -= TILE_SIZE;
			mousePosition.y -= TILE_SIZE;

			// Determine indexes in the grid
			std::size_t x = mousePosition.x / TILE_SIZE;
			std::size_t y = mousePosition.y / TILE_SIZE;

			if (isCorrectGridPosition(x, y) && m_players[m_currentPlayerTurn].neverShotThere(x, y))	// Attack action
			{
				if (m_players[otherPlayerIndex()].isShipCell(x, y))	// Hit
				{
					debugMsg("Hit");
					m_players[m_currentPlayerTurn].registerShot(x, y, HitTile);
					m_players[otherPlayerIndex()].removeShipCell(x, y);
				}
				else
				{
					debugMsg("Missed");
					m_players[m_currentPlayerTurn].registerShot(x, y, MissedTile);
				}

				endTurn();
			}
			else
				debugMsg("invalid grid positions");
		}
	}

	virtual void update()
	{
		if (m_endTurn && m_endTurnTimer.getElapsedTime() >= m_endTurnDelay)	// Swap turn
		{
			if (m_currentPlayerTurn == 0)
				m_currentPlayerTurn = 1;
			else
				m_currentPlayerTurn = 0;

			m_endTurn = false;
		}
	}

	void endTurn()
	{
		m_endTurn = true;
		m_endTurnTimer.restart();
	}

	virtual bool phaseEnded() const
	{
		return m_phaseEnded;
	}

	virtual void draw()
	{
		drawGridIndexes(0.f, 0.f);
		m_players[m_currentPlayerTurn].drawShipsGrid(0.f, 0.f);
		drawGridIndexes(GRID_SIZE, 0.f);
		m_players[m_currentPlayerTurn].drawAttackGrid(GRID_SIZE, 0.f);
	}

	std::size_t otherPlayerIndex() const
	{
		if (m_currentPlayerTurn == 0)
			return 1;
		return 0;
	}

private:
	sf::Clock m_endTurnTimer;
	const sf::Time m_endTurnDelay = sf::seconds(1);
	bool m_endTurn = false;
};
