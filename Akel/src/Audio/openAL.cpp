// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/08/2021
// Updated : 28/03/2023

#include <Audio/openAL.h>
#include <Core/core.h>

namespace Ak
{
	struct OpenAL::_Pimpl
	{
		ALCdevice* device = nullptr;
		ALCcontext* context = nullptr;
	};

	OpenAL::OpenAL() : _impl(memAlloc<OpenAL::_Pimpl>()) {}

	bool OpenAL::initOAL()
	{
		_impl->device = alcOpenDevice(nullptr);
		if(!_impl->device)
		{
			Core::log::report(ERROR, "OpenAL: unable to get sound device");
			return false;
		}

		_impl->context = alcCreateContext(_impl->device, nullptr);
		if(!_impl->context)
		{
			Core::log::report(ERROR, "OpenAL: unable to create context");
			return false;
		}

		if(!alcMakeContextCurrent(_impl->context))
		{
			Core::log::report(ERROR, "OpenAL: unable to make context current");
			return false;
		}

		return true;
	}

	void OpenAL::shutdownOAL()
	{
		alcMakeContextCurrent(nullptr);
		alcDestroyContext(_impl->context);
		alcCloseDevice(_impl->device);
	}

	OpenAL::~OpenAL()
	{
		memFree(_impl);
	}
}
