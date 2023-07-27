#pragma once
#include "OpenSandBox/API/Export.h"

#include "OpenSandBox/Core/Renderer.h"
#include "OpenSandBox/Core/ECS/Actor.h"
#include "OpenSandBox/Core/ECS/Components/LightComponent.h"

namespace OpenSandBox::Core::SceneSystem
{
	class API_OPENSANDBOX Scene
	{
	public:
		Scene(std::string p_name);
		~Scene();

		void AddActor(ECS::Actor* p_actor);
		void DestroyActor(ECS::Actor*& p_actor);
		
		void DrawAll(Renderer& p_renderer, Resources::Material* p_defaultMaterial) const;
		void Update(float p_deltaTime) const;

		std::unordered_map<std::string, ECS::Actor*>& GetActors();
		const std::vector<ECS::Components::LightComponent*>& GetLights();

	private:
		bool m_isDebugingNormal = false;
		std::string m_name;
		std::unordered_map<std::string, ECS::Actor*> m_actors;
		std::vector<ECS::Components::LightComponent*> m_lights;
	};
}
