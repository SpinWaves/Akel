#include <Akel.h>

#define AK_PROJECT_FILE_DIR std::string(Ak::Core::getMainDirPath() + "SandBox/cube")
#define AK_PROJECT_FILE_NAME std::string("cube")

#include <Akel_main.h>
#include "cubeComponent.h"

class Cube : public Ak::Application
{
    public:
        explicit Cube() : Ak::Application("Cube")
        {
            add_component(Ak::custom_malloc<CubeComponent>());
        }
        ~Cube() = default;
};

Ak::Application* Akel_main()
{
    return Ak::custom_malloc<Cube>();
}
