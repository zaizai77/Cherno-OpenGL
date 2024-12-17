#pragma once

#include <string>
#include <unordered_map>

#include "glm/glm.hpp"

struct ShaderProgramSource {
	std::string VertexSource;
	std::string FragmentSource;
	std::string GeometrySouce;
};

class Shader {
private:
	std::string m_FilePath;
	unsigned int m_RenderID;
	// caching for uniforms
	std::unordered_map<std::string, int> m_UniformLocationCache;
public:
	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void UnBind() const;

	unsigned int GetId() {
		return m_RenderID;
	}

	//Set uniforms
	void SetUniform1i(const std::string& name, int value);
	void SetUniform1f(const std::string& name, float value);
	void SetUniform3f(const std::string& name, float v0, float v1, float v2);
	void SetUniform3f(const std::string& name, glm::vec3 value);
	void SetUniform4f(const std::string& name,float v0,float v1,float v2,float v3);

	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);

private:
	unsigned int CompileShader(unsigned int type, const std::string& source);
	ShaderProgramSource ParseShader(const std::string& filepath);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader, const std::string& geometryShader);
	unsigned int GetUniformLoation(const std::string& name);
};