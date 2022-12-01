#include "../../include/Entities/Cell.hpp"
#include <wrl/implements.h>

Cell::Cell(uint16_t score, Cell::BaseType base_type)
	: m_score(score),
	m_base_type(base_type)
{}

uint16_t Cell::GetScore() const
{
	return m_score;
}

Cell::BaseType Cell::GetBaseType() const
{
	return m_base_type;
}

void Cell::SetScore(uint16_t score)
{
	m_score = score;
}

void Cell::SetBaseType(BaseType base_type)
{
	m_base_type = base_type;
}

