#include "../../include/Entities/Game.hpp"

int Game::GetRandomValueFrom0UpUntilN(int n){
	std::random_device rnd;
	std::default_random_engine random{rnd()};
	std::uniform_int_distribution<int> uniform(0, n - 1);
	return uniform(random);
}

// StartGame
// should contain:
// function to select random colours for every player
// function to start the game??

// something else
