#pragma once

#include "OpenSandBox/API/Export.h"

namespace OpenSandBox::Utils
{
	class API_OPENSANDBOX Maths
	{
	public:
		Maths() = delete;

		static float Lerp(const float p_start, const float p_end, const float p_alpha);

		static uint32_t Pack(uint8_t p_value1, uint8_t p_value2, uint8_t p_value3, uint8_t p_value4);
		static std::tuple<uint8_t, uint8_t, uint8_t, uint8_t> Unpack(uint32_t p_value);
		
		static float ToDegree(float p_radians);
		static float ToRadians(float p_degree);
	};
}
