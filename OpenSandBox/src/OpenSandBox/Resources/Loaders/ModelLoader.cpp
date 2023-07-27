#include "OpenSandBox.h"

#include "OpenSandBox/Resources/Loaders/ModelLoader.h"

OpenSandBox::Resources::Parsers::AssimpParser OpenSandBox::Resources::Loaders::ModelLoader::__ASSIMP;

std::string OpenSandBox::Resources::Loaders::ModelLoader::__FILE_TRACE;

OpenSandBox::Resources::Model* OpenSandBox::Resources::Loaders::ModelLoader::Create(const std::string& p_filePath, bool p_isLoadingMaterial)
{
	__FILE_TRACE = p_filePath;

	auto model = new Model(p_filePath);

	if(__ASSIMP.LoadModel(p_filePath, *model, p_isLoadingMaterial))
	{
		return model;
	}

	delete model;

	return nullptr;
}

void OpenSandBox::Resources::Loaders::ModelLoader::Reload(Model& p_model, const std::string& p_filePath, bool p_isLoadingMaterial)
{
	Model* newModel = Create(p_filePath, p_isLoadingMaterial);

	if (newModel)
	{
		p_model.m_meshes = newModel->m_meshes;
		newModel->m_meshes.clear();
		delete newModel;
	}
}

bool OpenSandBox::Resources::Loaders::ModelLoader::Destroy(Model*& p_modelInstance)
{
	if (p_modelInstance)
	{
		delete p_modelInstance;
		p_modelInstance = nullptr;

		return true;
	}

	return false;
}
