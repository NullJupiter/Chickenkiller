#pragma once

#include <string>
#include <filesystem>
#include <json.hpp>

namespace Asylum {

	namespace Utils {

		std::string LoadFileToString(const std::string filepath);
		nlohmann::json LoadFileToJsonObject(const std::string filepath);

        std::vector<std::string> GetFilenamesInDirectory(const std::string& directoryPath);

	}

}

#include <glm/glm.hpp>
#include "Graphics/Window.h"

namespace Asylum {

	namespace Utils {

		class Raycast
		{
		public:
			static glm::vec2 CastMousePosition(const glm::vec2& position, const glm::vec2& windowSize = { Window::Get()->GetWidth(), Window::Get()->GetHeight() });
		};

	}

}