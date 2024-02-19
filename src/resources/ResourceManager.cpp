#include "ResourceManager.h"
#include "../Renderer/Shader.h"
#include "../renderer/texture_2d.h"
#include <sstream>
#include <fstream>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNJ
#include "stb_image.h"

ResourceManager::ResourceManager(const std::string& exec_path)
{
	size_t found = exec_path.find_last_of("/\\");
	m_path = exec_path.substr(0, found);
}

std::string ResourceManager::GetFileString(const std::string& shader_path) const
{
	std::ifstream f;
	f.open(m_path + "/" + shader_path.c_str(), std::ios::in, std::ios::binary);
	if (!f.is_open()) {
		std::cerr << "File not open in method GetFileString" << "\n";
		throw std::runtime_error("ShaderFile Failed To Open");
		return std::string();
	}
	std::stringstream buffer;
	buffer << f.rdbuf();
	return buffer.str();
}


std::shared_ptr<Renderer::Shader> ResourceManager::load_shaders(const std::string& shader_name, const std::string& vertex_path, const std::string& fragment_path)
{
	std::string vertex_string = GetFileString(vertex_path);
	if (vertex_string.empty()) {
		throw std::runtime_error("Path is empty");
		return nullptr;
	}
	std::string fragment_string = GetFileString(fragment_path);
	if (fragment_string.empty()) {
		throw std::runtime_error("Path is empty");
		return nullptr;
	}
    std::shared_ptr<Renderer::Shader>& new_shader =	m_shader_program.emplace(shader_name, std::make_shared<Renderer::Shader>(vertex_string, fragment_string)).first->second;
	if (!new_shader->IsCompiled()) {
		std::cerr << "Shade is not compiled" << std::endl;
		return nullptr;
	}
	return new_shader;
}

std::shared_ptr<Renderer::Shader> ResourceManager::get_shader_program(const std::string& shader_name) const
{
	shader_program_map::const_iterator it = m_shader_program.find(shader_name);
	if (it == m_shader_program.end()) {
		throw std::runtime_error("There is no such shader");
		return nullptr;
	}
	return it->second;
}


std::shared_ptr<Renderer::Texture>  ResourceManager::LoadTexture(const std::string texture_name, const std::string texture_path)
{
	int channels = 0;
	int width = 0;
	int height = 0;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* pixels = stbi_load(std::string(m_path + "/" + texture_path).c_str(), &width, &height, &channels, 0);
	if (!pixels) {
		std::cerr << "Cant load pixels " << texture_path << "\n";
		return nullptr;
	}
	std::shared_ptr<Renderer::Texture> new_texture = m_textures.emplace(texture_name, std::make_shared<Renderer::Texture>(width, height, pixels, channels)).first->second;
	stbi_image_free(pixels);
	return new_texture;
}

std::shared_ptr<Renderer::Texture> ResourceManager::get_texture(const std::string& texture_name) const
{
	textures_wrap::const_iterator it = m_textures.find(texture_name);
	if (it == m_textures.end()) {
		std::cerr << "There is no such shader" << "\n";
		throw std::runtime_error("There is no such shader");
		return nullptr;
	}
	return it->second;
}
