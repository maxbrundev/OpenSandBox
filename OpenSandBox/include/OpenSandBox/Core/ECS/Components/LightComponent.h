#pragma once

#include "OpenSandBox/API/Export.h"

#include "OpenSandBox/Core/ECS/Components/AComponent.h"

#include "OpenSandBox/Rendering/Entities/ELightType.h"
#include "OpenSandBox/Rendering/Entities/Light.h"

namespace OpenSandBox
{
	namespace ECS
	{
		class Actor;
	}
}

namespace OpenSandBox::ECS::Components
{
	class API_OPENSANDBOX LightComponent : public AComponent
	{
	public:
		LightComponent(Actor& p_owner, Rendering::Entities::ELightType p_type);
		virtual ~LightComponent() override = default;

		void Update(float p_deltaTime) override;

		void SetColor(const Data::Color& p_color);
		void SetIntensity(float p_intensity);
		void SetConstant(float p_constant);
		void SetLinear(float p_linear);
		void SetQuadratic(float p_quadratic);
		void SetCutoff(float p_cutoff);
		void SetOuterCutoff(float p_outerCutoff);

		Rendering::Entities::Light& GetLightData();

	private:
		Rendering::Entities::Light m_data;
	};
}