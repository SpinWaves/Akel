// This file is a part of Akel
// Authors : @kbz_8
// Created : 22/12/2022
// Updated : 23/12/2022

#include <Renderer/Images/texture.h>

namespace Ak
{
	void Texture::create(std::vector<uint32_t> pixels, uint32_t width, uint32_t height)
	{
//		Image::create(pixels.data(), width, height, );
	}

	void Texture::createFromFile(std::filesystem::path path)
	{
		SDL_Surface* image = IMG_Load(path.c_str());
//		Image::create(image->pixels, image->w, image->h, );
		SDL_FreeSurface(image);
	}
}
