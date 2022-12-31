#include "../../include/Entities/Cell.hpp"

Cell::Cell()
	: m_player(std::nullopt),
	m_score(0),
	m_type(Type::NONE)
{}

std::string Cell::TypeToString(const Type type) {
	if (type == Type::Base)
		return "Base";
	else if (type == Type::AnnexedTerritory)
		return "AnnexedTerritory";
	return "NONE";
}

Cell::Cell(uint16_t score, Cell::Type base_type)
	: m_score(score),
	m_type(base_type),
	m_player(std::nullopt)
{}

uint16_t Cell::GetScore() const{
	return m_score;
}

Cell::Type Cell::GetType() const{
	return m_type;
}

std::optional<std::shared_ptr<Player>> Cell::GetPlayer() const {
	return m_player;
}

void Cell::SetScore(uint16_t score){
	m_score = score;
}

void Cell::SetType(Type base_type){
	m_type = base_type;
}

void Cell::SetPlayer(std::shared_ptr<Player> player) {
	m_player.emplace(player);
}

Cell::operator crow::json::wvalue() const {
	return crow::json::wvalue{
		{"player",
		m_player.has_value() ? static_cast<crow::json::wvalue>(*(m_player.value().get())) : "NONE"},
		{"score", m_score},
		{"type", TypeToString(m_type)}
	};
}

