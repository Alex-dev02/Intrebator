#pragma once

#include "crow.h"

class Server {
public:

	Server() = default;
	Server(Server&) = delete;
	Server(Server&&) = delete;
	~Server() = default;

	crow::SimpleApp& GetApp() const;

	void Start();

private:

	static crow::SimpleApp m_app;

};
