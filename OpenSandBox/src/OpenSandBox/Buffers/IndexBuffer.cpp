#include "OpenSandBox.h"

#include "OpenSandBox/Buffers/IndexBuffer.h"

OpenSandBox::Buffers::IndexBuffer::IndexBuffer(const unsigned int* p_data, size_t p_elements)
{
	glGenBuffers(1, &m_bufferID);
	Bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, p_elements * sizeof(unsigned int), p_data, GL_STATIC_DRAW);
}

OpenSandBox::Buffers::IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &m_bufferID);
}

void OpenSandBox::Buffers::IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferID);
}

void OpenSandBox::Buffers::IndexBuffer::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

uint32_t OpenSandBox::Buffers::IndexBuffer::GetID() const
{
	return m_bufferID;
}
