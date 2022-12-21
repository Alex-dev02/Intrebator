#pragma once

#include "Cell.hpp"

#include <vector>

class Map {

public:
	Map() = default;

	Map(int width, int height) {
		m_grid.resize(width);
		for (auto& row : m_grid) {
			row.resize(height);
		}
	}

	const Cell& GetCell(int x, int y) const {
		return m_grid[x][y];
	}

	// set cell ??? (anexed or base and to which color)

private:
	std::vector<std::vector<Cell>> m_grid;
};
