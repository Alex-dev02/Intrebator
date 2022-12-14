#include "../../include/Utils/CrowResponse.hpp"

		
const std::string& CrowResponse::ToString(Code code) {
	if (code == Code::OK)
		return "200";
	else if (code == Code::INVALID)
		return "400";
	else if (code == Code::SERVER_ERROR)
		return "500";
}

const crow::json::wvalue& CrowResponse::Json(Code code, const std::string& message = "", const crow::json::wvalue& data = {}) {
	return crow::json::wvalue{
		{"code", ToString(code)},
		{"message", message},
		{"data", data}
	};
}
