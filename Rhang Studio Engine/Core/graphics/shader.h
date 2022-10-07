#pragma once

#include "../utils/logger.h"
#include "../utils/glerror.h"
#include <GL/glew.h>
#include <vector>
#include <unordered_map>
#include "../utils/fileutils.h"
#include "../maths/maths.h"

namespace rse {
	namespace graphics {
	
		class Shader {
		private:
			GLuint m_ShaderID;
			const char *m_VertPath, *m_FragPath;

			//caching
			std::unordered_map<std::string, int> m_UniformLocationCache;
		public:
			Shader(const char* vertPath, const char* fragPath);
			~Shader();

			void SetUniform1f(const char* name, const float a);
			void SetUniform1i(const char* name, const int a);

			void SetUniform1fv(const char* name, int count, const float* a);
			void SetUniform1iv(const char* name, int count, const int* a);

			void SetUniform2f(const char* name, maths::vec2 a);
			void SetUniform3f(const char* name, maths::vec3 a);
			void SetUniform4f(const char* name, maths::vec4 a);

			void SetUniformMat4(const char* name, const maths::mat4& matrix);

			void enable() const;
			void disable() const;
		private:
			GLuint load();

			GLint GetUniformLocation(const char* name);
		};

	}
}