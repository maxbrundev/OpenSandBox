#pragma once

namespace OpenSandBox::Settings
{
	struct DriverSettings
	{
		bool enableDepthTest		= true;
		bool enableBackFaceCulling	= true;
		bool enableBlend			= true;
		bool enableMultisample		= true;
		bool enableDebugCallback	= true;
	};
}