#pragma once

#include <GL/glew.h>

#include "OpenSandBox/API/Export.h"

#include "OpenSandBox/Settings/DriverSettings.h"

namespace  OpenSandBox::Context
{
	class API_OPENSANDBOX Driver
	{
	public:
		Driver(const Settings::DriverSettings& p_driverSettings);
		~Driver() = default;

		void DisplayDriverInfo();
		
	private:
		void InitGlew();

	private:
		bool isActive;
	};
}
