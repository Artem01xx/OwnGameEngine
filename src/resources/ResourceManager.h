#pragma once
#include <string>
#include <memory>
#include <map>

namespace Renderer {
	class Shader;
	class Texture;
};

class ResourceManager
{
public:
	ResourceManager(const std::string& exec_path);
	~ResourceManager() = default;
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator = (const ResourceManager&) = delete;
	ResourceManager& operator = (const ResourceManager&&) = delete;
	ResourceManager(ResourceManager&&) = delete;

	std::shared_ptr<Renderer::Shader> load_shaders(const std::string& shader_name, const std::string& vertex_path, const std::string& fragment_path);
	std::shared_ptr<Renderer::Shader> get_shader_program(const std::string& shader_name) const;

	std::shared_ptr<Renderer::Texture> LoadTexture(const std::string texture_name, const std::string texture_path);
	std::shared_ptr<Renderer::Texture> get_texture(const std::string& texture_name) const;

	typedef std::map<std::string, std::shared_ptr<Renderer::Shader>> shader_program_map;
	shader_program_map m_shader_program;
	typedef std::map<std::string, std::shared_ptr<Renderer::Texture>> textures_wrap;
	textures_wrap m_textures;

	std::string m_path;
private:
	std::string GetFileString(const std::string& shader_path) const;
};