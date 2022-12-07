#include "../../include/Server/Server.hpp"

Server::Server(std::shared_ptr<Database> database)
	: m_database(database)
{}

crow::SimpleApp& Server::GetApp() {
	return m_app;
}

void Server::Start() {
	m_app.port(80).multithreaded().run();
}

void Server::CreateGame(){
	CROW_ROUTE(m_app, "/create_game/<int>")([](std::uint32_t user_id) {
		return crow::response(200);
	});
};
