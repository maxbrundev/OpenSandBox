#include "pch.h"

#include "Application.h"

#include <OpenSandBox/Managers/ResourcesManager.h>

#include <OpenSandBox/Tools/Time/Clock.h>
#include <OpenSandBox/Tools/Utils/ServiceLocator.h>
#include <OpenSandBox/Resources/Loaders/ShaderLoader.h>
#include <OpenSandBox/Core/ECS/Components/ModelComponent.h>

Example::Application::Application(const OpenSandBox::Settings::DeviceSettings & p_deviceSettings, const OpenSandBox::Settings::WindowSettings & p_windowSettings, const OpenSandBox::Settings::DriverSettings & p_driverSettings) :
	m_cameraPosition(0.0f, 0.0f, 0.0f),
	projectAssetsPath("Assets\\"),
	isRunning(false)
{
	device       = std::make_unique<OpenSandBox::Context::Device>(p_deviceSettings);
	window       = std::make_unique<OpenSandBox::Context::Window>(*device, p_windowSettings);
	driver       = std::make_unique<OpenSandBox::Context::Driver>(p_driverSettings);
	renderer     = std::make_unique<OpenSandBox::Core::Renderer>(*driver);
	inputManager = std::make_unique<OpenSandBox::Inputs::InputManager>(*window);

	Utils::ServiceLocator::Provide(*window);
	Utils::ServiceLocator::Provide(*inputManager);
	Utils::ServiceLocator::Provide(*renderer);

	OpenSandBox::Managers::ResourcesManager::ProvideAssetPath(projectAssetsPath);

	UBO = std::make_unique<OpenSandBox::Buffers::UniformBuffer>
		(
			/* UBO Data Layout */
			sizeof(glm::mat4) +
			sizeof(glm::mat4) +
			sizeof(glm::mat4) +
			sizeof(glm::vec3),
			0, 0,
			OpenSandBox::Buffers::EAccessSpecifier::STREAM_DRAW
		);
	
	lightSSBO = std::make_unique<OpenSandBox::Buffers::ShaderStorageBuffer>(OpenSandBox::Buffers::EAccessSpecifier::STREAM_DRAW);

	renderer->RegisterModelMatrixSender([this](const glm::mat4& p_modelMatrix)
	{
		UBO->SetSubData(p_modelMatrix, 0);
	});

	OpenSandBox::Managers::ResourcesManager::Instance().LoadShader("Standard", "Shaders\\Standard.glsl");
	OpenSandBox::Managers::ResourcesManager::Instance().LoadShader("Lambert", "Shaders\\Lambert.glsl");

	m_defaultMaterial.SetShader(&OpenSandBox::Managers::ResourcesManager::Instance().GetShader("Standard"));

	m_cameraController = std::make_unique<OpenSandBox::LowRenderer::CameraController>(m_camera, m_cameraPosition);

	m_scene = std::make_unique<OpenSandBox::Core::SceneSystem::Scene>("SandBox");

	isRunning = true;
}

void Example::Application::Setup()
{
	auto& resourcesManager = OpenSandBox::Managers::ResourcesManager::Instance();

	resourcesManager.LoadTexture("crystal_diffuse", "Textures\\crystal.jpg", OpenSandBox::Resources::ETextureFilteringMode::NEAREST_MIPMAP_LINEAR, OpenSandBox::Resources::ETextureFilteringMode::NEAREST, OpenSandBox::Resources::ETextureType::DIFFUSE_MAP,true, true);
	resourcesManager.LoadTexture("crystal_specular", "Textures\\crystal_spec.jpg", OpenSandBox::Resources::ETextureFilteringMode::NEAREST_MIPMAP_LINEAR, OpenSandBox::Resources::ETextureFilteringMode::NEAREST, OpenSandBox::Resources::ETextureType::SPECULAR_MAP, true, true);
}

void Example::Application::Run()
{
	Utils::Clock clock;

	OpenSandBox::Maths::Transform cubeTransform;

	auto* crystalMaterial = new OpenSandBox::Resources::Material();

	auto& resourcesManager = OpenSandBox::Managers::ResourcesManager::Instance();
	auto& modelCube = resourcesManager.LoadModel("Cube", "Models\\Cube.fbx");
	
	modelCube.GetMaterials()[0] = crystalMaterial;

	crystalMaterial->SetTexture(&resourcesManager.GetTexture("crystal_diffuse"));
	crystalMaterial->SetTexture(&resourcesManager.GetTexture("crystal_specular"));

	modelCube.SetShader(resourcesManager.GetShader("Standard"));

	OpenSandBox::ECS::Actor* testActor = new OpenSandBox::ECS::Actor("Actor1");
	OpenSandBox::ECS::Actor* testActor2 = new OpenSandBox::ECS::Actor("Actor2");
	OpenSandBox::ECS::Actor* testActor3 = new OpenSandBox::ECS::Actor("Actor3");

	OpenSandBox::ECS::Actor* directionalLight = new OpenSandBox::ECS::Actor("Directional Light");
	directionalLight->AddComponent<OpenSandBox::ECS::Components::LightComponent>(OpenSandBox::Rendering::Entities::ELightType::DIRECTIONAL);
	directionalLight->GetComponent<OpenSandBox::ECS::Components::LightComponent>()->SetIntensity(0.750f);

	testActor->AddComponent<OpenSandBox::ECS::Components::ModelComponent>("Sponza", "Models\\Sponza\\sponza.obj", true);
	testActor->GetComponent<OpenSandBox::ECS::Components::ModelComponent>()->GetModel()->SetShader(resourcesManager.GetShader("Standard"));
	testActor->GetTransform().SetWorldScale({ 0.05f, 0.05f, 0.05f });

	testActor2->AddComponent<OpenSandBox::ECS::Components::ModelComponent>("Nanosuit", "Models\\Nanosuit\\nanosuit.obj", true);
	testActor2->GetComponent<OpenSandBox::ECS::Components::ModelComponent>()->GetModel()->SetShader(resourcesManager.GetShader("Standard"));

	testActor3->AddComponent<OpenSandBox::ECS::Components::ModelComponent>("Nanosuit", "Models\\Nanosuit\\nanosuit.obj", true);
	testActor3->GetComponent<OpenSandBox::ECS::Components::ModelComponent>()->GetModel()->SetShader(resourcesManager.GetShader("Standard"));
	testActor3->SetParent(*testActor2);
	testActor3->GetTransform().SetLocalPosition({ 10.0f, 0.0f, 0.0f });

	m_scene->AddActor(testActor);
	m_scene->AddActor(testActor2);
	m_scene->AddActor(testActor3);
	m_scene->AddActor(directionalLight);

	while (IsRunning())
	{
		device->PollEvents();

		renderer->SetClearColor(0.1f, 0.1f, 0.1f);
		renderer->Clear(true, true, true);

		m_scene->Update(clock.GetDeltaTime());
		
		m_cameraController->Update(clock.GetDeltaTime());

		m_camera.CalculateMatrices(window->GetSize().first, window->GetSize().second, m_cameraPosition);

		size_t offset = sizeof(glm::mat4); // We skip the model matrix (Which is a special case, modified every draw calls)
		UBO->SetSubData(m_camera.GetViewMatrix(), offset);
		UBO->SetSubData(m_camera.GetProjectionMatrix(), offset);
		UBO->SetSubData(m_cameraPosition, offset);

		renderer->Clear(m_cameraController->GetCamera(), true, true, true);

		auto lightMatrices = renderer->FindLightMatrices(*m_scene);
		lightSSBO->SendBlocks<glm::mat4>(lightMatrices.data(), lightMatrices.size() * sizeof(glm::mat4));
		lightSSBO->Bind(0);

		m_scene->DrawAll(*renderer, &m_defaultMaterial);

		renderer->Draw(modelCube, &cubeTransform.GetWorldMatrix(), &m_defaultMaterial);

		lightSSBO->Unbind();

		HandleInput();

		window->SwapBuffers();
		inputManager->clearEvents();

		clock.Update();
	}
}

void Example::Application::HandleInput() const
{
	if (inputManager->IsKeyPressed(OpenSandBox::Inputs::EKey::KEY_ESCAPE))
		window->SetShouldClose(true);

	if (inputManager->IsKeyPressed(OpenSandBox::Inputs::EKey::KEY_R))
		OpenSandBox::Resources::Loaders::ShaderLoader::Recompile(OpenSandBox::Managers::ResourcesManager::Instance().GetShader("Standard"), projectAssetsPath + "Shaders\\Standard.glsl");
}

bool Example::Application::IsRunning() const
{
	return isRunning && window->IsActive();
}
