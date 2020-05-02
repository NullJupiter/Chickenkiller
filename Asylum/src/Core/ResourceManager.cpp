#include "ampch.h"
#include "ResourceManager.h"

namespace Asylum {
	
	struct ResourceManagerData
	{
		// data
		std::unordered_map<std::string, std::shared_ptr<Shader>> Shaders;
		std::unordered_map<std::string, std::shared_ptr<Texture>> Textures;
		std::unordered_map<std::string, std::shared_ptr<TextureAtlas>> TextureAtlases;
		std::unordered_map<std::string, std::shared_ptr<Animation>> Animations;
	};

	static ResourceManagerData sResouceManagerData;

	void ResourceManager::LoadResources(const std::string& configPath)
	{
		// get filepaths in config directory
		std::vector<std::string> configFiles = Utils::GetFilenamesInDirectory(configPath);

		// iterate over files and get the json elements
		for (auto& filePath : configFiles)
		{
			// load json file to json object
			auto j = Utils::LoadFileToJsonObject(filePath);
			// iterate over all subobjects
			for (auto& element : j.items())
			{
				// iterate over value array
				for (auto& valueObject : element.value())
				{
					std::string key = element.key();

					// check if current subobject is under the category of "Shaders"
					if (key == "Shaders")
					{
						// get parameters
						std::string name = valueObject["name"].get<std::string>();
						std::string vertexShaderPath = valueObject["vertex-file-path"].get<std::string>();
						std::string fragmentShaderPath = valueObject["fragment-file-path"].get<std::string>();

						// create new shader and store it in unordered_map
						sResouceManagerData.Shaders[name] = std::make_shared<Shader>(vertexShaderPath, fragmentShaderPath);
					}

					// check if current subobject is under the category of "Textures"
					if (key == "Textures")
					{
						// get parameters
						std::string name = valueObject["name"].get<std::string>();
						std::string textureFilePath = valueObject["file-path"].get<std::string>();
						uint32_t colorFormat = valueObject["color-format"] == "RGBA" ? GL_RGBA : GL_RGB;

						// create new shader and store it in unordered_map
						sResouceManagerData.Textures[name] = std::make_shared<Texture>(textureFilePath.c_str(), colorFormat);
					}

					// check if current subobject is under the category of "TextureAtlases"
					if (key == "TextureAtlases")
					{
						// get parameter
						std::string textureAtlasName = valueObject["name"].get<std::string>();
						std::string textureFilePath = valueObject["file-path"].get<std::string>();
						uint32_t colorFormat = valueObject["color-format"] == "RGBA" ? GL_RGBA : GL_RGB;
						uint32_t rowCount = valueObject["row-count"].get<uint32_t>();
						uint32_t columnCount = valueObject["column-count"].get<uint32_t>();

						// create new texture atlas and store it in unordered_map
						sResouceManagerData.TextureAtlases[textureAtlasName] = std::make_shared<TextureAtlas>(textureFilePath.c_str(), colorFormat, rowCount, columnCount);

						// create all animations
						for (auto& animation : valueObject["animations"])
						{
							// get parameters
							std::string animationName = animation["name"].get<std::string>();
							uint32_t animationRow = animation["animation-row"].get<uint32_t>();
							uint32_t frameCount = animation["frame-count"].get<uint32_t>();
							float frameTime = animation["frame-time"].get<float>();

							// create new animation and store it in unordered_map
							sResouceManagerData.Animations[animationName] = std::make_shared<Animation>(GetTextureAtlas(textureAtlasName), animationRow, frameCount, frameTime);
						}
					}
				}
			}
		}
	}

	void ResourceManager::UnloadResources()
	{
		// erase resource data
		sResouceManagerData.Shaders.clear();
		sResouceManagerData.Textures.clear();
		sResouceManagerData.TextureAtlases.clear();
		sResouceManagerData.Animations.clear();
	}

	std::shared_ptr<Shader> ResourceManager::GetShader(const std::string& name)
	{
		return sResouceManagerData.Shaders[name];
	}

	std::vector<std::shared_ptr<Shader>> ResourceManager::GetAllShaders()
	{
		std::vector<std::shared_ptr<Shader>> allShaders;
		allShaders.reserve(sResouceManagerData.Shaders.size());
		for (auto& shaderData : sResouceManagerData.Shaders)
			allShaders.push_back(shaderData.second);

		return allShaders;
	}

	std::shared_ptr<Texture> ResourceManager::GetTexture(const std::string& name)
	{
		return sResouceManagerData.Textures[name];
	}

	std::shared_ptr<TextureAtlas> ResourceManager::GetTextureAtlas(const std::string& name)
	{
		return sResouceManagerData.TextureAtlases[name];
	}

	std::shared_ptr<Animation> ResourceManager::GetAnimation(const std::string& name)
	{
		return sResouceManagerData.Animations[name];
	}

}