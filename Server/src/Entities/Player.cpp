#include "../../include/Entities/Player.hpp"

Player::Player(uint32_t id, const std::string& name, char* color, uint32_t score)
	:User(id, name), m_color(color), m_score(score)
{}


const std::string& Player::GetColor() const{
	return m_color;
}

uint32_t Player::GetScore() const{
	return m_score;
}


void Player::SetColor(char* color){
	m_color = color;
}

void Player::SetScore(uint32_t score){
	m_score = score;
}
