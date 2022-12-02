#pragma once

#include "Cell.hpp"

#include <array>

class Map{
public:
	// get cell ??
	// set cell ??? (anexed or base and to which color)

private:
	std::array<std::array<Cell, 5>, 3> m_grid;	// 3x5
};
