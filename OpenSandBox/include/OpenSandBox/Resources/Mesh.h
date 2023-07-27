#pragma once

#include "OpenSandBox/API/Export.h"

#include "OpenSandBox/Geometry/Vertex.h"

#include "OpenSandBox/Buffers/VertexArray.h"
#include "OpenSandBox/Buffers/VertexBuffer.h"
#include "OpenSandBox/Buffers/IndexBuffer.h"

namespace OpenSandBox::Resources
{
	class API_OPENSANDBOX Mesh
	{
	public:
		Mesh(const std::vector<Geometry::Vertex>& p_vertices, const std::vector<uint32_t>& p_indices, uint32_t p_materialIndex);
		~Mesh();

		void Bind() const;
		void Unbind() const;

		std::function<void(std::string_view, uint32_t)> SetTextureUniformCallback;

		uint32_t GetVertexCount() const;
		uint32_t GetIndexCount() const;
		uint32_t GetMaterialIndex() const;

	private:
		void InitBuffers(const std::vector<Geometry::Vertex>& p_vertices, const std::vector<uint32_t>& p_indices);

	private:
		const uint32_t m_vertexCount;
		const uint32_t m_indicesCount;
		const uint32_t m_materialIndex;

		Buffers::VertexArray m_vertexArray;
		std::unique_ptr<Buffers::VertexBuffer> m_vertexBuffer;
		std::unique_ptr<Buffers::IndexBuffer> m_indexBuffer;
	};
}