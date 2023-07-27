#pragma once

namespace OpenSandBox::Resources
{
	class RawShader
	{
	public:
		static std::pair<std::string, std::string> GetGrid();

		static std::pair<std::string, std::string> GetNormalVisualizer();
	};
}
