#include "OpenSandBox.h"

#include "OpenSandBox/Buffers/FrameBuffer.h"

OpenSandBox::Buffers::FrameBuffer::FrameBuffer(uint16_t p_width, uint16_t p_height)
{
	glGenFramebuffers(1, &m_bufferID);
	glGenTextures(1, &m_renderTexture);
	glGenRenderbuffers(1, &m_depthStencilBuffer);

	glBindTexture(GL_TEXTURE_2D, m_renderTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);

	Bind();
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_renderTexture, 0);
	Unbind();

	Resize(p_width, p_height);
}

OpenSandBox::Buffers::FrameBuffer::~FrameBuffer()
{
	glDeleteBuffers(1, &m_bufferID);
	glDeleteTextures(1, &m_renderTexture);
	glDeleteRenderbuffers(1, &m_depthStencilBuffer);
}

void OpenSandBox::Buffers::FrameBuffer::Bind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_bufferID);
}

void OpenSandBox::Buffers::FrameBuffer::Unbind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void OpenSandBox::Buffers::FrameBuffer::Resize(uint16_t p_width, uint16_t p_height)
{
	glBindTexture(GL_TEXTURE_2D, m_renderTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, p_width, p_height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	glBindRenderbuffer(GL_RENDERBUFFER, m_depthStencilBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_STENCIL, p_width, p_height);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	Bind();
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthStencilBuffer);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_depthStencilBuffer);
	Unbind();

	m_size.first = p_width;
	m_size.second = p_height;
}

uint32_t OpenSandBox::Buffers::FrameBuffer::GetID() const
{
	return m_bufferID;
}

uint32_t OpenSandBox::Buffers::FrameBuffer::GetTextureID() const
{
	return m_renderTexture;
}

uint32_t OpenSandBox::Buffers::FrameBuffer::GetRenderBufferID() const
{
	return m_depthStencilBuffer;
}

const std::pair<uint16_t, uint16_t> OpenSandBox::Buffers::FrameBuffer::GetSize() const
{
	return m_size;
}
