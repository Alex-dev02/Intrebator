#include "../../include/Entities/Player.hpp"

Player::Player(std::unique_ptr<User> user)
	: User(user->GetId(), user->GetName(), user->GetPassword())
{}

//Player::Player(uint32_t id, const std::string& name, Colour color, uint32_t score)
//	: User(id, name),
//	m_color(color),
//	m_score(score)
//{}


const Player::Color& Player::GetColor() const{    // Colour ii parte din Player. cum scrii Player::functie asa si Player::Colour. de asta nu ti-l gasea. (adi delete after seeing)
	return m_color;
}

uint32_t Player::GetScore() const{
	return m_score;
}


void Player::SetColor(Color color){
	m_color = color;
}

void Player::SetScore(uint32_t score){
	m_score = score;
}

Player::operator crow::json::wvalue() const {
	return crow::json::wvalue{
		{"id", GetId()},
		{"name", GetName()},
		{"color", m_color}
	};
}
