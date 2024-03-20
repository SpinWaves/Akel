#include <AkelCore.h>
#include <AkelPlatform.h>
#include <AkelGraphics.h>
#include <AkelEntryPoint.h>

void AkelSetupApplication(Ak::Application& app)
{
	app.LoadEngineModule<Ak::GraphicsModule>();

	auto& window = app.AddComponent<Ak::WindowComponent>(1250, 780, "My Window", Ak::WindowClosable | Ak::WindowResizable);

	//Ak::GraphicsModule::Get().RegisterNewRenderer(window);
}
