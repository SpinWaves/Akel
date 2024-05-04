#include <AkelCore.h>
#include <AkelPlatform.h>
#include <AkelEntryPoint.h>

void AkelSetupEngineConfig(Ak::EngineConfig& config)
{
	config.preffered_render_api = Ak::RendererDrivers::Vulkan;
}

void AkelSetupApplication(Ak::Application& app)
{

}
