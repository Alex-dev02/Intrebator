#pragma once

#include "User.hpp"

#include <string>
#include <memory>
#include <crow.h>


class Player : public User{
public:
	enum Color{
		RED,
		GREEN,
		YELLOW,
		BLUE
	};
public:
	Player(std::unique_ptr<User> user);
	// Player(uint32_t id, const std::string& name, Colour color, uint32_t score);


	const Color& GetColor() const;
	uint32_t GetScore() const;
	const std::string& GetPassword() const = delete;

	void SetColor(Color color);
	void SetScore(uint32_t score);
	void SetPassword(const std::string&) const = delete;

public:
	operator crow::json::wvalue() const;

private:
	Color m_color;
	uint32_t m_score;
	bool m_isActive = true;
};
