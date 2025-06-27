// Copyright (C) 2025 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Graphics/Renderer/RenderCore.h>
#include <Graphics/RHI/Defs.h>

namespace Ak
{
	RenderCore* RenderCore::s_instance = nullptr;

	RenderCore::RenderCore(UniquePtr<RHIInstance> instance)
	{
		if(s_instance != nullptr)
			return;

		p_instance = std::move(instance);

		AdapterMinimalSpecs adapter_specs;
		adapter_specs.type = AdapterType::Any;
		adapter_specs.vendors = AdapterVendorAny;
		adapter_specs.memory = 128;
		p_adapter = p_instance->PickAdapter(std::move(adapter_specs));
		p_device = p_adapter->CreateDevice();

		s_instance = this;
	}

	RenderCore::~RenderCore()
	{
		if(s_instance == nullptr)
			return;

		p_device.Reset();
		p_adapter.Reset();
		p_instance.Reset();

		s_instance = nullptr;
	}
}
