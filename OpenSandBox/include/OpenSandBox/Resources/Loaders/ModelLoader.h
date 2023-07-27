#pragma once

#include "OpenSandBox/API/Export.h"

#include "OpenSandBox/Resources/Model.h"
#include "OpenSandBox/Resources/Parsers/AssimpParser.h"

namespace OpenSandBox::Resources::Loaders
{
	class API_OPENSANDBOX ModelLoader
	{
	public:
		ModelLoader() = delete;

		static Model* Create(const std::string& p_filePath, bool p_isLoadingMaterial = false);
		static void Reload(Model& p_model, const std::string& p_filePath, bool p_isLoadingMaterial = false);
		static bool Destroy(Model*& p_modelInstance);

	private:
		static Resources::Parsers::AssimpParser __ASSIMP;
		static std::string __FILE_TRACE;
	};
}