#pragma once

#include "OpenSandBox/API/Export.h"

namespace OpenSandBox::Resources
{
	enum class API_OPENSANDBOX ETextureType : uint8_t
	{
		DIFFUSE_MAP,
		SPECULAR_MAP,
		NORMAL_MAP,
		HEIGHT_MAP,
		MASK_MAP
	};
}