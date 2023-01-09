#pragma once

#include "User.hpp"

#include <string>
#include <memory>
#include <crow.h>


class Player : public User{
public:
	enum class Color{
		RED,
		GREEN,
		YELLOW,
		BLUE,
		NONE
	};

	enum class Powerups{
		FIFTYFIFITY,
		FOURANSWERS,
		CORRECTANSWER
	};

	std::string ColorToString(Color color) const;
	static std::vector<Color> GetAllColors();
public:
	Player(std::unique_ptr<User> user);
	// Player(uint32_t id, const std::string& name, Colour color, uint32_t score);


	const Color& GetColor() const;
	uint32_t GetScore() const;
	const std::string& GetPassword() const = delete;

	void SetInactive();
	void SetColor(Color color);
	void SetScore(uint32_t score);
	void SetPassword(const std::string&) const = delete;

public:
	operator crow::json::wvalue() const;
	bool operator==(const Player& player);
private:
	Color m_color;
	uint32_t m_score;
	bool m_isActive = true;
	bool m_used5050Powerup;
	bool m_used4AnswersPowerup;
	bool m_usedCorrectAnswerPowerup;
};
