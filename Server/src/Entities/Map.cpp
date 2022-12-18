#include "../../include/Entities/Map.hpp"

Map::Map(uint8_t width, uint8_t height) {
	m_grid.resize(width);
	for (auto& row : m_grid) {
		row.resize(height);
	}
}

const Cell& Map::GetCell(uint8_t x, uint8_t y) const {
	return m_grid[x][y];
}
