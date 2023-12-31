#include "OpenSandBox.h"

#include "OpenSandBox/Tools/Utils/ColorsUtility.h"

#include "OpenSandBox/Tools/Utils/Maths.h"

OpenSandBox::Data::Color OpenSandBox::Utils::ColorsUtility::RGBAToNormalized(Data::Color p_color)
{
	return { static_cast<float>(p_color.r * 0.0039215686274509803921568627451),
		         static_cast<float>(p_color.g * 0.0039215686274509803921568627451),
		         static_cast<float>(p_color.b * 0.0039215686274509803921568627451),
		             p_color.a
	};
}

OpenSandBox::Data::Color OpenSandBox::Utils::ColorsUtility::NormalizedToRGBA(Data::Color p_color)
{
	return { p_color.r * 255.0f,
		         p_color.g * 255.0f,
		         p_color.b * 255.0f,
		             p_color.a
	};
}

uint32_t OpenSandBox::Utils::ColorsUtility::PackRGBAToNormalized(Data::Color p_color)
{
	const auto& normalized = RGBAToNormalized(p_color);

	return Maths::Pack(static_cast<uint8_t>(normalized.r), static_cast<uint8_t>(normalized.g), static_cast<uint8_t>(normalized.b), normalized.a);
}

uint32_t OpenSandBox::Utils::ColorsUtility::PackNormalizedToRGBA(Data::Color p_color)
{
	const auto& rgba = NormalizedToRGBA(p_color);

	return Maths::Pack(static_cast<uint8_t>(rgba.r), static_cast<uint8_t>(rgba.g), static_cast<uint8_t>(rgba.b), rgba.a);
}
