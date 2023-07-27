#include "OpenSandBox.h"

#include "OpenSandBox/Core/ECS/Actor.h"

#include <chrono>

#include "OpenSandBox/Core/ECS/Components/ModelComponent.h"

#include "OpenSandBox/Resources/Shader.h"

OpenSandBox::Eventing::Event<OpenSandBox::ECS::Actor&> OpenSandBox::ECS::Actor::CreatedEvent;
OpenSandBox::Eventing::Event<OpenSandBox::ECS::Actor&> OpenSandBox::ECS::Actor::DestroyEvent;

OpenSandBox::ECS::Actor::Actor(std::string p_name) : m_name(std::move(p_name))
{
	CreatedEvent.Invoke(*this);
}

OpenSandBox::ECS::Actor::~Actor()
{
	for (auto& component : m_components)
	{
		delete component;
		component = nullptr;
	}

	m_components.clear();

	for(auto child : m_children)
	{
		child->RemoveParent();
	}

	m_children.clear();

	RemoveParent();

	DestroyEvent.Invoke(*this);
}

void OpenSandBox::ECS::Actor::Update(const std::vector<Components::LightComponent*>& p_lights, float p_deltaTime) const
{
	for (const auto component : m_components)
	{
		component->Update(p_deltaTime);
	}
}

void OpenSandBox::ECS::Actor::RemoveParent()
{
	if (m_parent)
	{
		auto predicate = [this](Actor* p_element)
		{
			return p_element == this;
		};

		m_parent->m_children.erase(std::remove_if(m_parent->m_children.begin(), m_parent->m_children.end(), std::ref(predicate)));
	}

	m_parent = nullptr;

	m_transform.RemoveParent();
}

bool OpenSandBox::ECS::Actor::HasChildren() const
{
	return !m_children.empty();
}

void OpenSandBox::ECS::Actor::SetName(std::string p_name)
{
	m_name = std::move(p_name);
}

void OpenSandBox::ECS::Actor::SetParent(Actor& p_parent)
{
	m_transform.RemoveParent();

	m_parent = &p_parent;
	m_transform.SetParent(p_parent.GetTransform());
	p_parent.m_children.push_back(this);
}

std::string OpenSandBox::ECS::Actor::GetName()
{
	return m_name;
}

OpenSandBox::ECS::Actor* OpenSandBox::ECS::Actor::GetParent() const
{
	return m_parent;
}

std::vector<OpenSandBox::ECS::Actor*>& OpenSandBox::ECS::Actor::GetChildren()
{
	return m_children;
}

OpenSandBox::Maths::Transform& OpenSandBox::ECS::Actor::GetTransform()
{
	return m_transform;
}
