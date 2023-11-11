#ifndef VELOPRA_ENGINE_CORE_UTILITY_H
#define VELOPRA_ENGINE_CORE_UTILITY_H

#include <string>
#include <vector>

namespace VelopraEngine {
	namespace Core {

		// Trims whitespace from the start of a string.
		std::string TrimStart(const std::string& str);

		// Trims whitespace from the end of a string.
		std::string TrimEnd(const std::string& str);

		// Trims whitespace from both ends of a string.
		std::string Trim(const std::string& str);

		// Splits a string into a vector of strings based on the given delimiter.
		std::vector<std::string> Split(const std::string& str, char delimiter);

		// Checks if the string starts with the given substring.
		bool StartsWith(const std::string& str, const std::string& substr);

		// Checks if the string ends with the given substring.
		bool EndsWith(const std::string& str, const std::string& substr);

		// Converts a string to uppercase.
		std::string ToUpper(const std::string& str);

		// Converts a string to lowercase.
		std::string ToLower(const std::string& str);

		// Reads the entire content of a text file into a string.
		bool ReadTextFile(const std::string& filepath, std::string& outContent);

		// Writes text content to a file, overwriting any existing content.
		bool WriteTextFile(const std::string& filepath, const std::string& content);

	} // namespace Core
} // namespace VelopraEngine

#endif // VELOPRA_ENGINE_CORE_UTILITY_H
