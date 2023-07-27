#include "OpenSandBox.h"

#include "OpenSandBox/Resources/Model.h"

#include "OpenSandBox/Eventing/Event.h"

OpenSandBox::Resources::Model::Model(const std::string& p_filePath) : path(p_filePath)
{
	m_materials.fill(nullptr);
}

OpenSandBox::Resources::Model::~Model()
{
	for (auto& mesh : m_meshes)
	{
		delete mesh;
		mesh = nullptr;
	}

	for (auto& material : m_materials)
	{
		delete material;
		material = nullptr;
	}

}

void OpenSandBox::Resources::Model::SetShader(Shader& p_shader) const
{
	for(const auto material : m_materials)
	{
		if(material)
		{
			material->SetShader(&p_shader);
		}
	}
}

std::vector<std::string>& OpenSandBox::Resources::Model::GetMaterialNames()
{
	return m_materialNames;
}

std::vector<OpenSandBox::Resources::Mesh*>& OpenSandBox::Resources::Model::GetMeshes()
{
	return m_meshes;
}

std::array<OpenSandBox::Resources::Material*, 255>& OpenSandBox::Resources::Model::GetMaterials()
{
	return m_materials;
}
