#pragma once
#include <glad/glad.h>
#include <string>

namespace Renderer
{
	class Texture
	{
	public:
		Texture(GLuint texture_width, GLuint texture_height, const unsigned char* data, int channels = 4,
		        const GLenum filter = GL_LINEAR, GLenum wrapMode = GL_CLAMP_TO_EDGE);

		Texture() = delete;
		Texture(const Texture&) = delete;
		Texture& operator = (const Texture& texture_2d) = delete;
		Texture& operator = (Texture&& texture_2d) noexcept;
		Texture(Texture&& texture_2d) noexcept;
		~Texture();

		void bind() const;
	private:
		GLuint texture_id;
		GLenum texture_mode;
		unsigned int texture_width;
		unsigned int texture_height;
	};
}