#include "../../include/Entities/Map.hpp"

Map::Map(uint8_t width, uint8_t height)
	: m_width(width),
	m_height(height),
	m_grid(std::vector<std::vector<Cell>>(height, std::vector<Cell>(width, Cell())))
{}

Cell& Map::GetCell(uint8_t x, uint8_t y) {
	if (x > m_width || y > m_height || x < 0 || y < 0)
		throw std::exception("Out of bounderis cell");
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

bool Map::TryPickCell(uint8_t x, uint8_t y, std::shared_ptr<Player> player) {
	try{
		auto& cell = GetCell(x, y);
		if (!cell.GetPlayer().has_value() && CellIsInPlayerReach(x, y, player)) {
			cell.SetPlayer(player);
			return true;
		}
		return false;
			
	}
	catch (const std::exception&) {
		return false;
	}
}

bool Map::CellIsInPlayerReach(uint8_t x, uint8_t y, std::shared_ptr<Player> player) {
	try {
		auto& cell0 = GetCell(x + 1, y);
		if (cell0.GetPlayer().has_value() && cell0.GetPlayer().value()->GetId() == player->GetId())
			return true;
	}
	catch (const std::exception&)
	{}

	try {
		auto& cell0 = GetCell(x - 1, y);
		if (cell0.GetPlayer().has_value() && cell0.GetPlayer().value()->GetId() == player->GetId())
			return true;
	}
	catch (const std::exception&)
	{}

	try {
		auto& cell0 = GetCell(x, y + 1);
		if (cell0.GetPlayer().has_value() && cell0.GetPlayer().value()->GetId() == player->GetId())
			return true;
	}
	catch (const std::exception&)
	{}

	try {
		auto& cell0 = GetCell(x + 1, y - 1);
		if (cell0.GetPlayer().has_value() && cell0.GetPlayer().value()->GetId() == player->GetId())
			return true;
	}
	catch (const std::exception&)
	{}

	return false;
}
