#include "OpenSandBox.h"

#include "OpenSandBox/Buffers/VertexArray.h"

OpenSandBox::Buffers::VertexArray::VertexArray() : index{0}
{
	glGenVertexArrays(1, &m_bufferID);
	Bind();
}

OpenSandBox::Buffers::VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_bufferID);
}

void OpenSandBox::Buffers::VertexArray::BindAttribPointer(const unsigned int p_size, const unsigned int p_type, const unsigned int p_normalized, const unsigned int p_stride, void* p_pointer)
{
	glEnableVertexAttribArray(index);
	glVertexAttribPointer(static_cast<GLuint>(index), static_cast<GLint>(p_size), static_cast<GLenum>(p_type), p_normalized, static_cast<GLsizei>(p_stride), static_cast<const GLvoid*>(p_pointer));
	index++;
}

void OpenSandBox::Buffers::VertexArray::Bind() const
{
	glBindVertexArray(m_bufferID);
}

void OpenSandBox::Buffers::VertexArray::Unbind() const
{
	glBindVertexArray(0);
}

GLuint OpenSandBox::Buffers::VertexArray::GetID() const
{
	return m_bufferID;
}
