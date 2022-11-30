#pragma once

#include "User.hpp"

class Player : public User{
public:
	// <---- an enum with red, green, yellow, blue here?

	const std::string& GetColor() const;
	const uint32_t GetScore() const;
	// getter for inherited name?
	
	void SetColor(char* color);
	void SetScore(uint32_t score);
	// setter for inherited name?
private:
	char* m_color;
	uint32_t m_score;
};