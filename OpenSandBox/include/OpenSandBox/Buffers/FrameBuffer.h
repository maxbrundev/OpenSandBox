#pragma once

#include "OpenSandBox/API/Export.h"

#include "OpenSandBox/Context/Driver.h"

namespace OpenSandBox::Buffers
{
	class API_OPENSANDBOX FrameBuffer
	{
	public:
		FrameBuffer(uint16_t p_width, uint16_t p_height);
		~FrameBuffer();

		void Bind() const;
		void Unbind() const;

		void Resize(uint16_t p_width, uint16_t p_height);

		uint32_t GetID() const;
		uint32_t GetTextureID() const;
		uint32_t GetRenderBufferID() const;

		const std::pair<uint16_t, uint16_t> GetSize() const;

	private:
		uint32_t m_bufferID = 0;
		uint32_t m_renderTexture = 0;
		uint32_t m_depthStencilBuffer = 0;

		std::pair<uint16_t, uint16_t> m_size;
	};
}