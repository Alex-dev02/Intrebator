#pragma once

#include "User.hpp"

#include <string>

class Player : public User{
public:
	Player(uint32_t id, const std::string& name, char* color, uint32_t score);
	// <---- an enum with red, green, yellow, blue here?

	const std::string& GetColor() const;
	uint32_t GetScore() const;
	
	void SetColor(char* color);
	void SetScore(uint32_t score);
private:
	char* m_color;
	uint32_t m_score;
	bool m_isActive = true;
};