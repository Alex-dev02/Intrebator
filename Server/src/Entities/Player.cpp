#include "../../include/Entities/Player.hpp"

const std::string& Player::ColorToString(Color color) const{
	if (color == Color::RED)
		return "RED";
	else if (color == Color::GREEN)
		return "GREEN";
	else if (color == Color::YELLOW)
		return "YELLOW";
	else if (color == Color::BLUE)
		return "BLUE";
	else
		return "NONE";
}

Player::Player(std::unique_ptr<User> user)
	: User(user->GetId(), user->GetName(), user->GetPassword()),
	m_color(Color::NONE),
	m_score(0)
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

void Player::SetInactive() {
	m_isActive = false;
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
		{"color", ColorToString(m_color)}
	};
}

bool Player::operator==(const Player& player) {
	return this->GetId() == player.GetId();
}
