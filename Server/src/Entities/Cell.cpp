#include "../../include/Entities/Cell.hpp"

Cell::Cell(uint16_t score, Cell::BaseType base_type)
	: m_score(score),
	m_base_type(base_type),
	m_player(std::nullopt)
{}

uint16_t Cell::GetScore() const{
	return m_score;
}

Cell::BaseType Cell::GetBaseType() const{
	return m_base_type;
}

std::optional<std::shared_ptr<Player>> Cell::GetPlayer() const {
	return m_player;
}

void Cell::SetScore(uint16_t score){
	m_score = score;
}

void Cell::SetBaseType(BaseType base_type){
	m_base_type = base_type;
}

void Cell::SetPlayer(std::shared_ptr<Player> player) {
	m_player.emplace(player);
}

