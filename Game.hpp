#pragma once

#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "ResourceLibrary.hpp"
#include "SetupPhase.hpp"
#include "AttackPhase.hpp"

class Game
{
public:
	Game():
		m_players({Player(&m_window, &m_resourceLibrary), Player(&m_window, &m_resourceLibrary)})
	{
		// The room for two grids
		m_window.create(sf::VideoMode(2 * GRID_SIZE, GRID_SIZE), "Battleship");

		m_currentGamePhase = new SetupPhase(&m_window, m_players, &m_resourceLibrary);
	}

	~Game()
	{
		if (m_currentGamePhase)
			delete m_currentGamePhase;
	}

	void run()
	{
		while (m_window.isOpen())
		{
			if (m_currentGamePhase->phaseEnded())	// if SetupPhase ended, begin AttackPhase!
			{
				// Dirty code right here
				delete m_currentGamePhase;
				m_currentGamePhase = new AttackPhase(&m_window, m_players, &m_resourceLibrary);
			}

			sf::Event event;
			while (m_window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					m_window.close();
				else
					m_currentGamePhase->handleEvent(event);
			}

			m_currentGamePhase->update();
			m_window.clear();
			m_currentGamePhase->draw();
			m_window.display();
		}
	}

private:
	sf::RenderWindow m_window;

	/*
		- m_players[0] : the human player
		- m_players[1] : the computer player
	*/
	Player m_players[2];
	GamePhase* m_currentGamePhase = nullptr;

	ResourceLibrary m_resourceLibrary;
};
