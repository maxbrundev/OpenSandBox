#pragma once

#include <GL/glew.h>

#include "OpenSandBox/Resources/Texture.h"

namespace OpenSandBox::Resources::Loaders
{
	class TextureLoader
	{
	public:
		TextureLoader() = delete;

		static Texture* Create(std::string p_filePath, ETextureFilteringMode p_firstFilter, ETextureFilteringMode p_secondFilter, ETextureType p_textureType, bool p_flipVertically, bool p_generateMipmap);
		static Texture* CreateColor(uint32_t p_data, ETextureFilteringMode p_firstFilter, ETextureFilteringMode p_secondFilter, bool p_generateMipmap);
		static void Reload(const Texture& p_texture, const std::string& p_filePath, ETextureFilteringMode p_firstFilter, ETextureFilteringMode p_secondFilter, ETextureType p_textureType, bool p_flipVertically, bool p_generateMipmap);
		static bool Destroy(Texture*& p_textureInstance);
		static bool Delete(Texture* p_textureInstance);

	private:
		static std::string __FILE_TRACE;
	};
}
