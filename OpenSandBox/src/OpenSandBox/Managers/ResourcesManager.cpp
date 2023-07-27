#include "OpenSandBox.h"

#include "OpenSandBox/Managers/ResourcesManager.h"

#include "OpenSandBox/Resources/Loaders/ModelLoader.h"
#include "OpenSandBox/Resources/Loaders/ShaderLoader.h"
#include "OpenSandBox/Resources/Loaders/TextureLoader.h"

//OpenSandBox::Managers::ResourcesManager* OpenSandBox::Managers::ResourcesManager::m_instance = nullptr;
//OpenSandBox::Managers::ResourcesManager OpenSandBox::Managers::ResourcesManager::m_instance;

//OpenSandBox::Managers::ResourcesManager& OpenSandBox::Managers::ResourcesManager::Instance()
//{
//	//static ResourcesManager m_instance;
//	//return m_instance;
//
//	if(m_instance == nullptr)
//	{
//		m_instance = new ResourcesManager();
//	} 
//	
//	return *m_instance;
//}

//void OpenSandBox::Managers::ResourcesManager::Dispose()
//{
//	delete m_instance;
//	m_instance = nullptr;
//}

std::string OpenSandBox::Managers::ResourcesManager::__PROJECT_ASSETS_PATH = "";

OpenSandBox::Resources::Model& OpenSandBox::Managers::ResourcesManager::LoadModel(const std::string_view p_name, const std::string& p_filePath, bool p_isLoadingMaterial)
{
	if (m_modelResources.find(p_name) != m_modelResources.end())
		return *m_modelResources[p_name];

	const std::string realPath = __PROJECT_ASSETS_PATH + p_filePath;

	auto model = Resources::Loaders::ModelLoader::Create(realPath, p_isLoadingMaterial);
	
	const auto res = m_modelResources.emplace(p_name, model);
	return *res.first->second;
}

OpenSandBox::Resources::Shader& OpenSandBox::Managers::ResourcesManager::LoadShader(const std::string_view p_name,
	const std::string& p_filePath)
{
	if (m_shaderResources.find(p_name) != m_shaderResources.end())
		return *m_shaderResources[p_name];

	const std::string realPath = __PROJECT_ASSETS_PATH + p_filePath;

	Resources::Shader* shader = Resources::Loaders::ShaderLoader::Create(realPath);

	const auto res = m_shaderResources.emplace(p_name, shader);
	return *res.first->second;
}

OpenSandBox::Resources::Shader& OpenSandBox::Managers::ResourcesManager::LoadShaderFiles(const std::string_view p_name,
	const std::string& p_VertexFilePath, const std::string& p_FragmentFilePath)
{
	if (m_shaderResources.find(p_name) != m_shaderResources.end())
		return *m_shaderResources[p_name];

	const std::string vertexRealPath   = __PROJECT_ASSETS_PATH + p_VertexFilePath;
	const std::string fragmentRealPath = __PROJECT_ASSETS_PATH + p_FragmentFilePath;

	Resources::Shader* shader = Resources::Loaders::ShaderLoader::CreateFromSource(vertexRealPath, fragmentRealPath);

	const auto res = m_shaderResources.emplace(p_name, shader);
	return *res.first->second;
}

OpenSandBox::Resources::Texture& OpenSandBox::Managers::ResourcesManager::LoadTexture(const std::string_view p_name, const std::string& p_filePath, Resources::ETextureFilteringMode p_firstFilter, Resources::ETextureFilteringMode p_secondFilter, Resources::ETextureType p_textureType, bool p_flipVertically, bool p_generateMipmap)
{
	if (m_TextureResources.find(p_name) != m_TextureResources.end())
		return *m_TextureResources[p_name];

	const std::string realPath = __PROJECT_ASSETS_PATH + p_filePath;

	Resources::Texture* texture = Resources::Loaders::TextureLoader::Create(realPath, p_firstFilter, p_secondFilter, p_textureType, p_flipVertically, p_generateMipmap);

	const auto res = m_TextureResources.emplace(p_name, texture);
	return *res.first->second;
}

void OpenSandBox::Managers::ResourcesManager::ProvideAssetPath(const std::string& p_projectAssetsPath)
{
	__PROJECT_ASSETS_PATH = p_projectAssetsPath;
}

OpenSandBox::Resources::Shader& OpenSandBox::Managers::ResourcesManager::GetShader(const std::string_view p_name) const
{
	return *m_shaderResources.at(p_name);
}

OpenSandBox::Resources::Texture& OpenSandBox::Managers::ResourcesManager::GetTexture(const std::string_view p_name) const
{
	return  *m_TextureResources.at(p_name);
}

OpenSandBox::Resources::Model & OpenSandBox::Managers::ResourcesManager::GetModel(const std::string_view p_name) const
{
	return *m_modelResources.at(p_name);
}
