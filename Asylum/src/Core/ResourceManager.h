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
		static Ref<Shader> GetShader(const std::string& name);
		static std::vector<Ref<Shader>> GetAllShaders();
		static Ref<Texture> GetTexture(const std::string& name);
		static Ref<TextureAtlas> GetTextureAtlas(const std::string& name);
		static Ref<Animation> GetAnimation(const std::string& name);
	};

}