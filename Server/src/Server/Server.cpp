#include "../../include/Server/Server.hpp"
#include "../../include/Services/UserServices.hpp"
#include "../../include/Services/GameServices.hpp"

Server::Server(std::shared_ptr<Database> database)
	: m_database(database),
	m_game_running(false)
{}

void Server::InitRoutes(std::shared_ptr<Server> server) {
	UserServices user_services{ m_database };
	user_services.InitRoutes(server);

	GameServices game_services{ m_database, server };
	game_services.InitRoutes();
}

crow::SimpleApp& Server::GetApp() {
	return m_app;
}

void Server::StartGame() {
	m_game_running = true;
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
