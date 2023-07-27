#pragma once

namespace OpenSandBox::Rendering::Entities
{
	enum class ELightType : uint8_t
	{
		POINT,
		DIRECTIONAL,
		SPOT,
		AMBIENT
	};
}