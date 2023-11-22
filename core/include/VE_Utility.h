#ifndef VE_CORE_UTILITY_H
#define VE_CORE_UTILITY_H

#include "VE_CoreAPI.h"
#include <string>
#include <vector>

namespace velopraEngine {
namespace core {

// Trims whitespace from the start of a string.
VELOPRACORE_API std::string TrimStart(const std::string &str);

// Trims whitespace from the end of a string.
VELOPRACORE_API std::string TrimEnd(const std::string &str);

// Trims whitespace from both ends of a string.
VELOPRACORE_API std::string Trim(const std::string &str);

// Splits a string into a vector of strings based on the given delimiter.
VELOPRACORE_API std::vector<std::string> Split(const std::string &str,
                                               char delimiter);

// Checks if the string starts with the given substring.
VELOPRACORE_API bool StartsWith(const std::string &str,
                                const std::string &substr);

// Checks if the string ends with the given substring.
VELOPRACORE_API bool EndsWith(const std::string &str,
                              const std::string &substr);

// Converts a string to uppercase.
VELOPRACORE_API std::string ToUpper(const std::string &str);

// Converts a string to lowercase.
VELOPRACORE_API std::string ToLower(const std::string &str);

// Reads the entire content of a text file into a string.
VELOPRACORE_API bool ReadTextFile(const std::string &filepath,
                                  std::string &outContent);

// Writes text content to a file, overwriting any existing content.
VELOPRACORE_API bool WriteTextFile(const std::string &filepath,
                                   const std::string &content);

} // namespace core
} // namespace velopraEngine

#endif // VE_CORE_UTILITY_H
