#pragma once

#include "User.hpp"

#include <string>


class Player : public User{
public:
	enum Colour{
		RED,
		GREEN,
		YELLOW,
		BLUE
	};

	Player(uint32_t id, const std::string& name, Colour color, uint32_t score);


	const Colour& GetColor() const;
	uint32_t GetScore() const;

	void SetColor(Colour color);
	void SetScore(uint32_t score);

private:
	Colour m_color;
	uint32_t m_score;
	bool m_isActive = true;
};
