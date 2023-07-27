#pragma once

#include <GLFW/glfw3.h>

#include "OpenSandBox/API/Export.h"

#include "OpenSandBox/Settings/DeviceSettings.h"

#include "OpenSandBox/Context/EDeviceError.h"

#include "OpenSandBox/Eventing/Event.h"

namespace OpenSandBox::Context
{
	class API_OPENSANDBOX Device
	{
	public:
		static Eventing::Event<EDeviceError, std::string> ErrorEvent;
		
		Device(const Settings::DeviceSettings& p_deviceSettings);
		~Device();

		void PollEvents() const;
		
		void SetVsync(bool p_value);
		bool HasVsync() const;
		
		float GetElapsedTime() const;
		
	private:
		void InitGLFW();
		void BindErrorCallback();

	private:
		bool m_isAlive = false;
		bool m_vsync = false;
	};
}
