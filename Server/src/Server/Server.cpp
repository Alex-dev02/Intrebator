#include "../../include/Server/Server.hpp"

crow::SimpleApp& Server::GetApp() const {
	return m_app;
}

void Server::Start() {
	m_app.port(80).multithreaded().run();
}

crow::SimpleApp Server::m_app {};
