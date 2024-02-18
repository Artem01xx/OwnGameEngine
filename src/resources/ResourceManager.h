#pragma once
#include <string>
#include <memory>
#include <map>

namespace Renderer {
	class Shader;
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

	typedef std::map<std::string, std::shared_ptr<Renderer::Shader>> shader_program_map;
	shader_program_map m_shader_program;
	std::string m_path;
private:
	std::string GetFileString(const std::string& shader_path) const;
};