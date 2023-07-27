#include "pch.h"

#include <OpenSandBox/Tools/Utils/Defines.h>
FORCE_DEDICATED_GPU

#include "Application.h"


int main()
{
	OpenSandBox::Settings::DeviceSettings deviceSettings;
	deviceSettings.contextVersionMajor = 4;
	deviceSettings.contextVersionMinor = 3;
	deviceSettings.debugProfile = true;
	
	OpenSandBox::Settings::WindowSettings windowSettings;
	windowSettings.title = "SandBox";
	windowSettings.width = 1280;
	windowSettings.height = 720;
	windowSettings.resizable = true;
	windowSettings.vsync = false;
	windowSettings.fullScreen = false;
	windowSettings.samples = 4;

	OpenSandBox::Settings::DriverSettings driverSettings;
	driverSettings.enableDepthTest = true;
	driverSettings.enableBlend = true;
	driverSettings.enableBackFaceCulling = true;
	driverSettings.enableMultisample = true;
	driverSettings.enableDebugCallback = true;

	const auto listenerId = OpenSandBox::Context::Device::ErrorEvent += [](OpenSandBox::Context::EDeviceError device_error, std::string error_message)
	{
		error_message = "OpenSandBox requires OpenGL 4.3 or newer.\r\n" + error_message;
		std::cout << error_message.c_str() << std::endl;
	};

	const std::unique_ptr<Example::Application> exampleApp = std::make_unique<Example::Application>(deviceSettings, windowSettings, driverSettings);

	OpenSandBox::Context::Device::ErrorEvent -= listenerId;

	exampleApp->Setup();
	exampleApp->Run();

	return 0;
}