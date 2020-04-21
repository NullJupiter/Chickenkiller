#pragma once

#include "pch.h"

#include "Engine/Graphics/Shader.h"
#include "Engine/Graphics/Animation.h"

namespace Engine {

	class ResourceManager
	{
	public:
		// load and unload resources
		static void LoadResources(const std::string& configPath);
		static void UnloadResources();

		// getter
		static std::shared_ptr<Shader> GetShader(const std::string& name);
		static std::shared_ptr<Texture> GetTexture(const std::string& name);
		static std::shared_ptr<TextureAtlas> GetTextureAtlas(const std::string& name);
		static std::shared_ptr<Animation> GetAnimation(const std::string& name);
	};

}