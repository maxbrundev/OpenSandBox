#pragma once

#include "OpenSandBox/API/Export.h"

#include <assimp/scene.h>

#include "OpenSandBox/Geometry/Vertex.h"

#include "OpenSandBox/Resources/Model.h"
#include "OpenSandBox/Resources/Texture.h"

namespace OpenSandBox::Resources::Parsers
{
	class API_OPENSANDBOX AssimpParser
	{
	public:
		bool LoadModel(const std::string& p_filePath, Model& p_model, bool p_isLoadingMaterial);

	private:
		void ProcessNode(const aiMatrix4x4* p_transform, const aiNode* p_node, const aiScene* p_scene, std::vector<Mesh*>& p_meshes, std::array<Material*, 255>&, bool p_isLoadingMaterial);
		void ProcessMesh(const aiMatrix4x4* p_transform, const aiMesh* p_mesh, const aiScene* p_scene, std::vector<Geometry::Vertex>& p_outVertices, std::vector<uint32_t>& p_outIndices);
		void ProcessMaterial(const aiMesh* p_mesh, const aiScene* p_scene, Material& p_outMaterial);

		void LoadTexturesFromMaterial(const aiMaterial* p_mat, aiTextureType p_type, ETextureType p_textureType, std::unordered_map<ETextureType, std::shared_ptr<Texture>>& p_outTextures);

		std::vector<std::shared_ptr<Texture>> m_loadedTextures;
		std::string m_directory;
	};
}
