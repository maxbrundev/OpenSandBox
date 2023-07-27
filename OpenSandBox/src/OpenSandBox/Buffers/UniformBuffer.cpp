#include "OpenSandBox.h"

#include "OpenSandBox/Buffers/UniformBuffer.h"

#include "OpenSandBox/Resources/Shader.h"

void OpenSandBox::Buffers::UniformBuffer::BindBlockToShader(Resources::Shader& p_shader, uint32_t p_uniformBlockLocation, uint32_t p_bindingPoint)
{
	glUniformBlockBinding(p_shader.id, p_uniformBlockLocation, p_bindingPoint);
}

void OpenSandBox::Buffers::UniformBuffer::BindBlockToShader(Resources::Shader& p_shader, const std::string& p_name,
	uint32_t p_bindingPoint)
{
	glUniformBlockBinding(p_shader.id, GetBlockLocation(p_shader, p_name), p_bindingPoint);
}

uint32_t OpenSandBox::Buffers::UniformBuffer::GetBlockLocation(Resources::Shader& p_shader, const std::string& p_name)
{
	return glGetUniformBlockIndex(p_shader.id, p_name.c_str());
}

OpenSandBox::Buffers::UniformBuffer::UniformBuffer(size_t p_size, uint32_t p_bindingPoint, uint32_t p_offset, EAccessSpecifier p_accessSpecifier)
{
	glGenBuffers(1, &m_bufferID);
	glBindBuffer(GL_UNIFORM_BUFFER, m_bufferID);
	glBufferData(GL_UNIFORM_BUFFER, p_size, nullptr, static_cast<GLint>(p_accessSpecifier));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	glBindBufferRange(GL_UNIFORM_BUFFER, p_bindingPoint, m_bufferID, p_offset, p_size);
}

OpenSandBox::Buffers::UniformBuffer::~UniformBuffer()
{
	glDeleteBuffers(1, &m_bufferID);
}

void OpenSandBox::Buffers::UniformBuffer::Bind() const
{
	glBindBuffer(GL_UNIFORM_BUFFER, m_bufferID);
}

void OpenSandBox::Buffers::UniformBuffer::Unbind() const
{
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

uint32_t OpenSandBox::Buffers::UniformBuffer::GetID() const
{
	return m_bufferID;
}
