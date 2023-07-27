#pragma once

#include <string>
#include <any>

#include "OpenSandBox/Resources/EUniformType.h"

namespace OpenSandBox::Resources
{
	struct UniformInfo
	{
		EUniformType type;
		std::string  name;
		uint32_t     location;
		std::any     defaultValue;
	};
}
