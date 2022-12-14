#include "../../include/Server/Server.hpp"
#include "../../include/Services/UserServices.hpp"

Server::Server(std::shared_ptr<Database> database)
	: m_database(database)
{}

void Server::InitRoutes(std::shared_ptr<Server> server) {
	UserServices us{ m_database };
	us.InitRoutes(server);
}

crow::SimpleApp& Server::GetApp() {
	return m_app;
}

void Server::Start() {
	m_app.port(8080).multithreaded().run();
}
