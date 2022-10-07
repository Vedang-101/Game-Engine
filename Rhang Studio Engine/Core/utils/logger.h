#pragma once

#include <iostream>

#ifdef ENGINE_DEBUG
	#include <Windows.h>
#endif

namespace rse {
	namespace utils {

		static void Log(const char* message) {
			#ifdef ENGINE_DEBUG
			std::cout << "Log: " << message << std::endl;
			#endif
		}

		static void Log(const char* message1, const char* message2) {
			#ifdef ENGINE_DEBUG
			std::cout << "Log: " << message1 << message2 << std::endl;
			#endif
		}

		static void LogError(const char* message) {
			#ifdef ENGINE_DEBUG
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, 4);
			std::cout << "Error [" << 1 << "]: " << message << std::endl;
			SetConsoleTextAttribute(hConsole, 7);
			#endif
		}

		static void LogError(const char* message1, const char* message2) {
			#ifdef ENGINE_DEBUG
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, 4);
			std::cout << "Error [" << 1 << "]: " << message1 << message2 << std::endl;
			SetConsoleTextAttribute(hConsole, 7);
			#endif
		}

		static void LogWarning(const char* message) {
			#ifdef ENGINE_DEBUG
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, 6);
			std::cout << "Warning: " << message << std::endl;
			SetConsoleTextAttribute(hConsole, 7);
			#endif
		}

		static void LogWarning(const char* message1, const char* message2) {
			#ifdef ENGINE_DEBUG
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, 6);
			std::cout << "Warning: " << message1 << message2 << std::endl;
			SetConsoleTextAttribute(hConsole, 7);
			#endif
		}
	}
}