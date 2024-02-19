#include "texture_2d.h"


namespace Renderer
{
	Renderer::Texture::Texture(GLuint texture_width, GLuint texture_height, const unsigned char* data, int channels, const GLenum filter, GLenum wrap_mode)
		: texture_width(texture_width), texture_height(texture_height)
	{
		switch (channels)
		{
		case 4:
			texture_mode = GL_RGBA;
			break;
		case 3:
			texture_mode = GL_RGB;
			break;
		default:
			texture_mode = GL_RGBA;
			break;
		}
		glGenTextures(1, &texture_id);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture_id);
		glTexImage2D(GL_TEXTURE_2D, 0, texture_mode, texture_width, texture_height, 0, texture_mode, GL_UNSIGNED_BYTE, data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_mode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_mode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture::bind() const
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture_id);
	}

	Texture& Texture::operator=(Texture&& texture_2d) noexcept
	{
		glDeleteTextures(1, &texture_id);
		texture_id = texture_2d.texture_id;
		texture_2d.texture_id = 0;
		texture_mode = texture_2d.texture_mode;
		texture_width = texture_2d.texture_width;
		texture_height = texture_2d.texture_height;
		return *this;
	}

	Texture::Texture(Texture&& texture_2d) noexcept
	{
		texture_id = texture_2d.texture_id;
		texture_2d.texture_id = 0;
		texture_mode = texture_2d.texture_mode;
		texture_width = texture_2d.texture_width;
		texture_height = texture_2d.texture_height;
	}

	Renderer::Texture::~Texture()
	{
		glDeleteTextures(1, &texture_id);
	}

}
