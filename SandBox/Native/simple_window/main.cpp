#include <AkelCore.h>
#include <AkelPlatform.h>
#include <AkelEntryPoint.h>

void AkelSetupApplication(Ak::Application& app)
{
	app.LoadEngineModule<Ak::CoreModule>();
	app.LoadEngineModule<Ak::PlatformModule>();
}
