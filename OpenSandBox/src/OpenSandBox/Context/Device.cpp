#include "OpenSandBox.h"

#include "OpenSandBox/Context/Device.h"

OpenSandBox::Eventing::Event<OpenSandBox::Context::EDeviceError, std::string> OpenSandBox::Context::Device::ErrorEvent;

OpenSandBox::Context::Device::Device(const Settings::DeviceSettings& p_deviceSettings)
{
	InitGLFW();

	m_isAlive = true;

	if (p_deviceSettings.debugProfile)
		BindErrorCallback();
	
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, p_deviceSettings.debugProfile);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, p_deviceSettings.contextVersionMajor);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, p_deviceSettings.contextVersionMinor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

OpenSandBox::Context::Device::~Device()
{
	if(m_isAlive)
	{
		glfwTerminate();
	}
}

void OpenSandBox::Context::Device::InitGLFW()
{
	const int initializationCode = glfwInit();
	
	if (initializationCode == GLFW_FALSE)
	{
		glfwTerminate();
		throw std::runtime_error("Failed to Init GLFW");
	}
}

void OpenSandBox::Context::Device::PollEvents() const
{
	glfwPollEvents();
}

void OpenSandBox::Context::Device::SetVsync(bool p_value)
{
	glfwSwapInterval(p_value ? 1 : 0);
	m_vsync = p_value;
}

bool OpenSandBox::Context::Device::HasVsync() const
{
	return m_vsync;
}

float OpenSandBox::Context::Device::GetElapsedTime() const
{
	return static_cast<float>(glfwGetTime());
}

void OpenSandBox::Context::Device::BindErrorCallback()
{
	auto errorCallback = [](int p_code, const char* p_description)
	{
		ErrorEvent.Invoke(static_cast<EDeviceError>(p_code), p_description);
	};
	
	glfwSetErrorCallback(errorCallback);
}
