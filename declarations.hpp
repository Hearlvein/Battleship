#pragma once

enum TileType
{
	GridIndexTile = 0,
	SeaTile,
	ShipTile,
	QuestionTile,
	SelectedTile,
	HitTile,
	MissedTile
};

const float TILE_SIZE = 50.f;
const std::size_t GRID_WIDTH = 10;
const std::size_t GRID_HEIGHT = 10;
const bool DEBUG = true;
const float GRID_SIZE = 550.f;
const unsigned int MAX_NUMBER_SHIPS = 4;
