#include "OpenSandBox.h"

#include "OpenSandBox/Core/ECS/Components/ModelComponent.h"

#include "OpenSandBox/Core/ECS/Actor.h"

#include "OpenSandBox/Managers/ResourcesManager.h"
//#include "OpenSandBox/Tools/Utils/String.h"

OpenSandBox::ECS::Components::ModelComponent::ModelComponent(Actor& p_owner, std::string_view p_name, const std::string& p_filePath, bool p_isLoadingMaterial) : AComponent(p_owner),
	m_model(&Managers::ResourcesManager::Instance().LoadModel(p_name, p_filePath, p_isLoadingMaterial)), m_name(p_name)
{
	//std::string name = Utils::String::RemoveExtensionFromFileName(Utils::String::ExtractFileNameFromPath(p_filePath));
}

OpenSandBox::ECS::Components::ModelComponent::~ModelComponent()
{
	if(m_model != nullptr)
	{
		m_model = nullptr;
	}

	// Require Model to be shared pointer in order to unload the resource if the reference count is <= 1
	//Managers::ResourcesManager::Instance().RemoveModel(m_name);
}

void OpenSandBox::ECS::Components::ModelComponent::Update(float p_deltaTime)
{

}

OpenSandBox::Resources::Model* OpenSandBox::ECS::Components::ModelComponent::GetModel() const
{
	return m_model;
}

std::vector<OpenSandBox::Resources::Mesh*>& OpenSandBox::ECS::Components::ModelComponent::GetMeshes() const
{
	return m_model->GetMeshes();
}
