// This file is a part of Akel
// Authors : @kbz_8
// Created : 09/02/2023
// Updated : 10/02/2023

#include <Renderer/Images/cubemap.h>
#include <Core/log.h>
#include <Renderer/Buffers/vk_buffer.h>

namespace Ak
{
	CubeMap::CubeMap(std::filesystem::path cube_map_file) : _file(cube_map_file)
	{
		if(!std::filesystem::exists(_file))
			Core::log::report(FATAL_ERROR, "Cube Map : cube map file doesn't exists");

		std::ifstream file(_file, std::ios::binary);
		if(!file.is_open())
		{
			Core::log::report(ERROR, "Cube Map : unable to open '%s'", _file.string().c_str());
			return;
		}

		file.unsetf(std::ios::skipws);

		file.seekg(0, std::ios::end);
		std::size_t fileSize = file.tellg();
		file.seekg(0, std::ios::beg);

		std::vector<uint8_t> data(fileSize);
		data.insert(data.begin(), std::istream_iterator<uint8_t>(file), std::istream_iterator<uint8_t>());
		
		file.close();
		
		_json = json::from_msgpack(data);

		load();
	}

	CubeMap::CubeMap(CubeMapParts parts, std::string name)
	{
		_file = parts.top.remove_filename() / name / ".akcub";
		_json["top"] = parts.top.string();
		_json["bottom"] = parts.bottom.string();
		_json["left"] = parts.left.string();
		_json["right"] = parts.right.string();
		_json["front"] = parts.front.string();
		_json["back"] = parts.back.string();

		std::filesystem::remove(_file);
		std::ofstream newFile(_file, std::ios::ate | std::ios::binary);
		if(!newFile.is_open())
			Core::log::report(ERROR, "Cube Map : unable to create new cube map file");
		else
		{
			std::vector<uint8_t> data = json::to_msgpack(_json);
			for(uint8_t byte : data)
				newFile << byte;
			newFile.close();
		}

		load();
	}

	void CubeMap::load() noexcept
	{
		const std::array<std::string, 6> sides = {"right", "left", "top", "bottom", "back", "front"};
		std::vector<uint8_t> data;
		int width;
		int height;

		for(const std::string& side : sides)
		{
			uint8_t* tmp;
			int channels;

			std::string file  = _json[side];

			if(!std::filesystem::exists(file))
				Core::log::report(FATAL_ERROR, "Trying to create a cube map from unfound file '%s'", file.c_str());
			tmp = (uint8_t*)stbi_loadf(file.c_str(), &width, &height, &channels, 4);
			data.resize(data.size() + width * height * 4);
			for(std::size_t i = 0; i < width * height * 4; i++)
				data.push_back(tmp[i]);
		}

		Image::create(width, height, VK_FORMAT_R8G8B8A8_UNORM,
					VK_IMAGE_TILING_OPTIMAL,
					VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT,
					VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
		Image::createImageView(VK_IMAGE_VIEW_TYPE_CUBE, VK_IMAGE_ASPECT_COLOR_BIT);
		Image::createSampler();

		Buffer staging_buffer;
		staging_buffer.create(Buffer::kind::dynamic, data.size(), VK_BUFFER_USAGE_TRANSFER_SRC_BIT, data.data());
		Image::copyBuffer(staging_buffer);
		staging_buffer.destroy();
	}
}
