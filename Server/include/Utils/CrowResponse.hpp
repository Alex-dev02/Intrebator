#pragma once

#include <crow.h>
#include <string>

class CrowResponse {
public:
	enum Code {
		OK = 200,
		INVALID = 400,
		SERVER_ERROR = 500
	};
		
	static crow::json::wvalue Json(Code code, const std::string& message = "", const crow::json::wvalue& data = {});
};
