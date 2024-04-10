// This file is a part of Akel
// Authors : @kbz_8
// Created : 02/02/2024
// Updated : 10/04/2024

#include <Graphics/Enums.h>
#include <Core/Application.h>
#include <Graphics/GraphicsModule.h>
#include <Core/CLI.h>
#include <Core/Logs.h>
#include <Utils/ConstMap.h>

namespace Ak
{
	GraphicsModule* GraphicsModule::s_instance = nullptr;

	GraphicsModule::GraphicsModule() : Module("GraphicsModule")
	{
		if(s_instance != nullptr)
			FatalError("only one instance of GraphicsModule can exist at a given time");
		s_instance = this;
	}

	GraphicsModule& GraphicsModule::Get()
	{
		Verify(s_instance != nullptr, "GraphicsModule has not been instanciated");
		return *s_instance;
	}

	void GraphicsModule::LoadDriver()
	{
		using DriverLoader = func::function<RHIRenderer*(void)>;

		std::multimap<int, RendererDrivers> drivers_scores;

		RendererDrivers choosen = RendererDrivers::Vulkan;

		for(std::size_t i = 0; i < RendererDriversCount; i++)
			drivers_scores.insert(std::make_pair(ScoreDriver(static_cast<RendererDrivers>(i)), static_cast<RendererDrivers>(i)));

		#ifdef AK_EMBEDDED_RENDERER_DRIVERS
			
		#else
			
		#endif
	}

	int GraphicsModule::ScoreDriver(RendererDrivers driver)
	{
		int score = -1;

		static ConstMap<std::string, RendererDrivers> cli_options = {
			{ "vulkan", RendererDrivers::Vulkan },
			{ "none", RendererDrivers::None },
		};

		static std::optional<std::string> driver_option = CommandLineInterface::Get().GetOption("rdr-driver");
		if(driver_option.has_value())
		{
			if(!cli_options.Has(*driver_option))
				Error("GraphicsModule : invalid rdr-driver option '%'", *driver_option);
			else
			{
				auto it = cli_options.Find(*driver_option);
				if(it->second != driver)
					return -1;
			}
		}

		static ConstMap<RendererDrivers, int> api_scores = {
			{ RendererDrivers::Vulkan, 500 },
			{ RendererDrivers::None, -1 },
		};

		score = api_scores.Find(driver)->second;

		if(!Application::IsInit())
			FatalError("GraphicsModule : cannot select renderer driver, Application is not init (wtf what did u do ?)");

		RendererDrivers preffered = Application::Get().GetEngineConfig().preffered_render_api;

		if(driver == preffered)
			score = std::numeric_limits<int>::max();

		return score;
	}

	GraphicsModule::~GraphicsModule()
	{
		s_instance = nullptr;
	}
}
