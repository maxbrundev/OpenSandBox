#pragma once

#include <OpenSandBox/Context/Driver.h>
#include <OpenSandBox/Context/Device.h>
#include <OpenSandBox/Context/Window.h>

#include <OpenSandBox/Inputs/InputManager.h>

#include <OpenSandBox/Core/Renderer.h>

#include <OpenSandBox/Core/SceneSystem/Scene.h>

#include <OpenSandBox/Buffers/UniformBuffer.h>
#include <OpenSandBox/Buffers/ShaderStorageBuffer.h>

namespace Example
{
	class Application
	{
	public:
		Application(const OpenSandBox::Settings::DeviceSettings& p_deviceSettings, const OpenSandBox::Settings::WindowSettings& p_windowSettings, const OpenSandBox::Settings::DriverSettings& p_driverSettings);
		~Application() = default;

		void Setup();
		void Run();
		void HandleInput() const;

		bool IsRunning() const;

	private:
		std::unique_ptr<OpenSandBox::Context::Device> device;
		std::unique_ptr<OpenSandBox::Context::Window> window;
		std::unique_ptr<OpenSandBox::Context::Driver> driver;

		std::unique_ptr<OpenSandBox::Inputs::InputManager> inputManager;

		std::unique_ptr<OpenSandBox::Core::Renderer> renderer;

		std::unique_ptr<OpenSandBox::Buffers::UniformBuffer> UBO;
		std::unique_ptr<OpenSandBox::Buffers::ShaderStorageBuffer> lightSSBO;

		std::unique_ptr<OpenSandBox::LowRenderer::CameraController> m_cameraController;

		std::unique_ptr<OpenSandBox::Core::SceneSystem::Scene> m_scene;

		OpenSandBox::Resources::Material m_defaultMaterial;

		glm::vec3 m_cameraPosition;

		OpenSandBox::LowRenderer::Camera m_camera;

		const std::string projectAssetsPath;

		bool isRunning;
	};
}
