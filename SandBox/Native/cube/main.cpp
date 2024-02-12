#include <AkelCore.h>
#include <AkelPlatform.h>
#include <AkelGraphics.h>
#include <AkelEntryPoint.h>

void AkelSetupApplication(Ak::Application& app)
{
	app.LoadEngineModule<Ak::GraphicsModule>(Ak::RenderBackend::Vulkan);
	app.AddComponent<Ak::WindowComponent>(1250, 780, "My Window", Ak::WindowClosable | Ak::WindowResizable);
}
