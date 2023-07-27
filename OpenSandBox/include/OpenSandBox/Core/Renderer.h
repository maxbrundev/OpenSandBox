#pragma once

#include "OpenSandBox/API/Export.h"

#include "OpenSandBox/Context/Driver.h"

#include "OpenSandBox/LowRenderer/CameraController.h"

#include "OpenSandBox/Resources/Model.h"
#include "OpenSandBox/Resources/Texture.h"

namespace OpenSandBox::Core
{
	namespace SceneSystem
	{
		class Scene;
	}

	class API_OPENSANDBOX Renderer
	{
	public:
		Renderer(Context::Driver& p_driver);
		~Renderer();

		void Draw(Resources::Model& p_model, glm::mat4 const* p_modelMatrix, Resources::Material* p_defaultMaterial) const;
		void SetClearColor(float p_red, float p_green, float p_blue, float p_alpha = 1.0f) const;
		void Clear(bool p_colorBuffer = true, bool p_depthBuffer = true, bool p_stencilBuffer = true) const;
		void Clear(LowRenderer::Camera& p_camera, bool p_colorBuffer, bool p_depthBuffer, bool p_stencilBuffer) const;
		std::vector<glm::mat4> FindLightMatrices(SceneSystem::Scene& p_scene);
		void RegisterModelMatrixSender(std::function<void(glm::mat4)> p_modelMatrixSender);

		void PolygonModeLine() const;
		void PolygonModeFill() const;

	private:
		std::function<void(glm::mat4)> m_modelMatrixSender;
		void DrawMesh(const Resources::Mesh& p_mesh, Resources::Material& p_material) const;

	private:
		Context::Driver& m_driver;

		Resources::Texture* m_emptyTexture = nullptr;
	};
}
