#include "../../include/Entities/Map.hpp"

Map::Map(uint8_t width, uint8_t height) {
	m_grid = std::vector<std::vector<Cell>>(height, std::vector<Cell>(width, Cell()));
}

const Cell& Map::GetCell(uint8_t x, uint8_t y) const {
	return m_grid[x][y];
}

uint16_t Map::FreeCells() {
	uint16_t free_cells = 0;
	for (const auto& row : m_grid) {
		for (const auto& cell : row) {
			if (cell.GetPlayer().has_value())
				free_cells++;
		}
	}
	
	return free_cells;
}
