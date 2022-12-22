#include "../../include/Server/Server.hpp"
#include "../../include/Services/UserServices.hpp"
#include "../../include/Services/GameServices.hpp"

Server::Server(std::shared_ptr<Database> database)
	: m_database(database),
	m_game_running(false),
	m_game(std::make_shared<Game>())
{}

crow::SimpleApp& Server::GetApp() {
	return m_app;
}

void Server::StartGame() {
	m_game_running = true;
	m_game->SetDatabase(m_database);
	m_game->Run();
}

std::shared_ptr<Game> Server::GetGame() const {
	return m_game;
}

bool Server::GameIsRunning() const {
	return m_game_running;
}

void Server::StartServer() {
	m_app.port(8080).multithreaded().run();
}
