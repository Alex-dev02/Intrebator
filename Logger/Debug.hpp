#pragma once

#include <iostream>

#ifdef LOGGER_EXPORT
#define LOGGER_API __declspec(dllimport)
#else
#define LOGGER_API __declspec(dllexport)
#endif // LOGGER_EXPORT

class LOGGER_API Debug {
public:
	template<typename T>
	static void Log(const T& object) {
		std::cout << "[Info] " << object << std::endl;
	}

	template<typename T>
	static void LogWarning(const T& object) {
		std::cerr << "[Warning] " << object << std::endl;
	}

	template<typename T>
	static void LogError(const T& object) {
		std::cerr << "[Error] " << object << std::endl;
	}
};