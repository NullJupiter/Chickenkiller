#include "ampch.h"
#include "ResourceManager.h"

namespace Asylum {
	
	struct ResourceManagerData
	{
		// data
		std::unordered_map<std::string, Ref<Shader>> Shaders;
		std::unordered_map<std::string, Ref<Texture>> Textures;
		std::unordered_map<std::string, Ref<AnimationSheet>> AnimationSheets;
		std::unordered_map<std::string, Ref<Animation>> Animations;
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
						sResouceManagerData.Shaders[name] = CreateRef<Shader>(vertexShaderPath, fragmentShaderPath);
					}

					// check if current subobject is under the category of "Textures"
					if (key == "Textures")
					{
						// get parameters
						std::string name = valueObject["name"].get<std::string>();
						std::string textureFilePath = valueObject["file-path"].get<std::string>();
						uint32_t colorFormat = valueObject["color-format"] == "RGBA" ? GL_RGBA : GL_RGB;

						// create new shader and store it in unordered_map
						sResouceManagerData.Textures[name] = CreateRef<Texture>(textureFilePath.c_str(), colorFormat);
					}

					// check if current subobject is under the category of "AnimationSheets"
					if (key == "AnimationSheets")
					{
						// get parameter
						std::string animationSheetName = valueObject["name"].get<std::string>();
						std::string textureFilePath = valueObject["file-path"].get<std::string>();
						uint32_t colorFormat = valueObject["color-format"] == "RGBA" ? GL_RGBA : GL_RGB;
						uint32_t rowCount = valueObject["row-count"].get<uint32_t>();
						uint32_t columnCount = valueObject["column-count"].get<uint32_t>();

						// create new texture atlas and store it in unordered_map
						sResouceManagerData.AnimationSheets[animationSheetName] = CreateRef<AnimationSheet>(textureFilePath.c_str(), colorFormat, rowCount, columnCount);

						// create all animations from animation sheet
						for (auto& animation : valueObject["animations"])
						{
							// get parameters
							std::string animationName = animation["name"].get<std::string>();
							uint32_t animationRow = animation["animation-row"].get<uint32_t>();
							uint32_t frameCount = animation["frame-count"].get<uint32_t>();
							float frameTime = animation["frame-time"].get<float>();

							// create new animation and store it in unordered_map
							sResouceManagerData.Animations[animationName] = CreateRef<Animation>(GetAnimationSheet(animationSheetName), animationRow, frameCount, frameTime);
						}
					}

					// check if current subobject is under the category of "TextureAtlases"
					if (key == "TextureAtlases")
					{
						/*// get parameter
						std::string textureAtlasName = valueObject["name"].get<std::string>();
						std::string textureFilePath = valueObject["file-path"].get<std::string>();
						uint32_t colorFormat = valueObject["color-format"] == "RGBA" ? GL_RGBA : GL_RGB;
						uint32_t rowCount = valueObject["row-count"].get<uint32_t>();
						uint32_t columnCount = valueObject["column-count"].get<uint32_t>();

						// create new texture atlas and store it in unordered_map
						sResouceManagerData.TextureAtlases[textureAtlasName] = CreateRef<AnimationSheet>(textureFilePath.c_str(), colorFormat, rowCount, columnCount);*/
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
		sResouceManagerData.AnimationSheets.clear();
		sResouceManagerData.Animations.clear();
	}

	const Ref<Shader>& ResourceManager::GetShader(const std::string& name)
	{
		return sResouceManagerData.Shaders[name];
	}

	std::vector<Ref<Shader>> ResourceManager::GetAllShaders()
	{
		std::vector<Ref<Shader>> allShaders;
		allShaders.reserve(sResouceManagerData.Shaders.size());
		for (auto& shaderData : sResouceManagerData.Shaders)
			allShaders.push_back(shaderData.second);

		return allShaders;
	}

	const Ref<Texture>& ResourceManager::GetTexture(const std::string& name)
	{
		return sResouceManagerData.Textures[name];
	}

	const std::unordered_map<std::string, Ref<Texture>>& ResourceManager::GetAllTextureData()
	{
		return sResouceManagerData.Textures;
	}

	const Ref<AnimationSheet>& ResourceManager::GetAnimationSheet(const std::string& name)
	{
		return sResouceManagerData.AnimationSheets[name];
	}

	const Ref<Animation>& ResourceManager::GetAnimation(const std::string& name)
	{
		return sResouceManagerData.Animations[name];
	}

	const std::unordered_map<std::string, Ref<Animation>>& ResourceManager::GetAllAnimationData()
	{
		return sResouceManagerData.Animations;
	}

}