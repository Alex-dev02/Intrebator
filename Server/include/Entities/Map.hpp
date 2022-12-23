#pragma once

#include "Cell.hpp"

#include <vector>

class Map {

public:
	Map() = default;

	Map(uint8_t width, uint8_t height);

	Cell& GetCell(uint8_t x, uint8_t y);

	// set cell ??? (anexed or base and to which color)
public:
	uint16_t FreeCells();
	bool TryPickCell(uint8_t x, uint8_t y, std::shared_ptr<Player> player);

private:
	uint8_t m_width;
	uint8_t m_height;
	std::vector<std::vector<Cell>> m_grid;
};
