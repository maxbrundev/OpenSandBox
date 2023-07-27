#include "OpenSandBox.h"

#include "OpenSandBox/Core/ECS/Components/AComponent.h"

#include "OpenSandBox/Core/ECS/Actor.h"

OpenSandBox::ECS::Components::AComponent::AComponent(Actor& p_owner) : owner(p_owner)
{
}
