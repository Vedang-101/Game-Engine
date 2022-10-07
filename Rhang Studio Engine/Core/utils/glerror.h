#pragma once

#include <GL/glew.h>
#include <iostream>

#ifdef ENGINE_DEBUG
	#include <Windows.h>
#endif

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x)	GLClearError();\
					x;\
					ASSERT(GLLogCall(#x, __FILE__, __LINE__))

static void GLClearError() {
	#ifdef ENGINE_DEBUG
	while (glGetError() != GL_NO_ERROR);
	#endif
}

static bool GLLogCall(const char* function, const char* file, int line) {
	#ifdef ENGINE_DEBUG
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 4);
	while (GLenum error = glGetError()) {
		std::cout << "Error [OpenGL] (" << error << "): " << function <<
			" " << file << ":" << line << std::endl;
		return false;
	}
	SetConsoleTextAttribute(hConsole, 7);
	#endif
	return true;
}