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
		static const Ref<Shader>& GetShader(const std::string& name);
		static std::vector<Ref<Shader>> GetAllShaders();

		static const Ref<Texture>& GetTexture(const std::string& name);
		static const std::unordered_map<std::string, Ref<Texture>>& GetAllTextureData();

		static const Ref<AnimationSheet>& GetAnimationSheets(const std::string& name);
		static const Ref<Animation>& GetAnimation(const std::string& name);
	};

}