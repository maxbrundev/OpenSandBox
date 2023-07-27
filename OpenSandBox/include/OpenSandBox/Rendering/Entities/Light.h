#pragma once

#include "OpenSandBox/Rendering/Entities/ELightType.h"

#include "OpenSandBox/Maths/Transform.h"
#include "OpenSandBox/Data/Color.h"

namespace OpenSandBox::Rendering::Entities
{
	struct Light
	{
		Light(Maths::Transform& p_tranform, ELightType p_type);

		glm::mat4 GenerateMatrix() const;

		Data::Color	color		= { 1.0f, 1.0f, 1.0f };
		float		intensity	= 1.0f;
		float		constant	= 0.0f;
		float		linear		= 0.0f;
		float		quadratic	= 1.0f;
		float		cutoff		= 12.0f;
		float		outerCutoff = 15.0f;
		float		type		= 0.0f;

	private:
		Maths::Transform& m_transform;
	};
}
