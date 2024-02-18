#include "ResourceManager.h"
#include "../Renderer/Shader.h"
#include <sstream>
#include <fstream>
#include <iostream>

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
		return nullptr;
		throw std::runtime_error("Failed to compile shader");
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
