#include <AkelCore.h>
#include <AkelPlatform.h>
#include <AkelEntryPoint.h>

void AkelSetupEngineConfig(Ak::EngineConfig& config)
{
}

void AkelSetupApplication(Ak::Application& app)
{
	app.LoadEngineModule<Ak::PlatformModule>();
	app.AddComponent<Ak::WindowComponent>(1250, 780, "My Window", Ak::WindowClosable | Ak::WindowResizable);
}
