#include "Shader.h"
#include <iostream>

namespace Renderer
{
	Renderer::Shader::Shader(const std::string& vertexShader, const std::string& fragmentShader)
	{
		GLuint vertex_shaderID;
		if (!CreateShader(vertexShader, GL_VERTEX_SHADER, vertex_shaderID)) {
			std::cerr << "Shader compile error " << "\n";
			return;
		}
		GLuint fragment_shaderID;
		if (!CreateShader(fragmentShader, GL_FRAGMENT_SHADER, fragment_shaderID)) {
			std::cerr << "Shader compile error " << "\n";
			glDeleteShader(vertex_shaderID);
			return;
		}

		shader_program = glCreateProgram();
		glAttachShader(shader_program, vertex_shaderID);
		glAttachShader(shader_program, fragment_shaderID);
		glLinkProgram(shader_program);
        
		GLint sucsecc;
		glGetProgramiv(shader_program, GL_LINK_STATUS, &sucsecc);
		if (!sucsecc) {
			GLchar info_log[1024];
			glGetProgramInfoLog(shader_program, 1024, nullptr, info_log);
			std::cerr << "Shader link error " << info_log << "\n";
		}
		else {
			is_compiled = true;
		}

		glDeleteShader(vertex_shaderID);
		glDeleteShader(fragment_shaderID);
	}


	bool Renderer::Shader::IsCompiled() { return is_compiled; }

	void Renderer::Shader::Use() const { glUseProgram(shader_program); }

	bool Shader::CreateShader(const std::string& source, const GLenum shader_type, GLuint& shaderID)
	{
		shaderID = glCreateShader(shader_type);
		const char* code = source.c_str();
		glShaderSource(shaderID, 1, &code, nullptr);
		glCompileShader(shaderID);
        
		GLint sucsecc;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &sucsecc);

		if (!sucsecc) {
			GLchar info_log[1024];
			glGetShaderInfoLog(shaderID, 1024, nullptr, info_log);
			std::cerr << "Shader compile error " << info_log << "\n";
			return false;
		}
		return true;
	}

	Shader& Renderer::Shader::operator=(Shader&& shader) noexcept
	{
		glDeleteProgram(shader_program);
		shader_program = shader.shader_program;
		is_compiled = shader.is_compiled;

		shader.shader_program = 0;
		shader.is_compiled = false;
		return *this;
	}

	Renderer::Shader::Shader(Shader&& shader) noexcept
	{
		shader_program = shader.shader_program;
		is_compiled = shader.is_compiled;

		shader.shader_program = 0;
		shader.is_compiled = false;
	}

	void Renderer::Shader::SetId(const std::string& name, const GLint value)
	{
		glUniform1i(glGetUniformLocation(shader_program, name.c_str()), value);
	}

	Shader::~Shader() { glDeleteProgram(shader_program); }
}