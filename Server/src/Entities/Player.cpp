#include "../../include/Entities/Player.hpp"

Player::Player(uint32_t id, const std::string& name, Colour color, uint32_t score)
	:User(id, name), m_color(color), m_score(score)
{}


const Colour& Player::GetColor() const{ //nu stiu de ce nu gaseste Colour
	return m_color;
}

uint32_t Player::GetScore() const{
	return m_score;
}


void Player::SetColor(Colour color){
	m_color = color;
}

void Player::SetScore(uint32_t score){
	m_score = score;
}
