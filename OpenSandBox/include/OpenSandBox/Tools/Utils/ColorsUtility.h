#pragma once

#include "OpenSandBox/API/Export.h"

#include "OpenSandBox/Data/Color.h"

namespace OpenSandBox::Utils
{
	struct API_OPENSANDBOX ColorsUtility
	{
		ColorsUtility() = delete;

		static Data::Color RGBAToNormalized(Data::Color p_color);
		static Data::Color NormalizedToRGBA(Data::Color p_color);

		static uint32_t PackRGBAToNormalized(Data::Color p_color);
		static uint32_t PackNormalizedToRGBA(Data::Color p_color);
	};
}
