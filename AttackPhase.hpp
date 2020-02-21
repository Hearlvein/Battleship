#pragma once

#include "GamePhase.hpp"

class AttackPhase : public GamePhase
{
public:
	AttackPhase(sf::RenderWindow* window, Player* players, ResourceLibrary* resourceLibrary):
		GamePhase(window, players, resourceLibrary)
	{
	    m_infoText.setFont(*m_resourceLibrary->getFont());
		m_infoText.setPosition(20.f, GRID_SIZE + 20.f);
		updateInfoText();
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

			if (isCorrectGridPosition(x, y) && getCurrentPlayer()->neverShotThere(x, y))	// Attack action
			{
				if (getOtherPlayer()->isShipCell(x, y))	// Hit
				{
					debugMsg("Hit");
					getCurrentPlayer()->registerShot(x, y, HitTile);
					getOtherPlayer()->removeShipCell(x, y);
				}
				else
				{
					debugMsg("Missed");
					getCurrentPlayer()->registerShot(x, y, MissedTile);
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

            updateInfoText();

			m_endTurn = false;
		}

		if (m_players[0].hasNoShip())
			m_infoText.setString("Player " + int2string(1) + " lost!");
		else if (m_players[1].hasNoShip())
			m_infoText.setString("Player " + int2string(2) + " lost!");
	}

	void updateInfoText()
	{
		m_infoText.setString("Player " + int2string(m_currentPlayerTurn + 1) + " is playing");
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
		getCurrentPlayer()->drawShipsGrid(0.f, 0.f);
		drawGridIndexes(GRID_SIZE, 0.f);
		getCurrentPlayer()->drawAttackGrid(GRID_SIZE, 0.f);
		m_window->draw(m_infoText);
	}

	std::size_t otherPlayerIndex() const
	{
		if (m_currentPlayerTurn == 0)
			return 1;
		return 0;
	}

private:
	sf::Clock m_endTurnTimer;
	const sf::Time m_endTurnDelay = sf::seconds(2);
	bool m_endTurn = false;
	sf::Text m_infoText;
};
