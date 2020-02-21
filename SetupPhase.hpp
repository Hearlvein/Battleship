#pragma once

#include "Ship.hpp"
#include "GamePhase.hpp"
#include "functions.hpp"

class SetupPhase : public GamePhase
{
public:
	SetupPhase(sf::RenderWindow* window, Player* players, ResourceLibrary* resourceLibrary):
		GamePhase(window, players, resourceLibrary)
	{
		m_infoText.setFont(*m_resourceLibrary->getFont());
		m_infoText.setPosition(20.f, GRID_SIZE + 20.f);
		updateInfoText();
	}

	virtual ~SetupPhase()
	{
	}

	virtual void handleEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			sf::Vector2i mousePosition = sf::Mouse::getPosition(*m_window);

			// Player 2 plays on the right grid
			if (m_currentPlayerTurn == 1)
				mousePosition.x -= GRID_SIZE;

			// Substract indexes row and column of the grid
			mousePosition.x -= TILE_SIZE;
			mousePosition.y -= TILE_SIZE;

			// Determine indexes in the grid
			std::size_t x = mousePosition.x / TILE_SIZE;
			std::size_t y = mousePosition.y / TILE_SIZE;

			if (isCorrectGridPosition(x, y))
				m_positions.push_back(sf::Vector2u(x, y));	// Register position for a next update
			else
				debugMsg("invalid grid positions");
		}
	}

	virtual void update()
	{
		if (m_positions.size() == 2)
		{
			std::cout << "adding a ship to player" << m_currentPlayerTurn << std::endl;
			m_players[m_currentPlayerTurn].addShip(m_positions[0], m_positions[1]);
			m_positions.clear();
		}

		if (m_players[m_currentPlayerTurn].everyShipsReady() && !m_endTurn)
			endTurn();

		if (m_endTurn && m_endTurnTimer.getElapsedTime() >= m_endTurnDelay)
		{
			if (m_currentPlayerTurn == 0)
			{
				m_currentPlayerTurn = 1;
				updateInfoText();
			}
			else
				m_phaseEnded = true;

			m_endTurn = false;
		}
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
		if (m_currentPlayerTurn == 0)
		{
			// Player 1 grid
			drawGridIndexes(0.f, 0.f, m_resourceLibrary->get(SeaTile));
			m_players[0].drawShipsGrid(0.f, 0.f);

			// Player 2 grid
			drawGridIndexes(GRID_SIZE, 0.f, m_resourceLibrary->get(QuestionTile));

			// Selected tile
			if (!m_positions.empty())
			{
				m_resourceLibrary->get(SelectedTile)->setPosition((float)(m_positions[0].x + 1) * TILE_SIZE, (float)(m_positions[0].y + 1) * TILE_SIZE);
				m_window->draw(*m_resourceLibrary->get(SelectedTile));
			}
		}
		else
		{
			// Player 1 grid
			drawGridIndexes(0.f, 0.f, m_resourceLibrary->get(QuestionTile));

			// Player 2 grid
			drawGridIndexes(GRID_SIZE, 0.f, m_resourceLibrary->get(SeaTile));
			m_players[1].drawShipsGrid(GRID_SIZE, 0.f);

			// Selected tile
			if (!m_positions.empty())
			{
				m_resourceLibrary->get(SelectedTile)->setPosition((float)(m_positions[0].x + 1) * TILE_SIZE + GRID_SIZE, (float)(m_positions[0].y + 1) * TILE_SIZE);
				m_window->draw(*m_resourceLibrary->get(SelectedTile));
			}
		}

		m_window->draw(m_infoText);
	}

private:
	std::vector<sf::Vector2u> m_positions;
	sf::Clock m_endTurnTimer;
	const sf::Time m_endTurnDelay = sf::seconds(2);
	bool m_endTurn = false;
	sf::Text m_infoText;
};
