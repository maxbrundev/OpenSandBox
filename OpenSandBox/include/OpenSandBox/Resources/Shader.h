#pragma once

#include "OpenSandBox/API/Export.h"

#include <GL/glew.h>

#include "OpenSandBox/Resources/UniformInfo.h"


namespace OpenSandBox::Resources
{
	class API_OPENSANDBOX Shader
	{
	public:
		Shader(std::string p_filePath, uint32_t p_id);
		~Shader();

		void QueryUniforms();

		void Bind() const;
		void Unbind() const;

		void SetUniformIntPointer(const std::string_view p_name, int p_count, const int* p_value);
		void SetUniformInt(const std::string_view p_name, const int p_value);
		void SetUniformFloat(const std::string_view p_name, const float p_value);
		void SetUniform4Float(const std::string_view p_name, const float p_v0, const float p_v1, const float p_v2, const float p_v3);
		void SetUniformVec2(const std::string_view p_name, const glm::vec2& p_vec2);
		void SetUniformVec3(const std::string_view p_name, const glm::vec3& p_vec3);
		void SetUniformVec4(const std::string_view p_name, const glm::vec4& p_vec4);
		void SetUniformMat4(const std::string_view p_name, const glm::mat4& p_mat4);

		int GetUniformInt(const std::string& p_name);
		float GetUniformFloat(const std::string& p_name);
		glm::vec2 GetUniformVec2(const std::string& p_name);
		glm::vec3 GetUniformVec3(const std::string& p_name);
		glm::vec4 GetUniformVec4(const std::string& p_name);
		glm::mat4 GetUniformMat4(const std::string& p_name);

		const UniformInfo* GetUniformInfo(const std::string& p_name) const;

	private:
		bool IsEngineUBOUniform(const std::string& p_uniformName);
		uint32_t GetUniformLocation(const std::string_view p_name);

	public:
		const uint32_t id;
		const std::string path;
		std::vector<UniformInfo> uniforms;

	private:
		std::unordered_map<std::string_view, uint32_t> m_uniformLocationCache;
	};
}