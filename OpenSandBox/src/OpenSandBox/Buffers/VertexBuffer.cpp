#include "OpenSandBox.h"

#include "OpenSandBox/Buffers/VertexBuffer.h"

OpenSandBox::Buffers::VertexBuffer::VertexBuffer(const void* p_data, size_t p_elements)
{
	glGenBuffers(1, &m_bufferID);
	Bind();
	glBufferData(GL_ARRAY_BUFFER, p_elements * sizeof(float), p_data, GL_STATIC_DRAW);
}

OpenSandBox::Buffers::VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_bufferID);
}

void OpenSandBox::Buffers::VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
}

void OpenSandBox::Buffers::VertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

GLuint OpenSandBox::Buffers::VertexBuffer::GetID()
{
	return m_bufferID;
}
