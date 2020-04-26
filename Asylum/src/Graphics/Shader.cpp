#include "ampch.h"
#include "Shader.h"

#include <glm/gtc/type_ptr.hpp>

namespace Asylum {

	Shader::Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
		: mShaderID(0)
	{
		// create shader program
		mShaderID = glCreateProgram();
		// compile shaders
		uint32_t vertexShader = CompileShader(GL_VERTEX_SHADER, Utils::LoadFileToString(vertexShaderPath));
		uint32_t fragmentShader = CompileShader(GL_FRAGMENT_SHADER, Utils::LoadFileToString(fragmentShaderPath));

		// attach shaders to program and link them
		glAttachShader(mShaderID, vertexShader);
		glAttachShader(mShaderID, fragmentShader);
		glLinkProgram(mShaderID);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		// check for linking errors
		int success;
		glGetProgramiv(mShaderID, GL_LINK_STATUS, &success);
		if (!success) {
			int length;
			glGetProgramiv(mShaderID, GL_INFO_LOG_LENGTH, &length);
			char* infoLog = (char*)alloca(length * sizeof(char));
			glGetProgramInfoLog(mShaderID, length, &length, infoLog);
			LOG(infoLog);
			LOG("Could not link shader program! (Program ID: " << mShaderID << ")");
			glDeleteProgram(mShaderID);
			return;
		}

	}

	uint32_t Shader::CompileShader(uint32_t shaderType, std::string shaderSource)
	{
		// create shader
		uint32_t shader = glCreateShader(shaderType);
		const char* src = shaderSource.c_str();

		// compile shader
		glShaderSource(shader, 1, &src, nullptr);
		glCompileShader(shader);

		// check for compilation errors
		int success;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			int length;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
			char* infoLog = (char*)alloca(length * sizeof(char));
			glGetShaderInfoLog(shader, length, &length, infoLog);
			LOG(infoLog);
			LOG("Could not compile " << (shaderType == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!)");
			glDeleteShader(shader);
			return 0;
		}

		return shader;
	}

	Shader::~Shader()
	{
		glDeleteProgram(mShaderID);
	}

	void Shader::Bind() const
	{
		glUseProgram(mShaderID);
	}

	void Shader::Unbind() const
	{
		glUseProgram(0);
	}

	int Shader::GetUniformLocation(const std::string& name)
	{
		if (!mUniforms[name])
			mUniforms[name] = glGetUniformLocation(mShaderID, name.c_str());
		return mUniforms[name];
	}

	void Shader::SetUniform1f(const std::string& name, float value)
	{
		glUniform1f(GetUniformLocation(name), value);
	}

	void Shader::SetUniform2f(const std::string& name, const glm::vec2& value)
	{
		glUniform2f(GetUniformLocation(name), value.x, value.y);
	}

	void Shader::SetUniform3f(const std::string& name, const glm::vec3& value)
	{
		glUniform3f(GetUniformLocation(name), value.x, value.y, value.z);
	}

	void Shader::SetUniform4f(const std::string& name, const glm::vec4& value)
	{
		glUniform4f(GetUniformLocation(name), value.x, value.y, value.z, value.w);
	}

	void Shader::SetUniformIntArray(const std::string& name, int count, int* value)
	{
		glUniform1iv(GetUniformLocation(name), count, value);
	}

	void Shader::SetUniformMat4(const std::string& name, const glm::mat4& value)
	{
		glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
	}

	void Shader::SetUniformSampler2D(const std::string& name, int value)
	{
		glUniform1i(GetUniformLocation(name), value);
	}


}