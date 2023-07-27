#pragma once

#include <GL/glew.h>

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) OpenSandBox::Debug::GLDebug::GLClearError();\
	x;\
	ASSERT(OpenSandBox::Debug::GLDebug::GLLogCall(#x, __FILE__, __LINE__))

#include "OpenSandBox/API/Export.h"

namespace OpenSandBox::Debug
{
	class API_OPENSANDBOX GLDebug
	{
	public:
		static void GLClearError();
		static bool GLLogCall(const char* function, const char* file, int line);
		static void GLAPIENTRY GLDebugMessageCallback(GLenum source, GLenum type,
			GLuint id, GLenum severity, GLsizei length,
			const GLchar *message, const void *userParam);
	};
}