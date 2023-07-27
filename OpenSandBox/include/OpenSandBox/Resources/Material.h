#pragma once

#include "OpenSandBox/API/Export.h"

#include <map>
#include <any>

#include "OpenSandBox/Resources/Texture.h"
#include "OpenSandBox/Resources/Shader.h"

namespace OpenSandBox::Resources
{
	class API_OPENSANDBOX Material
	{
	public:
		Material();
		~Material();

		void Bind(const Texture* p_emptyTexture) const;
		void Unbind() const;

		bool HasShader() const;
		void FillUniform();
		void FillTextures(std::unordered_map<ETextureType, std::shared_ptr<Texture>> p_textures);

		template<typename T>
		void SetUniform(const std::string p_key, const T& p_value)
		{
			if (m_uniformsData.find(p_key) != m_uniformsData.end())
				m_uniformsData[p_key] = std::any(p_value);
		}

		template<typename T>
		const T& GetUniform(const std::string p_key)
		{
			if(m_uniformsData.find(p_key) != m_uniformsData.end())
			{
				return T();
			}

			return std::any_cast<T>(m_uniformsData.at(p_key));
		}

		void ResetToPreviousShader();
		void SetShader(Shader* p_shader);
		void SetTexture(Texture* p_texture);
		void SetBlendable(bool p_blendable);
		void SetBackfaceCulling(bool p_backfaceCulling);
		void SetFrontfaceCulling(bool p_frontfaceCulling);
		void SetDepthTest(bool p_depthTest);
		void SetDepthWriting(bool p_depthWriting);
		void SetColorWriting(bool p_colorWriting);
		void SetGPUInstances(uint64_t p_instances);
		void SetName(std::string p_name);

		const Shader* GetShader() const;
		const std::unordered_map<ETextureType, std::shared_ptr<Texture>>& GetTextures();
		const std::string& GetName();
		const std::map<std::string, std::any>& GetUniformsData();
		bool IsBlendable() const;
		bool HasBackfaceCulling() const;
		bool HasFrontfaceCulling() const;
		bool HasDepthTest() const;
		bool HasDepthWriting() const;
		bool HasColorWriting() const;

		uint64_t GetGPUInstances() const;

	private:
		Shader* m_previousShader = nullptr;
		Shader* m_shader = nullptr;

		std::unordered_map<ETextureType, std::shared_ptr<Texture>> m_textures;
		std::map<std::string, std::any> m_uniformsData;
		bool m_blendable = false;
		bool m_backfaceCulling = true;
		bool m_frontfaceCulling = false;
		bool m_depthTest = true;
		bool m_depthWriting = true;
		bool m_colorWriting = true;

		bool hasSpecularMap = true;

		uint64_t m_gpuInstances = 1;

		std::string m_name;
	};
}