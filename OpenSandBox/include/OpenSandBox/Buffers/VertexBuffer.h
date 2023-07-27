#pragma once

#include "OpenSandBox/API/Export.h"

#include "OpenSandBox/Context/Driver.h"

namespace OpenSandBox::Buffers
{
	class API_OPENSANDBOX VertexBuffer
	{
	public:
		VertexBuffer(const void* p_data, size_t p_elements);
		~VertexBuffer();

		void Bind() const;
		void Unbind() const;

		GLuint GetID();

	private:
		GLuint m_bufferID;
	};
}