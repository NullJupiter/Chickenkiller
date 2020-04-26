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