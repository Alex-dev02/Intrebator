#include "../../include/Server/Server.hpp"

crow::SimpleApp& Server::GetApp() const {
	return m_app;
}

void Server::Start() {
	m_app.port(80).multithreaded().run();
}

crow::SimpleApp Server::m_app {};

void Server::CreateGame(){
	CROW_ROUTE(m_app, "/create_game/<int>")([](std::uint32_t id){

	});
};
