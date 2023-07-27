#include "OpenSandBox.h"

#include "OpenSandBox/Core/ECS/Components/LightComponent.h"

#include "OpenSandBox/Core/ECS/Actor.h"

OpenSandBox::ECS::Components::LightComponent::LightComponent(Actor& p_owner, Rendering::Entities::ELightType p_type): AComponent(p_owner), m_data(p_owner.GetTransform(), p_type)
{

}

void OpenSandBox::ECS::Components::LightComponent::Update(float p_deltaTime)
{

}

void OpenSandBox::ECS::Components::LightComponent::SetColor(const Data::Color& p_color)
{
	m_data.color = p_color;
}

void OpenSandBox::ECS::Components::LightComponent::SetIntensity(float p_intensity)
{
	m_data.intensity = p_intensity;
}

void OpenSandBox::ECS::Components::LightComponent::SetConstant(float p_constant)
{
	m_data.constant = p_constant;
}

void OpenSandBox::ECS::Components::LightComponent::SetLinear(float p_linear)
{
	m_data.linear = p_linear;
}

void OpenSandBox::ECS::Components::LightComponent::SetQuadratic(float p_quadratic)
{
	m_data.quadratic = p_quadratic;
}

void OpenSandBox::ECS::Components::LightComponent::SetCutoff(float p_cutoff)
{
	m_data.cutoff = p_cutoff;
}

void OpenSandBox::ECS::Components::LightComponent::SetOuterCutoff(float p_outerCutoff)
{
	m_data.outerCutoff = p_outerCutoff;
}

OpenSandBox::Rendering::Entities::Light& OpenSandBox::ECS::Components::LightComponent::GetLightData()
{
	return m_data;
}
