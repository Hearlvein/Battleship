#pragma once

#include "declarations.hpp"
#include "functions.hpp"

class Grid
{
public:
	Grid()
	{
		m_grid.resize(GRID_WIDTH);
		for (std::size_t i = 0; i < GRID_WIDTH; ++i)
			m_grid[i].resize(GRID_HEIGHT);

		for (std::size_t i = 0; i < GRID_WIDTH; ++i)
			for (std::size_t j = 0; j < GRID_HEIGHT; ++j)
				m_grid[i][j] = SeaTile;
	}

	~Grid()
	{
	}

	TileType get(const std::size_t x, const std::size_t y)
	{
		if (isCorrectGridPosition(x, y))
			return m_grid[x][y];

		return QuestionTile;
	}

	void set(const std::size_t x, const std::size_t y, TileType value)
	{
		if (isCorrectGridPosition(x, y))
			m_grid[x][y] = value;
	}

private:
	std::vector< std::vector<TileType> > m_grid;
};
