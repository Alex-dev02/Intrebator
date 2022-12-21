#pragma  once
#include "Player.hpp"

#include <iostream>


class Cell {
public:
	enum class Type {
		Base,
		AnnexedTerritory,
		NONE
	};

public:
	Cell();
	Cell(uint16_t score, Type base_type);

	uint16_t GetScore() const;
	Type GetType() const;
	std::optional<std::shared_ptr<Player>> GetPlayer() const;

	void SetScore(uint16_t score);
	void SetType(Type base_type);
	void SetPlayer(std::shared_ptr<Player> player);

private:
	std::optional<std::shared_ptr<Player>> m_player;
	uint16_t m_score;
	Type m_type;
};

