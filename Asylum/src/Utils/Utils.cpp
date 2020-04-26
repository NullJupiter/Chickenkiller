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