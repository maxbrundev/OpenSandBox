#pragma once

#include "OpenSandBox/API/Export.h"

#include "OpenSandBox/Context/Driver.h"

namespace OpenSandBox::Buffers
{
	class API_OPENSANDBOX IndexBuffer
	{
	public:
		IndexBuffer(const unsigned int* p_data, size_t p_elements);
		~IndexBuffer();

		void Bind() const;
		void Unbind() const;

		GLuint GetID() const;

	private:
		GLuint m_bufferID;
	};
}