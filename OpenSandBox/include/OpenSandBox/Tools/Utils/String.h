#pragma once

#include "OpenSandBox/API/Export.h"

namespace Utils
{
	class API_OPENSANDBOX String
	{
	public:
		String() = delete;

		static std::string ExtractDirectoryFromPath(const std::string& p_path);
		static std::string ExtractFileNameFromPath(const std::string& p_path);
		static std::string RemoveExtensionFromFileName(const std::string& p_file);
		static std::string IntToString(int p_number);
		static int StringToInt(const std::string& p_string);
		static int* StringToIntArray(const std::string& p_string);
		static void ParseInputIntoVector(const std::string& p_inputString, std::vector<std::string>& p_outVector);
		static std::string RemoveAllOcurrences(const std::string& p_target, const char p_character);
		static std::string ToUpper(const std::string& p_target);
		static std::string ToMinor(const std::string& p_target);
	};
}
