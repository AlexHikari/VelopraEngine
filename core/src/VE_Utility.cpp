#include "VE_Utility.h"
#include "VE_LoggerMacros.h"
#include <algorithm>
#include <cctype>
#include <fstream>
#include <filesystem>

namespace VelopraEngine {
	namespace Core {

		std::string TrimStart(const std::string& str) {
			auto it = std::find_if_not(str.begin(), str.end(), ::isspace);
			return { it, str.end() };
		}

		std::string TrimEnd(const std::string& str) {
			auto it = std::find_if_not(str.rbegin(), str.rend(), ::isspace).base();
			return { str.begin(), it };
		}

		std::string Trim(const std::string& str) {
			return TrimEnd(TrimStart(str));
		}

		std::vector<std::string> Split(const std::string& str, char delimiter) {
			std::vector<std::string> elements;
			std::string::size_type start = 0;
			std::string::size_type end = str.find(delimiter);

			while (end != std::string::npos) {
				elements.push_back(str.substr(start, end - start));
				start = end + 1;
				end = str.find(delimiter, start);
			}

			elements.push_back(str.substr(start, end - start)); // Last element
			return elements;
		}

		bool StartsWith(const std::string& str, const std::string& substr) {
			return str.rfind(substr, 0) == 0;
		}

		bool EndsWith(const std::string& str, const std::string& substr) {
			if (substr.size() > str.size()) return false;
			return std::equal(substr.rbegin(), substr.rend(), str.rbegin());
		}

		std::string ToUpper(const std::string& str) {
			std::string result;
			result.reserve(str.size());
			std::transform(str.begin(), str.end(), std::back_inserter(result), ::toupper);
			return result;
		}

		std::string ToLower(const std::string& str) {
			std::string result;
			result.reserve(str.size());
			std::transform(str.begin(), str.end(), std::back_inserter(result), ::tolower);
			return result;
		}

		bool ReadTextFile(const std::string& filepath, std::string& outContent) {
			std::ifstream file(filepath, std::ios::binary | std::ios::ate);
			if (!file) {
				VELOPRA_CORE_ERROR("Unable to open file for reading: {}", filepath);
				return false;
			}

			auto size = file.tellg();
			std::string buffer(size, '\0');
			file.seekg(0);
			file.read(&buffer[0], size);

			if (file) {
				outContent.swap(buffer); // Only assign the content if read was successful
				return true;
			}
			else {
				VELOPRA_CORE_ERROR("Failed to read from file: {}", filepath);
				return false;
			}
		}

		bool WriteTextFile(const std::string& filepath, const std::string& content) {
			std::ofstream file(filepath);
			if (!file) {
				VELOPRA_CORE_ERROR("Unable to open file for writing: {}", filepath);
				return false;
			}

			file.write(content.data(), content.size());
			if (!file) {
				VELOPRA_CORE_ERROR("Failed to write to file: {}", filepath);
				return false;
			}

			return true;
		}

	} // namespace Core
} // namespace VelopraEngine
