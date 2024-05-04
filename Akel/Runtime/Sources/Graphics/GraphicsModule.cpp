// This file is a part of Akel
// Authors : @kbz_8
// Created : 02/02/2024
// Updated : 04/05/2024

#include <Core/OS/OSInstance.h>
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
		LoadDriver();
	}

	GraphicsModule& GraphicsModule::Get()
	{
		Verify(s_instance != nullptr, "GraphicsModule has not been instanciated");
		return *s_instance;
	}

	void GraphicsModule::LoadDriver()
	{
		using DriverLoaderFunctor = RHIRenderer* (*)(void);

		std::multimap<int, RendererDrivers, std::greater<int>> drivers_scores;

		for(std::size_t i = 0; i < RendererDriversCount; i++)
			drivers_scores.insert(std::make_pair(ScoreDriver(static_cast<RendererDrivers>(i)), static_cast<RendererDrivers>(i)));

		if(drivers_scores.upper_bound(0) == drivers_scores.end())
			FatalError("GraphicsModule : failed to find a suitable render driver");

		#ifndef AK_EMBEDDED_RENDERER_DRIVERS
			ConstMap<RendererDrivers, std::filesystem::path> drivers_paths = {
				{ RendererDrivers::Vulkan, AK_LIB_PREFIX "AkelVulkan" AK_LIB_EXTENSION },
				{ RendererDrivers::WebGPU, AK_LIB_PREFIX "AkelWebGPU" AK_LIB_EXTENSION },
			};
		#endif

		for(auto& [score, driver] : drivers_scores)
		{
			if(score < 1)
				continue;

			#ifndef AK_EMBEDDED_RENDERER_DRIVERS
				LibLoader& loader = OSInstance::GetLibLoader();
				LibModule module = loader.Load(drivers_paths.Find(driver)->second);
				if(module == NullModule)
				{
					Warning("GraphicsModule : cannot load %, falling back...", drivers_paths.Find(driver)->second);
					continue;
				}

				DriverLoaderFunctor loader_function = reinterpret_cast<DriverLoaderFunctor>(loader.GetSymbol(module, "AkelLoadRendererDriver"));
				if(!loader_function)
				{
					Warning("GraphicsModule : cannot load %, no loading symbol found, falling back...", drivers_paths.Find(driver)->second);
					loader.UnloadLib(module);
					continue;
				}

				RHIRenderer* renderer = loader_function();
			#else
				RHIRenderer* renderer = nullptr;
			#endif

			if(renderer == nullptr)
			{
				Warning("GraphicsModule : cannot load %, error while loading the renderer, falling back...", drivers_paths.Find(driver)->second);
					loader.UnloadLib(module);
				continue;
			}

			#ifndef AK_EMBEDDED_RENDERER_DRIVERS
				DebugLog("GraphicsModule : loaded %", drivers_paths.Find(driver)->second);
			#endif

			m_chosen_driver = driver;
			m_renderer = renderer;
			m_driver_lib = module;
			break;
		}

		if(m_renderer == nullptr)
			FatalError("GraphicsModule : failed to load any renderer driver");
	}

	int GraphicsModule::ScoreDriver(RendererDrivers driver)
	{
		int score = -1;

		static ConstMap<std::string, RendererDrivers> cli_options = {
			{ "vulkan", RendererDrivers::Vulkan },
			{ "webgpu", RendererDrivers::WebGPU },
			{ "auto", RendererDrivers::Auto },
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
			{ RendererDrivers::WebGPU, 100 },
			{ RendererDrivers::Auto, 0 },
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
		OSInstance::GetLibLoader().UnloadLib(m_driver_lib);
		s_instance = nullptr;
	}
}
