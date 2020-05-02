#pragma once

#include <string>

#include "Graphics/Shader.h"
#include "Graphics/Animation.h"

namespace Asylum {

	class ResourceManager
	{
	public:
		// load and unload resources
		static void LoadResources(const std::string& configPath);
		static void UnloadResources();

		// getter
		static std::shared_ptr<Shader> GetShader(const std::string& name);
		static std::vector<std::shared_ptr<Shader>> GetAllShaders();
		static std::shared_ptr<Texture> GetTexture(const std::string& name);
		static std::shared_ptr<TextureAtlas> GetTextureAtlas(const std::string& name);
		static std::shared_ptr<Animation> GetAnimation(const std::string& name);
	};

}