#pragma once

#include "Cell.hpp"

#include <vector>

class Map {

public:
	Map() = default;

	Map(uint8_t width, uint8_t height);

	const Cell& GetCell(uint8_t x, uint8_t y) const;

	// set cell ??? (anexed or base and to which color

private:
	std::vector<std::vector<Cell>> m_grid;
};
