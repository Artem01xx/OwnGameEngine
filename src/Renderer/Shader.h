#pragma once
#include <glad/glad.h>
#include <string>


namespace Renderer
{
	class Shader
	{
	public:
		Shader(const std::string& vertexShader, const std::string& fragmentShader);

		bool IsCompiled();
		void Use() const;
		Shader() = delete;
		Shader(const Shader&) = delete;
		Shader& operator = (const Shader&) = delete;

		Shader& operator = (Shader&& shader) noexcept;
		Shader(Shader&& program) noexcept;
 
		~Shader();
	private:
		bool CreateShader(const std::string& source, const GLenum shader_type, GLuint& shaderID);

		bool is_compiled = false;
		GLuint shader_program = 0;
	};
}