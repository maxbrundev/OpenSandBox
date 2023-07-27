#pragma once

#include "OpenSandBox/API/Export.h"

#include "OpenSandBox/Core/ECS/Components/AComponent.h"

#include "OpenSandBox/Resources/Model.h"

namespace OpenSandBox
{
	namespace ECS
	{
		class Actor;
	}
}

namespace OpenSandBox::ECS::Components
{
	class API_OPENSANDBOX ModelComponent : public AComponent
	{
	public:
		ModelComponent(Actor& p_owner, std::string_view p_name, const std::string& p_filePath, bool p_isLoadingMaterial = false);
		virtual ~ModelComponent() override;

		void Update(float p_deltaTime) override;

		Resources::Model* GetModel() const;
		std::vector<Resources::Mesh*>& GetMeshes() const;

	private:
		Resources::Model* m_model;
		std::string_view m_name;
	};
}
