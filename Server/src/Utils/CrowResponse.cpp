#include "../../include/Utils/CrowResponse.hpp"

const crow::json::wvalue& CrowResponse::Json(Code code, const std::string& message, const crow::json::wvalue& data) {
	return crow::json::wvalue{
		{"code", code},
		{"message", message},
		{"data", data}
	};
}
