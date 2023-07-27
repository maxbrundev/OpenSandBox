#include "OpenSandBox.h"

#include "OpenSandBox/Tools/Utils/Maths.h"

float OpenSandBox::Utils::Maths::Lerp(const float p_start, const float p_end, const float p_alpha)
{
	return p_start + (p_end - p_start) * p_alpha;
}

uint32_t OpenSandBox::Utils::Maths::Pack(uint8_t p_value1, uint8_t p_value2, uint8_t p_value3, uint8_t p_value4)
{
	return (p_value1 << 24) | (p_value2 << 16) | (p_value3 << 8) | p_value4;
}

std::tuple<uint8_t, uint8_t, uint8_t, uint8_t> OpenSandBox::Utils::Maths::Unpack(uint32_t p_value)
{
	return std::make_tuple((p_value >> 24) & 0xff,
	                           (p_value >> 16) & 0xff,
		                       (p_value >> 8)  & 0xff,
		                       (p_value)       & 0xff);
}

float OpenSandBox::Utils::Maths::ToDegree(float p_radians)
{
	return p_radians * ( 180.0f / glm::pi<float>());
}

float OpenSandBox::Utils::Maths::ToRadians(float p_degree)
{
	return p_degree * (glm::pi<float>() / 180.0f);
}
