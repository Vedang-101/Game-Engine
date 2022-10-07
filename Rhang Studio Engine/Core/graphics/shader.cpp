#include "shader.h"

namespace rse {
	namespace graphics {
		Shader::Shader(const char* vertPath, const char* fragPath)
			: m_VertPath(vertPath), m_FragPath(fragPath)
		{
			m_ShaderID = load();
		}

		GLuint Shader::load() {
			GLCall(GLuint program = glCreateProgram());
			GLCall(GLuint vertex = glCreateShader(GL_VERTEX_SHADER));
			GLCall(GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER));

			std::string vertSourceString = utils::read_file(m_VertPath);
			std::string fragSourceString = utils::read_file(m_FragPath);

			const char* vertSource = vertSourceString.c_str();
			const char* fragSource = fragSourceString.c_str();

			GLCall(glShaderSource(vertex, 1, &vertSource, NULL));
			GLCall(glCompileShader(vertex));

			GLint result;
			GLCall(glGetShaderiv(vertex, GL_COMPILE_STATUS, &result));
			if (result == GL_FALSE) {
				GLint length;
				GLCall(glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length));
				std::vector<char> error(length);
				GLCall(glGetShaderInfoLog(vertex, length, &length, &error[0]));
				utils::LogError("Failed to compiler Vertex Shader!: ", &error[0]);

				GLCall(glDeleteShader(vertex));
				return 0;
			}

			GLCall(glShaderSource(fragment, 1, &fragSource, NULL));
			GLCall(glCompileShader(fragment));

			GLCall(glGetShaderiv(fragment, GL_COMPILE_STATUS, &result));
			if (result == GL_FALSE) {
				GLint length;
				GLCall(glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length));
				std::vector<char> error(length);
				GLCall(glGetShaderInfoLog(fragment, length, &length, &error[0]));
				utils::LogError("Failed to compiler Fragment Shader!: ", &error[0]);

				GLCall(glDeleteShader(fragment));
				return 0;
			}

			GLCall(glAttachShader(program, vertex));
			GLCall(glAttachShader(program, fragment));

			GLCall(glLinkProgram(program));
			GLCall(glValidateProgram(program));

			GLCall(glDeleteShader(vertex));
			GLCall(glDeleteShader(fragment));

			return program;
		}

		Shader::~Shader() {
			GLCall(glDeleteProgram(m_ShaderID));
		}

		void Shader::enable() const {
			GLCall(glUseProgram(m_ShaderID));
		}

		void Shader::disable() const {
			GLCall(glUseProgram(0));
		}

		void Shader::SetUniform1f(const char* name, const float a) {
			GLCall(glUniform1f(GetUniformLocation(name), a));
		}

		void Shader::SetUniform1i(const char* name, const int a) {
			GLCall(glUniform1i(GetUniformLocation(name), a));
		}

		void Shader::SetUniform1fv(const char* name, int count, const float* a) {
			GLCall(glUniform1fv(GetUniformLocation(name), count, a));
		}

		void Shader::SetUniform1iv(const char* name, int count, const int* a) {
			GLCall(glUniform1iv(GetUniformLocation(name), count, a));
		}

		void Shader::SetUniform2f(const char* name, maths::vec2 vector) {
			GLCall(glUniform2f(GetUniformLocation(name), vector.x, vector.y));
		}
		
		void Shader::SetUniform3f(const char* name, maths::vec3 vector) {
			GLCall(glUniform3f(GetUniformLocation(name), vector.x, vector.y, vector.z));
		}

		void Shader::SetUniform4f(const char* name, maths::vec4 vector) {
			GLCall(glUniform4f(GetUniformLocation(name), vector.x, vector.y, vector.z, vector.w));
		}

		void Shader::SetUniformMat4(const char* name, const maths::mat4& matrix) {
			GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, matrix.elements));
		}

		GLint Shader::GetUniformLocation(const char* name) {
			if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
				return m_UniformLocationCache[name];
			GLCall(GLint uniform_location = glGetUniformLocation(m_ShaderID, name));
			if (uniform_location == -1)
				utils::LogWarning("Following Uniform does not exist: ", name);

			m_UniformLocationCache[name] = uniform_location;
			return uniform_location;
		}

	}
}