#include "OpenSandBox.h"

#include "OpenSandBox/Core/SceneSystem/Scene.h"

#include "OpenSandBox/Core/ECS/Components/ModelComponent.h"
#include "OpenSandBox/Core/ECS/Components/LightComponent.h"

#include "OpenSandBox/Resources/Shader.h"

OpenSandBox::Core::SceneSystem::Scene::Scene(std::string p_name) : m_name(std::move(p_name))
{
}

OpenSandBox::Core::SceneSystem::Scene::~Scene()
{
	for (auto& actor : m_actors)
	{
		delete actor.second;
		actor.second = nullptr;
	}

	m_actors.clear();
	m_lights.clear();
}

void OpenSandBox::Core::SceneSystem::Scene::AddActor(ECS::Actor* p_actor)
{
	const auto& actor = m_actors.emplace(p_actor->GetName(), p_actor);

	if(auto lightComponent = actor.first->second->GetComponent<ECS::Components::LightComponent>(); lightComponent != nullptr)
	{
		m_lights.emplace_back(lightComponent);
	}
}

void OpenSandBox::Core::SceneSystem::Scene::DestroyActor(ECS::Actor*& p_actor)
{
	const auto it = m_actors.find(p_actor->GetName());
	
	if(it != m_actors.end())
	{
		delete p_actor;
		p_actor = nullptr;
	
		m_actors.erase(it->first);
	}
}

void OpenSandBox::Core::SceneSystem::Scene::DrawAll(Renderer& p_renderer, Resources::Material* p_defaultMaterial) const
{
	for (const auto& actor : m_actors)
	{
		if(const auto modelComponent = actor.second->GetComponent<ECS::Components::ModelComponent>(); modelComponent != nullptr)
		{
			p_renderer.Draw(*modelComponent->GetModel(), &actor.second->GetTransform().GetWorldMatrix(), p_defaultMaterial);
		}
	}
}

void OpenSandBox::Core::SceneSystem::Scene::Update(float p_deltaTime) const
{
	for (const auto& actor : m_actors)
	{
		// TODO: Find a better way to access lights.
		actor.second->Update(m_lights, p_deltaTime);
	}
}

std::unordered_map<std::string, OpenSandBox::ECS::Actor*>& OpenSandBox::Core::SceneSystem::Scene::GetActors()
{
	return m_actors;
}

const std::vector<OpenSandBox::ECS::Components::LightComponent*>& OpenSandBox::Core::SceneSystem::Scene::GetLights()
{
	return m_lights;
}
