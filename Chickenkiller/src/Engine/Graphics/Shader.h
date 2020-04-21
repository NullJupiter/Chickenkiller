#pragma once

#include "pch.h"

namespace Engine {

	class Shader
	{
	private:
		uint32_t mShaderID;
		std::unordered_map<std::string, int> mUniforms;
	public:
		Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
		~Shader();

		void Bind() const;
		void Unbind() const;

		// set uniform functions
		void SetUniform1f(const std::string& name, float value);
		void SetUniform2f(const std::string& name, const glm::vec2& value);
		void SetUniform3f(const std::string& name, const glm::vec3& value);
		void SetUniform4f(const std::string& name, const glm::vec4& value);
		
		void SetUniformIntArray(const std::string& name, int count, int* value);
		void SetUniformMat4(const std::string& name, const glm::mat4& value);
		void SetUniformSampler2D(const std::string& name, int value);
	private:
		int GetUniformLocation(const std::string& name);
		uint32_t CompileShader(uint32_t shaderType, std::string shaderSource);
	};

}