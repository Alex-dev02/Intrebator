#include "pch.h"

#include "Cell.h"

Cell::Cell(uint16_t score, Cell::BaseType base_type)
	: m_score(score),
	m_base_type(base_type)
{}