#include "ampch.h"
#include "Utils.h"

namespace Asylum {

	namespace Utils {

		std::string LoadFileToString(const std::string filepath)
		{
			// open file
			FILE* file = fopen(filepath.c_str(), "rt");
			if (!file) {
				LOG("Could not open file (filepath: " << filepath << ")");
				return "";
			}

			// get file size
			fseek(file, 0, SEEK_END);
			uint32_t length = ftell(file);
		
			// create buffer
			char* data = new char[length + 1];
			memset(data, 0, length + 1);

			// fill buffer with data
			fseek(file, 0, SEEK_SET);
			fread(data, 1, length, file);

			// close file
			fclose(file);

			// convert char* to std::string
			std::string ret = std::string(data);
			delete[] data;
			return ret;
		}

		nlohmann::json LoadFileToJsonObject(const std::string filepath)
		{
			return nlohmann::json::parse(LoadFileToString(filepath));
		}

		struct path_string
		{
			std::string operator()(const std::filesystem::directory_entry& entry) const
			{
				return entry.path().string();
			}
		};

		std::vector<std::string> GetFilenamesInDirectory(const std::string& directoryPath)
		{
			std::filesystem::path p(directoryPath);
			std::filesystem::directory_iterator start(p);
			std::filesystem::directory_iterator end;
			std::vector<std::string> result;
			std::transform(start, end, std::back_inserter(result), path_string());

			return result;
		}

	}

}

#include "Graphics/OrthographicCameraController.h"

namespace Asylum {

	namespace Utils {

		glm::vec2 Raycast::CastMousePosition(const glm::vec2& position, const glm::vec2& windowSize)
		{
			// 3d Normalised Device Coordinates
			float x = (2.0f * position.x) / windowSize.x - 1.0f;
			float y = 1.0f - (2.0f * position.y) / windowSize.y;
			float z = 1.0f;
			glm::vec3 normCoords = { x, y, z };

			// 4d Homogeneous Clip Coordinates
			glm::vec4 rayClipSpace = { normCoords.x, normCoords.y, 0.0, 1.0 };

			// 4d Eye (Camera) Coordinates
			const glm::mat4& projMatrix = OrthographicCameraController::Get()->GetProjectionMatrix();
			glm::vec4 rayEyeSpace = glm::inverse(projMatrix) * rayClipSpace;
			rayEyeSpace = { rayEyeSpace.x, rayEyeSpace.y, 0.0f, 1.0f };

			// 4d World Coordinates
			const glm::mat4& viewMatrix = OrthographicCameraController::Get()->GetViewMatrix();
			glm::vec4 rayWorldSpace = glm::inverse(viewMatrix) * rayEyeSpace;

			return { rayWorldSpace.x, rayWorldSpace.y };
		}

	}

}