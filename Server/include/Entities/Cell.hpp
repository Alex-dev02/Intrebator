#pragma  once
#include "Player.hpp"

#include <iostream>


class Cell {
public:
	enum class BaseType {
		Base,
		AnnexedTerritory
	};

public:
	Cell() = default;
	Cell(uint16_t score, BaseType base_type);

	uint16_t GetScore() const;
	BaseType GetBaseType() const;
	void SetScore(uint16_t score);
	void SetBaseType(BaseType base_type);

private:
	std::unique_ptr<Player> m_player;
	uint16_t m_score;
	BaseType m_base_type;
};

