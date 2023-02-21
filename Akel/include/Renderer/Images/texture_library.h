// This file is a part of Akel
// Authors : @kbz_8
// Created : 21/02/2023
// Updated : 21/02/2023

#ifndef __AK_TEXTURE_LIBRARY__
#define __AK_TEXTURE_LIBRARY__

#include <Akpch.h>
#include <Renderer/Images/texture.h>
#include <Utils/selfInstance.h>

namespace Ak
{
	using TextureID = uint32_t;

	class TextureLibrary : public SelfInstance<TextureLibrary>
	{
		public:
			TextureLibrary() = default;

			std::shared_ptr<Texture> getTexture(TextureID id);
			TextureID addTextureToLibrary(std::shared_ptr<Texture> texture);
			void removeTextureFromLibrary(TextureID id);

			void clearLibrary();

			~TextureLibrary() = default;

		private:
			std::unordered_map<TextureID, std::shared_ptr<Texture>> _cache;
			TextureID _current_id = 0;
	};
}

#endif
