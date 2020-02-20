#pragma once

#include "declarations.hpp"

class ResourceLibrary
{
public:
	ResourceLibrary()
	{
		m_tileset.loadFromFile("tileset.png");

		for (std::size_t i = 0; i < 4; ++i)
			for (std::size_t j = 0; j < 5; ++j)
				m_gridIndexesTiles[i * 5 + j] = sf::Sprite(m_tileset, sf::IntRect(j * TILE_SIZE, (i + 1) * TILE_SIZE, TILE_SIZE, TILE_SIZE));

		m_seaTile.setTexture(m_tileset);
		m_seaTile.setTextureRect(sf::IntRect(0, 0, TILE_SIZE, TILE_SIZE));

		m_shipTile.setTexture(m_tileset);
		m_shipTile.setTextureRect(sf::IntRect(TILE_SIZE, 0, TILE_SIZE, TILE_SIZE));

		m_questionTile.setTexture(m_tileset);
		m_questionTile.setTextureRect(sf::IntRect(2 * TILE_SIZE, 0, TILE_SIZE, TILE_SIZE));

		m_selectedTile.setTexture(m_tileset);
		m_selectedTile.setTextureRect(sf::IntRect(3 * TILE_SIZE, 0, TILE_SIZE, TILE_SIZE));

		m_hitTile.setTexture(m_tileset);
		m_hitTile.setTextureRect(sf::IntRect(4 * TILE_SIZE, 0, TILE_SIZE, TILE_SIZE));

		m_missedTile.setTexture(m_tileset);
		m_missedTile.setTextureRect(sf::IntRect(5 * TILE_SIZE, 0, TILE_SIZE, TILE_SIZE));
	}

	~ResourceLibrary()
	{
	}

	sf::Sprite* get(TileType tileType, int index = 0)
	{
		if (tileType == GridIndexTile && index >= 0 && index < 20)
			return &m_gridIndexesTiles[index];
		else if (tileType == SeaTile)
			return &m_seaTile;
		else if (tileType == ShipTile)
			return &m_shipTile;
		else if (tileType == QuestionTile)
			return &m_questionTile;
		else if (tileType == SelectedTile)
			return &m_selectedTile;
		else if (tileType == HitTile)
			return &m_hitTile;
		else if (tileType == MissedTile)
			return &m_missedTile;

        return nullptr;
	}

private:
	// Defined here and shared to avoid multiple declaration (--optimization)
	sf::Texture m_tileset;

	/*
		- from 0 to 9: a-j (x axis)
		- from 10 to 19: 1-10 (y axis)
	*/
	sf::Sprite m_gridIndexesTiles[20];
	sf::Sprite m_seaTile;
	sf::Sprite m_shipTile;
	sf::Sprite m_questionTile;
	sf::Sprite m_selectedTile;
	sf::Sprite m_hitTile;
	sf::Sprite m_missedTile;
};
